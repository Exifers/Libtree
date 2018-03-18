/**
 ** \file inlining/libinlining.hh
 ** \brief Declare functions exported by the inlining module.
 */

#pragma once

#include <ast/fwd.hh>
#include <misc/error.hh>

/// Inlining functions of an ast::Ast.
namespace inlining
{

  /*-----------.
  | Inlining.  |
  `-----------*/

  /** Perform inline expansion of function bodies.

      \param tree  abstract syntax tree's root, whose bindings and types
                   have been computed.  Each identifier must also be unique
                   within the AST to avoid name capture.

      \return      the AST where the bodies of non recursive functions have
                   been expanded (inlined), with bindings and type-checked.
  */
  template <typename A>
  A* inline_expand(const A& tree);

  /*-------------------.
  | Function pruning.  |
  `-------------------*/

  /** Prune unused function from the AST.

      \param tree  abstract syntax tree's root, whose bindings and types
                   have been computed, and whose identifiers are all unique.

      \return      the AST whose unused functions have been removed, with
                   bindings and type-checked.  */
  template <typename A>
  A* prune(const A& tree);

} // namespace inlining
