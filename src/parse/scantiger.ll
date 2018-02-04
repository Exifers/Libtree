%option noyywrap

%{
#include <iostream>
#include "parsetiger.hh"
yy::parser::location_type loc;

#define YY_USER_ACTION    \
  do {                    \
    loc.columns(yyleng);  \
  } while(false);
%}

SPACE [ \t]
STRING "\""[^"\""]*"\""
ID ([a-zA-Z][0-9a-zA-Z_]*|"_main")
INTEGER [0-9]+

%%
  loc.step();

  /* keywords */
"array" { return yy::parser::make_ARRAY(loc); }
"if" { return yy::parser::make_IF(loc); }
"then" { return yy::parser::make_THEN(loc); }
"else" { return yy::parser::make_ELSE(loc); }
"while" { return yy::parser::make_WHILE(loc); }
"for" { return yy::parser::make_FOR(loc); }
"to" { return yy::parser::make_TO(loc); }
"do" { return yy::parser::make_DO(loc); }
"let" { return yy::parser::make_LET(loc); }
"in" { return yy::parser::make_IN(loc); }
"end" { return yy::parser::make_END(loc); }
"of" { return yy::parser::make_OF(loc); }
"break" { return yy::parser::make_BREAK(loc); }
"nil" { return yy::parser::make_NIL(loc); }
"function" { return yy::parser::make_FUNCTION(loc); }
"var" { return yy::parser::make_VAR(loc); }
"type" { return yy::parser::make_TYPE(loc); }
"import" { return yy::parser::make_IMPORT(loc); }
"primitive" { return yy::parser::make_PRIMITIVE(loc); }

  /* object extension keyword */
"class" { return yy::parser::make_CLASS(loc); }
"extends" { return yy::parser::make_EXTENDS(loc); }
"method" { return yy::parser::make_METHOD(loc); }
"new" { return yy::parser::make_NEW(loc); }

  /* Symbols */
"," { return yy::parser::make_COMMA(loc); }
":" { return yy::parser::make_COLON(loc); }
";" { return yy::parser::make_SEMICOLON(loc); }
"(" { return yy::parser::make_OPAR(loc); }
")" { return yy::parser::make_CPAR(loc); }
"[" { return yy::parser::make_OBRA(loc); }
"]" { return yy::parser::make_CBRA(loc); }
"{" { return yy::parser::make_OCBRA(loc); }
"}" { return yy::parser::make_CCBRA(loc); }
"." { return yy::parser::make_POINT(loc); }
"+" { return yy::parser::make_PLUS(loc); }
"-" { return yy::parser::make_MINUS(loc); }
"*" { return yy::parser::make_TIMES(loc); }
"/" { return yy::parser::make_SLASH(loc); }
"=" { return yy::parser::make_EQUAL(loc); }
"<>" { return yy::parser::make_NEQUAL(loc); }
"<" { return yy::parser::make_LESST(loc); }
"<=" { return yy::parser::make_LESSE(loc); }
">" { return yy::parser::make_MORET(loc); }
">=" { return yy::parser::make_MOREE(loc); }
"&" { return yy::parser::make_AND(loc); }
"|" { return yy::parser::make_OR(loc); }
":=" { return yy::parser::make_ASSIGN(loc); }

  /* Additional */
{STRING} { return yy::parser::make_STRING(loc); }
{ID} { return yy::parser::make_ID(loc); }
{INTEGER} { return yy::parser::make_INTEGER(strtol(yytext, nullptr, 0), loc); }
{SPACE}   { }

<<EOF>> return yy::parser::make_EOF(loc);
\n        { loc.lines(yyleng); }
.         {
            std::cerr << "Unexpected character : " << yytext << std::endl; 
            num_errors += 1;
            std::exit(1); /* TODO check subject for exit status */
          }
%%
