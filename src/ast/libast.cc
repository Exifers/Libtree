/**
 ** \file ast/libast.cc
 ** \brief Public ast interface implementation.
 */

#include <fstream>

#include <ast/libast.hh>
#include <ast/pretty-printer.hh>

// Define exported ast functions.
namespace ast
{
  // Making the following variables const is more than merely
  // stylistic.  If they were not, Swig will create set/get for them,
  // and there is no set (operator=), since it has a const member.

  /// xalloc slot to enable escapes display in Ast display.
  const misc::xalloc<bool> escapes_display;

  // Print the TREE on OSTR.
  std::ostream&
  operator<<(std::ostream& ostr, const Ast& tree)
  {
    PrettyPrinter print(ostr);
    print(tree);
    return ostr;
  }

} // namespace ast
