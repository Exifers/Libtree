/**
 ** Checking string comparisons desugaring.
 */

#include <ostream>
#include <string>

#include <ast/all.hh>
#include <ast/libast.hh>
#include <desugar/desugar-visitor.hh>
#include <misc/file-library.hh>
#include <parse/libparse.hh>
#include <type/type-checker.hh>
#include <type/types.hh>

using namespace ast;
using namespace desugar;

const char* program_name = "test-string-cmp-desugar";

static
void
test_string_desugaring(const std::string& oper)
{
  Exp* tree = parse::parse
    ("let primitive streq(s1 : string, s2 : string) : int\n"
     "   primitive strcmp(s1 : string, s2 : string) : int\n"
     "in\n"
     "  (\"foo\" " + oper + " \"bar\")\n"
     "end\n");
  type::TypeChecker type;
  type(tree);

  std::cout << "/* === Original tree...  */\n"
            << *tree << '\n';

  DesugarVisitor desugar(false, true);
  tree->accept(desugar);
  delete tree;
  tree = nullptr;
  std::cout << "/* === Desugared tree...  */\n"
            << *desugar.result_get() << '\n';
  delete desugar.result_get();
}

int
main()
{
  // Desugaring `"foo" = "bar"' as `streq("foo", "bar")'.
  std::cout << "First test...\n";
  test_string_desugaring("=");
  std::cout << std::endl;

  // Desugaring `"foo" <> "bar"' as `streq("foo", "bar") = 0'.
  std::cout << "Second test...\n";
  test_string_desugaring("<>");
  std::cout << std::endl;

  // Desugaring `"foo" >= "bar"' as `strcmp("foo", "bar") >= 0'.
  std::cout << "Third test...\n";
  test_string_desugaring(">=");
}
