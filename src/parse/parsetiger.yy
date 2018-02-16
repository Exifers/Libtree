%require "3.0"
%language "C++"
%name-prefix "parse"
%define api.value.type variant
%define api.token.constructor
%skeleton "glr.cc"
%glr-parser
%expect 1
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

%nterm <std::list<ast::Exp*>> exps
%nterm <std::list<ast::Exp*>> exp_semicolon_list

  /* TODO check operator priority on these from subject */
%left AND OR
%left EQ NE
%left LT LE GT GE
%left PLUS MINUS
%left TIMES DIVIDE

%right "array_of"
%right "assign"
%right "if_then"
%right "if_then_else"
%right "while"
%right "for"

%type <ast::Exp*> exp
%type <ast::DecsList*> decs


%start program

%%

  /* Hint : non terminals are in lower case, terminals in upper case */

program: exp   { tp.ast_ = $1; }
       | decs  { tp.ast_ = $1; }
       ;

exp:
  /* Literals */
  NIL          { $$ = new ast::NilExp(@$); }
| INT          { $$ = new ast::IntExp(@$, $1); }
| STRING       { $$ = new ast::StringExp(@$, $1); }

  /* Array and record creation */
| ID LBRACK exp RBRACK OF exp  {
    $$ = new ast::ArrayExp(@$, new ast::NameTy(@$, $1), $3, $6);
  } %prec "array_of"

| ID LBRACE RBRACE {
    $$ = new ast::RecordExp(@$, new ast::NameTy(@$, $1), std::list<ast::VarDec*>());
  }
| ID LBRACE rec_init_list RBRACE {
    $$ = new ast::RecordExp(@$, new ast::NameTy(@$, $1), std::list<ast::VarDec*>());
  }
  /* Object creation */
| NEW ID { $$ = new ast::ObjectExp(@$, new ast::NameTy(@$, $2)); }
  /* Variables, field, element of an array */
| lvalue {
    $$ = new ast::SeqExp(@$, std::list<ast::FieldInit*>());
  }
  /* Function call */
| ID LPAREN RPAREN { 
    $$ = new ast::CallExp(@$, new ast::NameTy(@$, $1), std::list<ast::Exp*>());
  }
| ID LPAREN exp_comma_list RPAREN {
    $$ = new ast::CallExp(@$, new ast::NameTy(@$, $1), std::list<ast::Exp*>());
  }
  /* Method call */
| method_body LPAREN RPAREN
| method_body LPAREN exp_comma_list RPAREN
  /* Operations */
| MINUS exp

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

| LPAREN exps RPAREN
  /* Assignment */
| lvalue ASSIGN exp                                       %prec "assign"

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
  exp {  }
| exp SEMI exp_semicolon_list { }
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
  exp
| exp COMMA exp_comma_list
;

rec_init_list:
  ID EQ exp
| ID EQ exp COMMA rec_init_list
;

lvalue:
  ID lvalue_follow
;

lvalue_follow:
  %empty
| DOT ID lvalue_follow
| LBRACK exp RBRACK lvalue_follow
;

/*---------------.
| Declarations.  |
`---------------*/

%token DECS "_decs";

decs: { $$ = new ast::DecsList(@$); }
  %empty
| dec decs
;

dec:
  /* Type declaration */
  TYPE ID EQ ty
  /* Class definition (alternative form) */
| CLASS ID LBRACE classfields RBRACE
| CLASS ID EXTENDS typeid LBRACE classfields RBRACE
  /* Variable declaration */
| vardec
  /* Function declaration */
| FUNCTION ID LPAREN tyfields RPAREN EQ exp
| FUNCTION ID LPAREN tyfields RPAREN COLON typeid EQ exp
  /* Primitive declaration */
| PRIMITIVE ID LPAREN tyfields RPAREN
| PRIMITIVE ID LPAREN tyfields RPAREN COLON typeid
  /* Importing a set of declaration */
| IMPORT STRING
;

classfields:
  %empty
| classfield classfields
;

classfield:
  vardec
| METHOD ID LPAREN tyfields RPAREN EQ exp
| METHOD ID LPAREN tyfields RPAREN COLON typeid EQ exp
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
;

vardec:
  VAR ID ASSIGN exp
| VAR ID COLON typeid ASSIGN exp
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
