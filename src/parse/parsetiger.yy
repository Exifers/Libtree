%require "3.0"
%language "C++"
%name-prefix "parse"
%define api.value.type variant
%define api.token.constructor
%skeleton "glr.cc"
%glr-parser
%expect 5
%expect-rr 0
%error-verbose
%defines
%debug
  /* Prefix all the tokens with TOK_ to avoid colisions. */
%define api.token.prefix {TOK_}

/* We use pointers to store the filename in the locations.  This saves
   space (pointers), time (no deep copy), but leaves the problem of
   deallocation.  This would be a perfect job for a misc::symbol
   object (passed by reference), however Bison locations require the
   filename to be passed as a pointer, thus forcing us to handle the
   allocation and deallocation of this object.

   Nevertheless, all is not lost: we can still use a misc::symbol
   object to allocate a flyweight (constant) string in the pool of
   symbols, extract it from the misc::symbol object, and use it to
   initialize the location.  The allocated data will be freed at the
   end of the program (see the documentation of misc::symbol and
   misc::unique).  */
%define filename_type {const std::string}
%locations

  /* The parsing context. */
%param { ::parse::TigerParser& tp }

/*---------------------.
| Support for tokens.  |
`---------------------*/
%code requires
{
#include <string>
#include <misc/algorithm.hh>
#include <misc/separator.hh>
#include <misc/symbol.hh>
#include <parse/fwd.hh>

  /* Pre-declare parse::parse to allow a ``reentrant'' parsing within
  ** the parser. */
  namespace parse
  {
    ast_type parse(Tweast& input);
  }
}

%code provides
{
  /* Announce to Flex the prototype we want for lexing (member) function. */
  # define YY_DECL_(Prefix)                               \
    ::parse::parser::symbol_type                          \
    (Prefix parselex)(::parse::TigerParser& tp)
  # define YY_DECL YY_DECL_(yyFlexLexer::)
}


%token <std::string>    STRING "string"
%token <misc::symbol>   ID     "identifier"
%token <int>            INT    "integer"


/*--------------------------------.
| Support for the non-terminals.  |
`--------------------------------*/

%code requires
{
# include <ast/fwd.hh>
// Provide the declarations of the following classes for the
// %destructor clauses below to work properly.
# include <ast/exp.hh>
# include <ast/var.hh>
# include <ast/ty.hh>
# include <ast/name-ty.hh>
# include <ast/field.hh>
# include <ast/field-init.hh>
# include <ast/function-dec.hh>
# include <ast/type-dec.hh>
# include <ast/var-dec.hh>
# include <ast/any-decs.hh>
# include <ast/decs-list.hh>
}

  /* Printers and destructors */
%destructor { delete $$; } <ast::Exp*>
%printer { debug_stream () << $$; } <int> <string>

/*-----------------------------------------.
| Code output in the implementation file.  |
`-----------------------------------------*/

%code
{
# include <parse/tiger-parser.hh>
# include <parse/scantiger.hh>
# include <parse/tweast.hh>
# include <misc/separator.hh>
# include <misc/symbol.hh>
# include <ast/all.hh>
# include <ast/libast.hh>

  namespace
  {

    /* Get the metavar from the specified map. */
    template <typename T>
    T*
    metavar(parse::TigerParser& tp, unsigned key)
    {
      parse::Tweast* input = tp.input_;
      return input->template take<T>(key);
    }

  }

  /* Use our local scanner object. */
  inline
  ::parse::parser::symbol_type
  parselex(parse::TigerParser& tp)
  {
    return tp.scanner_->parselex(tp);
  }
}

  /* Definition of the tokens, and their pretty-printing. */
%token AND          "&"
       ARRAY        "array"
       ASSIGN       ":="
       BREAK        "break"
       CAST         "_cast"
       CLASS        "class"
       COLON        ":"
       COMMA        ","
       DIVIDE       "/"
       DO           "do"
       DOT          "."
       ELSE         "else"
       END          "end"
       EQ           "="
       EXTENDS      "extends"
       FOR          "for"
       FUNCTION     "function"
       GE           ">="
       GT           ">"
       IF           "if"
       IMPORT       "import"
       IN           "in"
       LBRACE       "{"
       LBRACK       "["
       LE           "<="
       LET          "let"
       LPAREN       "("
       LT           "<"
       MINUS        "-"
       METHOD       "method"
       NE           "<>"
       NEW          "new"
       NIL          "nil"
       OF           "of"
       OR           "|"
       PLUS         "+"
       PRIMITIVE    "primitive"
       RBRACE       "}"
       RBRACK       "]"
       RPAREN       ")"
       SEMI         ";"
       THEN         "then"
       TIMES        "*"
       TO           "to"
       TYPE         "type"
       VAR          "var"
       WHILE        "while"
       EOF 0        "end of file"

  /* TODO check operator priority on these from subject */
