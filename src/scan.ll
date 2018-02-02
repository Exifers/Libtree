%option noyywrap

%{
#include <iostream>
%}

SPACE [ \t\n\r]
  /* \r \n \r\n and \n\r are white spaces, if they're ignored, considering
  ** only \n and \r should do the trick.
  */
STRING "\""[^"\""]*"\""
ID ([a-zA-Z][0-9a-zA-Z_]*|"_main")
INTEGER [0-9]+

%%

  /* keywords */
"array" {}
"if" {}
"then" {}
"else" {}
"while" {}
"for" {}
"to" {}
"do" {}
"let" {}
"in" {}
"end" {}
"of" {}
"break" {}
"nil" {}
"function" {}
"var" {}
"type" {}
"import" {}
"primitive" {}

  /* object extension keyword */
"class" {}
"extends" {}
"method" {}
"new" {}

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

  /* Additional */
{STRING} {}
{ID} { }
{INTEGER} {}
{SPACE} {}

. { }

%%
