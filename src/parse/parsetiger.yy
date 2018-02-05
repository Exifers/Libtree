%require "3.0"
%language "C++"
%name-prefix "parse"
%define api.value.type variant
%define api.token.constructor
%skeleton "lalr1.cc"
%expect 1
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

%printer { yyo << $$; } <int> <std::string> <misc::symbol>;

%token <std::string>    STRING "string"
%token <misc::symbol>   ID     "identifier"
%token <int>            INT    "integer"



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

%right "array_of"
%right "assign"
%right "if_then"
%right "if_then_else"
%right "while"
%right "for"

%start program

%%

  /* Hint : non terminals are in lower case, terminals in upper case */

program: exp   {}
       | decs  {}
       ;

exp:
  /* Literals */
  NIL          {}
| INT          {}
| STRING       {}
  /* Array and record creation */
| ID LBRACK exp RBRACK OF exp              %prec "array_of"
| ID LBRACE RBRACE
| ID LBRACE rec_init_list RBRACE
  /* Object creation */
| NEW ID
  /* Variables, field, element of an array */
| lvalue
  /* Function call */
| ID LPAREN RPAREN
| ID LPAREN exp_comma_list RPAREN
  /* Method call */
| method_body LPAREN RPAREN
| method_body LPAREN exp_comma_list RPAREN
  /* Operations */
| MINUS exp
| exp_binary_operations
| LPAREN exps RPAREN
  /* Assignment */
| lvalue ASSIGN exp                    %prec "assign"
  /* Control structures */
| IF exp THEN exp                      %prec "if_then"
| IF exp THEN exp ELSE exp             %prec "if_then_else"
| WHILE exp DO exp                     %prec "while"
| FOR ID ASSIGN exp TO exp DO exp      %prec "for"
| BREAK
| LET decs IN exps END
;

exps:
  %empty
| exp_semicolon_list
;

exp_semicolon_list:
  exp
| exp SEMI exp_semicolon_list
;

exp_binary_operations:
  exp PLUS exp
| exp MINUS exp
| exp TIMES exp
| exp DIVIDE exp
| exp EQ exp
| exp NE exp
| exp LT exp
| exp LE exp
| exp GT exp
| exp GE exp 
| exp AND exp
| exp OR exp
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

%token DECS "_decs";

decs:
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


/*---------------.
| Declarations.  |
`---------------*/

%%

void
parse::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}