%left AND OR
%left EQ NE
%left LT LE GT GE
%left PLUS MINUS
%left TIMES DIVIDE
%left DOT

%right "array_of"
%right "assign"
%right "if_then"
%right "if_then_else"
%right "while"
%right "for"

%type <std::list<ast::Exp*>> exps
%type <ast::Exp*> exp
%type <ast::DecsList*> decs
%type <ast::Dec*> dec
%type <ast::Var*> lvalue
%type <std::list<ast::FieldInit*>> rec_init_list
%type <std::list<ast::Exp*>> exp_comma_list
%type <ast::Var*> method_body
%type <std::list<ast::Exp*>> exp_semicolon_list
%type <ast::Ty*> ty
%type <ast::DecsList*> classfields
%type <ast::NameTy*> typeid
%type <ast::VarDec*> vardec
%type <ast::VarDecs*> tyfields
%type <ast::Decs*> classfield
%type <ast::FieldVar*> lvalue_fv
%type <ast::SubscriptVar*> lvalue_sc

%start program

%%

  /* Hint : non terminals are in lower case, terminals in upper case */

program: exp   { tp.ast_ = $1; }
       | decs  { tp.ast_ = $1; }
       ;

%token CAST "_cast";
%token EXP "_exp";

exp:
  /* Literals */
  NIL          { $$ = new ast::NilExp(@$); }
| INT          { $$ = new ast::IntExp(@$, $1); }
| STRING       { $$ = new ast::StringExp(@$, $1); }

| CAST LPAREN exp COMMA ty RPAREN
| EXP LPAREN INT RPAREN { $$ = metavar<ast::Exp>(tp, (unsigned) $3); }

  /* Array and record creation */
| ID LBRACK exp RBRACK OF exp  {
    $$ = new ast::ArrayExp(@$, new ast::NameTy(@$, $1), $3, $6);
  } %prec "array_of"

| ID LBRACE RBRACE {
    $$ = new ast::RecordExp(@$, new ast::NameTy(@$, $1),
        std::list<ast::FieldInit*>());
  }
| ID LBRACE rec_init_list RBRACE {
    $$ = new ast::RecordExp(@$, new ast::NameTy(@$, $1), $3);
  }
  /* Object creation */
| NEW ID { $$ = new ast::ObjectExp(@$, new ast::NameTy(@$, $2)); }
  /* Variables, field, element of an array */
| lvalue {
    $$ = $1;
  }
  /* Function call */
| ID LPAREN RPAREN {
    $$ = new ast::CallExp(@$, $1, std::list<ast::Exp*>());
  }
| ID LPAREN exp_comma_list RPAREN {
    $$ = new ast::CallExp(@$, $1, $3);
  }
  /* Method call */
| method_body LPAREN RPAREN {
    $$ = new ast::MethodCallExp(@$, misc::symbol(), std::list<ast::Exp*>(),
        $1);
  }
| method_body LPAREN exp_comma_list RPAREN {
    $$ = new ast::MethodCallExp(@$, misc::symbol(), $3, $1);
  }
  /* Operations */
| MINUS exp { $$ = new ast::OpExp(@$, nullptr, ast::OpExp::Oper::sub, $2); }

| exp PLUS exp { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::add, $3); }
| exp MINUS exp { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::sub, $3); }
| exp TIMES exp { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::mul, $3); }
| exp DIVIDE exp { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::div, $3); }
| exp EQ exp { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::eq, $3); }
| exp NE exp { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::ne, $3); }
| exp LT exp { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::lt, $3); }
| exp LE exp { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::le, $3); }
| exp GT exp { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::gt, $3); }
| exp GE exp  { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::ge, $3); }
| exp AND exp
| exp OR exp

| LPAREN exps RPAREN { $$ = new ast::SeqExp(@$, $2); }

  /* Assignment */
