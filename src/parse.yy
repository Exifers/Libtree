  /* Prologue */
%language "C++"

%define api.value.type variant
%define api.token.constructor
%locations

%code provides
{
#include <iostream>
yy::parser::symbol_type yylex();
}

%token INTEGER
%token PLUS
%token MINUS

%start exp

%%

  /* Grammar rules */
exp:
      INTEGER PLUS exp
   |  INTEGER MINUS exp
   |  INTEGER
   |  %empty
   ;

%%
  /* Epilogue */

void yy::parser::error(const location_type& loc, const std::string& s)
{
  std::cerr << loc << ": " << s << '\n';
}

int main(void)
{
  yy::parser parser{};
  auto status = parser.parse();
  return status;
}
