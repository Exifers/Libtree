%language "C++"
%define api.value.type variant
%define api.token.constructor
%define api.token.prefix {TOK_}
%define parse.error verbose
%define parse.trace
%locations

%param { int& num_errors }

%code provides
{
#define YY_DECL yy::parser::symbol_type yylex(int& num_errors)
YY_DECL;
}

%{
  #include <iostream>
  void yyerror(const char *);
%}

  /* regexes */
%token STRING
%token ID
%token<int> INTEGER

  /* keywords */
%token ARRAY
%token IF
%token THEN
%token ELSE
%token WHILE
%token FOR
%token TO
%token DO
%token LET
%token IN
%token END
%token OF
%token BREAK
%token NIL
%token FUNCTION
%token VAR
%token TYPE
%token IMPORT
%token PRIMITIVE

  /* object extension keyword */
%token CLASS
%token EXTENDS
%token METHOD
%token NEW

  /* Symbols */
%token COMMA ","
%token COLON ":"
%token SEMICOLON ";"
%token OPAR "("
%token CPAR ")"
%token OBRA "["
%token CBRA "]"
%token OCBRA "{"
%token CCBRA "}"
%token POINT "."
%token PLUS "+"
%token MINUS "-"
%token TIMES "*"
%token SLASH "/"
%token EQUAL "="
%token NEQUAL "<>"
%token LESST "<"
%token LESSE "<="
%token MORET ">"
%token MOREE ">="
%token AND "&"
%token OR "|"
%token ASSIGN ":="

%token EOF 0 "end of file"

%printer { yyo << $$; } <int>;


  /* TODO check operator priority on these from subject */
%left AND OR
%left EQUAL NEQUAL
%left LESST LESSE MORET MOREE
%left PLUS MINUS
%left TIMES SLASH

%right "array_of"
%right "assign"
%right "if_then"
%right "if_then_else"
%right "while"
%right "for"

%expect 1 /* Can't figure out how to solve it XD */

%%

  /* Hint : non terminals are in lower case, terminals in upper case */

program: exp   {}
       | decs  {}
       ;

exp:
  /* Literals */
  NIL          {}
| INTEGER      {}
| STRING       {}
  /* Array and record creation */
| ID OBRA exp CBRA OF exp              %prec "array_of"
| ID OCBRA CCBRA
| ID OCBRA rec_init_list CCBRA
  /* Object creation */
| NEW ID
  /* Variables, field, element of an array */
| lvalue
  /* Function call */
| ID OPAR CPAR
| ID OPAR exp_comma_list CPAR
  /* Method call */
| method_body OPAR CPAR
| method_body OPAR exp_comma_list CPAR
  /* Operations */
| MINUS exp
| exp_binary_operations
| OPAR exps CPAR
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
| exp SEMICOLON exp_semicolon_list
;

exp_binary_operations:
  exp PLUS exp
| exp MINUS exp
| exp TIMES exp
| exp SLASH exp
| exp EQUAL exp
| exp NEQUAL exp
| exp LESST exp
| exp LESSE exp
| exp MORET exp
| exp MOREE exp 
| exp AND exp
| exp OR exp
;

method_body:
  ID method_spec
;

method_spec:
  POINT ID method_spec_tail
| OBRA exp CBRA POINT ID method_spec_tail
;

method_spec_tail:
  %empty
| POINT ID method_spec_tail
| OBRA exp CBRA POINT ID method_spec_tail
;

exp_comma_list:
  exp
| exp COMMA exp_comma_list
;

rec_init_list:
  ID EQUAL exp
| ID EQUAL exp COMMA rec_init_list
;

lvalue:
  ID lvalue_follow
;

lvalue_follow:
  %empty
| POINT ID lvalue_follow
| OBRA exp CBRA lvalue_follow
;

decs:
	%empty
| dec decs
;

dec:
  /* Type declaration */
  TYPE ID EQUAL ty
  /* Class definition (alternative form) */
| CLASS ID OCBRA classfields CCBRA
| CLASS ID EXTENDS typeid OCBRA classfields CCBRA
  /* Variable declaration */
| vardec
  /* Function declaration */
| FUNCTION ID OPAR tyfields CPAR EQUAL exp
| FUNCTION ID OPAR tyfields CPAR COLON typeid EQUAL exp
  /* Primitive declaration */
| PRIMITIVE ID OPAR tyfields CPAR
| PRIMITIVE ID OPAR tyfields CPAR COLON typeid
  /* Importing a set of declaration */
| IMPORT STRING 
;

classfields:
  %empty
| classfield classfields
;

classfield:
  vardec
| METHOD ID OPAR tyfields CPAR EQUAL exp
| METHOD ID OPAR tyfields CPAR COLON typeid EQUAL exp
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
| OCBRA tyfields CCBRA
| ARRAY OF typeid
| CLASS OCBRA classfields CCBRA
| CLASS EXTENDS typeid OCBRA classfields CCBRA
;

%%

void yy::parser::error(const location_type& loc, const std::string& s)
{
  num_errors += 1;
  std::cerr << loc << ": " << s << std::endl;
}

int main(void)
{
  auto num_errors = 0;
  yy::parser parser(num_errors);
  extern int yy_flex_debug;

  if (getenv("YYDEBUG"))
    parser.set_debug_level(1);

  auto status = parser.parse();
  return status || num_errors;
}