| lvalue ASSIGN exp {
    $$ = new ast::AssignExp(@$, $1, $3);
  } %prec "assign"

  /* Control structures */
| IF exp THEN exp {
    $$ = new ast::IfExp(@$, $2, $4, nullptr);
  } %prec "if_then"

| IF exp THEN exp ELSE exp {
    $$ = new ast::IfExp(@$, $2, $4, $6);
  } %prec "if_then_else"

| WHILE exp DO exp {
    $$ = new ast::WhileExp(@$, $2, $4);
  } %prec "while"

| FOR ID ASSIGN exp TO exp DO exp {
    $$ = new ast::ForExp(@$, new ast::VarDec(@$, $2, nullptr, $4), $6, $8);
  } %prec "for"
| BREAK { $$ = new ast::BreakExp(@$); }
| LET decs IN exps END { $$ = new ast::LetExp(@$, $2, $4); }
;

exps:
  %empty { $$ = std::list<ast::Exp*>(); }
| exp_semicolon_list { $$ = $1; }
;

exp_semicolon_list:
  exp {
    auto l = std::list<ast::Exp*>();
    l.push_front($1);
    $$ = l;
  }
| exp SEMI exp_semicolon_list {
    $3.push_front($1);
    $$ = $3;
  }
;

method_body:
  ID method_spec
;

method_spec:
  DOT ID method_spec_tail
| LBRACK exp RBRACK DOT ID method_spec_tail
;

method_spec_tail:
  %empty
| DOT ID method_spec_tail
| LBRACK exp RBRACK DOT ID method_spec_tail
;

exp_comma_list:
  exp {
    auto l = std::list<ast::Exp*>();
    l.push_front($1);
    $$ = l;
  }
| exp COMMA exp_comma_list {
    $3.push_front($1);
    $$ = $3;
  }
;

rec_init_list:
  ID EQ exp {
    auto field = new ast::FieldInit(@$, $1, $3);
    auto l = std::list<ast::FieldInit*>();
    l.push_front(field);
    $$ = l;
  }
| ID EQ exp COMMA rec_init_list {
    auto field = new ast::FieldInit(@$, $1, $3);
    auto l = $5;
    l.push_front(field);
    $$ = l;
  }
;

%token LVALUE "_lvalue";

lvalue:
  ID { $$ = new ast::SimpleVar(@$, $1); }
|        ID DOT ID {
    auto sv = new ast::SimpleVar(@$, $1);
    auto fv = new ast::FieldVar(@$, $3, sv);
    $$ = fv;
  }
| lvalue_fv DOT ID {
    auto fv = $1;
    auto fv2 = new ast::FieldVar(@$, $3, fv);
    $$ = fv2;
  }
| lvalue_sc DOT ID {
    auto sc = $1;
    auto fv = new ast::FieldVar(@$, $3, sc);
    $$ = fv;
  }
|        ID LBRACK exp RBRACK {
    auto sv = new ast::SimpleVar(@$, $1);
    auto sc = new ast::SubscriptVar(@$, sv, $3);
    $$ = sc;
  }
| lvalue_fv LBRACK exp RBRACK {
    auto fv = $1;
    auto sc = new ast::SubscriptVar(@$, fv, $3);
    $$ = sc;
  }
| lvalue_sc LBRACK exp RBRACK {
    auto sc = $1;
    auto sc2 = new ast::SubscriptVar(@$, sc, $3);
    $$ = sc2;
  }

| CAST LPAREN lvalue COMMA ty RPAREN
| LVALUE LPAREN INT RPAREN {
    $$ = metavar<ast::Var>(tp, (unsigned) $3);
  }
;

lvalue_fv:
         ID DOT ID {
    auto sv = new ast::SimpleVar(@$, $1);
    auto fv = new ast::FieldVar(@$, $3, sv);
    $$ = fv;
  }
| lvalue_fv DOT ID {
    auto fv = $1;
    auto fv2 = new ast::FieldVar(@$, $3, fv);
    $$ = fv2;
  }
| lvalue_sc DOT ID {
    auto sc = $1;
    auto fv = new ast::FieldVar(@$, $3, sc);
    $$ = fv;
  }
;

lvalue_sc:
         ID LBRACK exp RBRACK {
    auto sv = new ast::SimpleVar(@$, $1);
    auto sc = new ast::SubscriptVar(@$, sv, $3);
    $$ = sc;
  }
