  /* Prologue */
%language "C++"

%define api.value.type variant
%define api.token.constructor
%define api.token.prefix {TOK_}
%define parse.error verbose
%define parse.trace
%locations

%param {int& num_errors}

%code provides
{
#include <iostream>
#define YY_DECL yy::parser::symbol_type yylex(int& num_errors)
YY_DECL;
}

%token<int> INTEGER
%token PLUS "+"
%token MINUS "-"
%token EOF 0 "end of file"

%start file

%nterm <int> exp
%printer { yyo << $$; } <int>;

%%

  /* Grammar rules */
file:
	  exp file
	| EOF
  ;

exp:
      INTEGER PLUS exp  { std::cout << $1 << std::endl; }
   |  INTEGER MINUS exp
   |  INTEGER
   ;

%%
  /* Epilogue */

void yy::parser::error(const location_type& loc, const std::string& s)
{
  std::cerr << loc << ": " << s << '\n';
}

int main(void)
{
  auto num_errors = 0;
  yy::parser parser(num_errors);
  extern int yy_flex_debug;
  if (getenv("YYDEBUG"))
    parser.set_debug_level(1);
  auto status = parser.parse();
  return status;
}
