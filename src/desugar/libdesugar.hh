/**
 ** \file desugar/libdesugar.hh
 ** \brief Declare functions exported by the desugar module.
 */

#pragma once

#include <misc/error.hh>

/// Desugaring an ast::Ast.
namespace desugar
{

  /*----------.
  | Helpers.  |
  `----------*/

  /// Recompute the bindings and the types of the AST \a tree.
  ///
  /// Raise an Internal Compiler Error on failure.
  template <typename A>
  void bind_and_types_check(A& tree);


  /*----------.
  | Desugar.  |
  `----------*/

  /** \brief Remove the syntactic sugar from an AST.

      \param tree                 abstract syntax tree's root, whose bindings
                                  and types have been computed, and whose
                                  identifiers are all unique.
      \param desugar_for_p        desugar `for' loops.
      \param desugar_string_cmp_p desugar string comparisons.

      \return the desugared, bound and type-checked AST.  */
  template <typename A>
  A*
  desugar(const A& tree,
          bool desugar_for_p, bool desugar_string_cmp_p);

  /** \brief Remove the syntactic sugar from an AST without
      recomputing its bindings nor its types.

      This function acts like desugar::desugar, but stops just after
      the desugaring step (in fact, desugar::desugar is built upon
      this function).  It is meant to be used as a test of
      DesugarVisitor (i.e., even if the desugared tree is badly bound
      or typed, it can still be pretty-printed).

      \param tree                 AST to desugar.
      \param desugar_for_p        desugar `for' loops.
      \param desugar_string_cmp_p desugar string comparisons.

      \return the desugared AST.  */
  template <typename A>
  A*
  raw_desugar(const A& tree,
              bool desugar_for_p, bool desugar_string_cmp_p);


  /*-----------------------.
  | Array bounds checking.  |
  `-----------------------*/

  /** \brief Add runtime checks of array bounds.

      \param tree abstract syntax tree's root, whose bindings and types
                  have been computed, and whose identifiers are all unique.

      \return the AST with bounds checks, with bindings and type-checked. */

  template <typename A>
  A*
  bounds_checks_add(const A& tree);

  /** \brief Remove the syntactic sugar from an AST without
      recomputing its bindings nor its types.

      This function acts like desugar::bounds_checks_add, but stops
      just after the tranformation step (in fact,
      desugar::bounds_checks_add is built upon this function).  It is
      meant to be used as a test of BoundsCheckingVisitor (i.e., even
      if the tree with bounds checks is badly bound or typed, it can
      still be pretty-printed).

      \param tree AST on which bounds checks are to be added

      \return the AST with bounds checks.  */
  template <typename A>
  A*
  raw_bounds_checks_add(const A& tree);

} // namespace desugar