| lvalue_fv LBRACK exp RBRACK {
    auto fv = $1;
    auto sc = new ast::SubscriptVar(@$, fv, $3);
    $$ = sc;
  }
| lvalue_sc LBRACK exp RBRACK {
    auto sc = $1;
    auto sc2 = new ast::SubscriptVar(@$, sc, $3);
    $$ = sc2;
  }
;

/*---------------.
| Declarations.  |
`---------------*/

%token DECS "_decs";
%token NAMETY "_namety";

decs:
  %empty { $$ = new ast::DecsList(@$, std::list<ast::Decs*>()); }
| dec decs {
    /*
    auto decslist = $2;
    decslist->push_front($1);
    $$ = decslist;
    */
  }
| DECS LPAREN INT RPAREN decs {
    $$ = metavar<ast::DecsList>(tp, (unsigned) $3);
  }
;

dec:
  /* Type declaration */
  TYPE ID EQ ty { $$ = new ast::TypeDec(@$, $2, $4); }
  /* Class definition (alternative form) */
| CLASS ID LBRACE classfields RBRACE {
    $$ = new ast::TypeDec(@$, $2, new ast::ClassTy(@$, nullptr, $4)); }
| CLASS ID EXTENDS typeid LBRACE classfields RBRACE {
    $$ = new ast::TypeDec(@$, $2, new ast::ClassTy(@$, $4, $6));
  }
  /* Variable declaration */
| vardec { $$ = $1; }
  /* Function declaration */
| FUNCTION ID LPAREN tyfields RPAREN EQ exp {
    $$ = new ast::FunctionDec(@$, $2, $4, nullptr, $7);
  }
| FUNCTION ID LPAREN tyfields RPAREN COLON typeid EQ exp {
    $$ = new ast::FunctionDec(@$, $2, $4, $7, $9);
  }
  /* Primitive declaration */
| PRIMITIVE ID LPAREN tyfields RPAREN {
    $$ = new ast::FunctionDec(@$, $2, $4, nullptr, nullptr);
  }
| PRIMITIVE ID LPAREN tyfields RPAREN COLON typeid {
    $$ = new ast::FunctionDec(@$, $2, $4, $7, nullptr);
  }
  /* Importing a set of declaration */
  /* If this rule is executed, that means the import hasn't been done by
  ** the lexer, and this is an error, but we leave it there for consistency. */
| IMPORT STRING
;

classfields:
  %empty { $$ = new ast::DecsList(@$, std::list<ast::Decs*>()); }
| classfield classfields {
    auto decslist = $2;
    decslist->push_front($1);
    $$ = decslist;
  }
;

classfield:
  vardec {
    auto vect = std::make_shared<std::vector<ast::VarDec*>>();
    vect->push_back($1);
    $$ = new ast::VarDecs(@$, vect.get());
  }
| METHOD ID LPAREN tyfields RPAREN EQ exp {
    auto methodDec = std::make_shared<ast::MethodDec>(@$, $2, $4, nullptr, $7);
    auto vect = std::make_shared<std::vector<ast::MethodDec*>>();
    vect->push_back(methodDec.get());
    $$ = new ast::MethodDecs(@$, vect.get());
  }
| METHOD ID LPAREN tyfields RPAREN COLON typeid EQ exp {
    auto methodDec = std::make_shared<ast::MethodDec>(@$, $2, $4, $7, $9);
    auto vect = std::make_shared<std::vector<ast::MethodDec*>>();
    vect->push_back(methodDec.get());
    $$ = new ast::MethodDecs(@$, vect.get());
  }
;

tyfields:
  %empty
| ID COLON typeid tyfields_tail
;

tyfields_tail:
  %empty
| COMMA ID COLON typeid tyfields_tail
;

typeid:
  ID
| NAMETY LPAREN INT RPAREN
;

vardec:
  VAR ID ASSIGN exp { $$ = new ast::VarDec(@$, $2, nullptr, $4); }
| VAR ID COLON typeid ASSIGN exp { $$ = new ast::VarDec(@$, $2, $4, $6); }
;

ty:
  typeid
| LBRACE tyfields RBRACE
| ARRAY OF typeid
| CLASS LBRACE classfields RBRACE
| CLASS EXTENDS typeid LBRACE classfields RBRACE
;

%%

void
parse::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
  exit(3);
}
