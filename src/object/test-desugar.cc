/// Checking the removal of object constructs.

#include <cstdlib>
#include <iostream>

#include <ast/decs-list.hh>
#include <ast/exp.hh>
#include <ast/libast.hh>
#include <bind/libbind.hh>
#include <object/desugar-visitor.hh>
#include <object/libobject.hh>
#include <parse/libparse.hh>
#include <type/libtype.hh>


const char* program_name = "test-desugar";

int
main()
{
  std::cout << "/* Test 1.  */\n";
}
