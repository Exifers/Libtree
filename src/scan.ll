%{
#include <iostream>
%}


%option noyywrap

INTEGER [0-9]+

%%

{INTEGER} {std::cout << "int"; }


%%

int main(void)
{
  return yylex();
}
