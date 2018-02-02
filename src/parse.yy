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

%token<int> INT
%token  PLUS        "+"
        MINUS       "-"
        EOF 0       "end of file"
        ARRAY       "array"
        IF          "if"
        THEN        "then"
        ELSE        "else"
        WHILE       "while"
        FOR         "for"
        TO          "to"
        DO          "do"
        LET         "let"
        IN          "in"
        END         "end"
        OF          "of"
        BREAK       "break"
        NIL         "nil"
        FUNCTION    "function"
        VAR         "var"
        TYPE        "type"
        IMPORT      "import"
        PRIMITIVE   "primitive"
        CLASS       "class"
        EXTENDS     "extends"
        METHOD      "method"
        NEW         "new"




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
      INT PLUS exp  { std::cout << $1 << std::endl; }
   |  INT MINUS exp
   |  INT
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
