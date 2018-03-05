/**
 ** \file escapes/libescapes.cc
 ** \brief Define exported escapes functions.
 */

#include <escapes/escapes-visitor.hh>
#include <escapes/libescapes.hh>

namespace escapes
{

  /** Walk the tree, and set the escape flag of variables and arguments
      if they do escape. */
  void
  escapes_compute(ast::Ast& tree)
  {
    EscapesVisitor escapes_compute;
    escapes_compute(tree);
  }


} // namespace escapes
