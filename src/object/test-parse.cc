/// Test the parser with object extensions.

#include <cstdlib>
#include <iostream>

#include <ast/exp.hh>
#include <ast/decs-list.hh>
#include <ast/libast.hh>
#include <object/libobject.hh>
#include <parse/libparse.hh>

const char* program_name = "test-parse";

int
main()
{
  // Canonical syntax.
  ast::Exp* e1 = parse::parse(" let"
                              "   class C extends Object"
                              "   {"
                              "     var a := 42"
                              "     method print() = print_int(a)"
                              "   }"
                              "   var c := new C"
                              " in"
                              "   c.a := 51;"
                              "   c.print()"
                              " end",
                              true);
  std::cout << *e1 << '\n';
  delete e1;

  // Alternative syntax.
  ast::Exp* e2 = parse::parse(" let"
                              "   type C = class extends Object"
                              "   {"
                              "     var a := 42"
                              "     method print() = print_int(a)"
                              "   }"
                              "   var c := new C"
                              " in"
                              "   c.a := 51;"
                              "   c.print()"
                              " end",
                              true);
  std::cout << *e2 << '\n';
  delete e2;
}
