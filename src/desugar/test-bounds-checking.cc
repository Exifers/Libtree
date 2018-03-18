// Checking bounds checking.

#include <ostream>
#include <string>

#include <ast/all.hh>
#include <ast/libast.hh>
#include <bind/libbind.hh>
#include <desugar/bounds-checking-visitor.hh>
#include <parse/libparse.hh>
#include <type/libtype.hh>

using namespace ast;
using namespace desugar;

const char* program_name = "test-bounds-checking";

static
void
test_bounds_checking(ast::Ast& tree)
{
  bind::bind(tree);
  type::types_check(tree);
  std::cout << "/* === Original tree...  */\n"
            << tree << '\n';

  BoundsCheckingVisitor bounds_checks_add;
  bounds_checks_add(tree);

  std::cout << "/* === AST with bounds checks...  */\n"
            << *bounds_checks_add.result_get() << '\n';
  delete bounds_checks_add.result_get();
  std::cout << std::endl;
}

int
main()
{
  // Minimal built-in function requirements.
  std::string builtins =
    " primitive print_err(string: string)"
    " primitive exit(status: int)"

    " type strings = array of string"
    " var forty_twos := strings [42] of \"forty-two\"";

  // A single exp.
  {
    std::cout << "First test...\n";
    Exp* tree = parse::parse(parse::Tweast() <<
                             " let" <<
                             "   " << builtins <<
                             " in" <<
                             "   forty_twos[0]" <<
                             " end");
    test_bounds_checking(*tree);
    delete tree;
    tree = nullptr;
  }

  // Using a _main function.
  {
    std::cout << "Second test...\n";
    DecsList* tree = parse::parse(parse::Tweast() <<
                                  builtins <<
                                  " function _main() ="
                                  "   ("
                                  "     forty_twos[0];"
                                  "     ()"
                                  "   )");
    test_bounds_checking(*tree);
    delete tree;
    tree = nullptr;
  }
}
