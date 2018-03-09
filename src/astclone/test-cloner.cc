/**
 ** Checking astclone::Cloner.
 */

#include <list>
#include <ostream>

#include <astclone/cloner.hh>
#include <ast/libast.hh>
#include <misc/file-library.hh>
#include <parse/libparse.hh>

using namespace ast;
using namespace astclone;

const char* program_name = "test-cloner";

static
void
clone_ast(const std::string& s)
{
  ast::Exp* e = parse::parse(s);

  std::cout << *e << '\n';

  Cloner clone;
  clone(e);
  delete e;
  std::cout << *clone.result_get() << '\n';
  delete clone.result_get();
}

int
main()
{
  std::cout << "First test...\n";
  clone_ast("( (a := 5); (a + 1) )");

  std::cout << "Second test...\n";
  clone_ast("let function f() : int = g(a) in f() end");
}
