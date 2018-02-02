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
| type-id OBRA exp CBRA OF exp
;

decs: ARRAY    {}

type-id: ID    {}


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
