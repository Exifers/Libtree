/**
 ** Test the string parser.
 **/

#include <cstdlib>
#include <iostream>

#include <ast/libast.hh>
#include <ast/exp.hh>
#include <parse/libparse.hh>

const char* program_name = "test-parse";

int
main()
{
  ast::Exp* e = parse::parse("a + b");
  std::cout << *e << '\n';
  e = parse::parse("let "
                   " function f(a : int, b : string) : int = a "
                   "in a end");
  std::cout << *e << '\n';
}
