/// Test the typing with object extensions.

#include <cstdlib>
#include <iostream>

#include <ast/exp.hh>
#include <ast/decs-list.hh>
#include <ast/libast.hh>
#include <object/libobject.hh>
#include <parse/libparse.hh>

const char* program_name = "test-type";

// Return true on correct typing.
inline static
bool
typed(const std::string& s)
{
  ast::DecsList* d = parse::parse_unit(s, true);
  object::bind(*d);
  misc::error e = object::types_check(*d);
  std::cout << *d << '\n';
  if (e)
    std::cerr << "error-->" << e << '\n';
  delete d;
  return !e;
}


int
main()
{
  ast::bindings_display(std::cout) = true;
  assertion(typed(" let"
                  "   class C"
                  "   {"
                  "     var a := 0"
                  "   }"
                  "   var c := new C"
                  " in"
                  "   c.a := 2"
                  " end"));
  assertion(!typed(" let"
                   "   class C"
                   "   {"
                   "     var a := 0"
                   "   }"
                   "   class D extends C"
                   "   {"
                   "     method print() ="
                   "       self.a"
                   "   }"
                   "   var d := new D"
                   " in"
                   "   d.a := 2;"
                   "   d.print()"
                   " end"));
  assertion(typed(" let"
                  "   class C"
                  "   {"
                  "     var a := 0"
                  "   }"
                  "   class D extends C"
                  "   {"
                  "     method inc_a() ="
                  "       self.a := self.a + 1"
                  "     method add_a(x : int) : int ="
                  "       if x > 0 then"
                  "       ("
                  "         self.inc_a();"
                  "         self.add_a(x - 1)"
                  "       )"
                  "       else"
                  "         self.a"
                  "   }"
                  "   var d : D := new D"
                  " in"
                  "   d.a := 2;"
                  "   d.a := d.add_a(d.a)"
                  " end"));
  assertion(!typed(" let"
                   "   class C extends D"
                   "   {"
                   "     var a := 0"
                   "   }"
                   "   class D extends C"
                   "   {"
                   "     var a := \"string\""
                   "   }"
                   "   var d : D := new D"
                   " in"
                   "   d.a := \"empty\""
                   " end"));
  assertion(!typed(" let"
                   "   class C"
                   "   {"
                   "     var a := 0"
                   "   }"
                   "   class D extends C"
                   "   {"
                   "     method inc_a() ="
                   "       self.a := self.a + 1"
                   "     method add_a(x : int) : int ="
                   "       if x > 0 then"
                   "       ("
                   "         self.inc_a();"
                   "         self.add_a(x - 1)"
                   "       )"
                   "       else"
                   "         self.a"
                   "   }"
                   "   var d : D := new D"
                   " in"
                   "   d.a := 2;"
                   "   d.a := d.a(d.a)"
                   " end"));
}
