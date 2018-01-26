/**
 ** Test the string parser.
 **/

#include <cstdlib>
#include <iostream>

#include <parse/libparse.hh>

const char* program_name = "test-parse";

int
main()
{
  ast::Exp* e = parse::parse("a + b");
}
