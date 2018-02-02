%option noyywrap

%{
#include <iostream>
#include "parse.hh"

#define YY_USER_ACTION                      \
    loc.columns(yyleng);
#define TOKEN(Type)                         \
    yy::parser::make_ ## Type(loc)
#define TOKEN_VAL(Type, Value)              \
    yy::parser::make_ ## Type(Value, loc)
#define yyterminate()                       \
    yy_delete_buffer(YY_CURRENT_BUFFER);    \
    return TOKEN(EOF);
static yy::location loc;
%}


int             [0-9]+
%x STRING COMMENT

%%
%{
    loc.step();
%}

{int}           {
                    auto val = std::stoi(yytext);
                    return TOKEN_VAL(INT, val);
                }

  /* keywords */
"array"             return TOKEN(ARRAY); 
"if"                return TOKEN(IF);
"then"              return TOKEN(THEN);
"else"              return TOKEN(ELSE);
"while"             return TOKEN(WHILE);
"for"               return TOKEN(FOR);
"to"                return TOKEN(TO);
"do"                return TOKEN(DO);
"let"               return TOKEN(LET);
"in"                return TOKEN(IN);
"end"               return TOKEN(END);
"of"                return TOKEN(OF);
"break"             return TOKEN(BREAK);
"nil"               return TOKEN(NIL);
"function"          return TOKEN(FUNCTION);
"var"               return TOKEN(VAR);
"type"              return TOKEN(TYPE);
"import"            return TOKEN(IMPORT);
"primitive"         return TOKEN(PRIMITIVE);

  /* object extension keyword */
"class"             return TOKEN(CLASS);
"extends"           return TOKEN(EXTENDS);
"method"            return TOKEN(METHOD);
"new"               return TOKEN(NEW);

  /* Symbols */
"," {}
":" {}
";" {}
"(" {}
")" {}
"[" {}
"]" {}
"{" {}
"}" {}
"." {}
"+" {}
"-" {}
"*" {}
"/" {}
"=" {}
"<>" {}
"<" {}
"<=" {}
">" {}
">=" {}
"&" {}
"|" {}
":=" {}

<<<<<<< HEAD
  /* Additional */
{STRING} { }
{ID} { }
{INTEGER} { std::cout << "integer\n"; }
{SPACE} { }

=======
>>>>>>> b4a7a8c00997d6e5ebc15730d029776d1a130340
. { }

<<EOF>> return yy::parser::make_EOF(loc);

%%
