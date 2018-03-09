/**
 ** \file object/libobject.hh
 ** \brief Declare functions and variables exported by object module.
 */

#pragma once

#include <ast/fwd.hh>
#include <misc/error.hh>
#include <misc/map.hh>
#include <misc/symbol.hh>
#include <type/class.hh>

namespace object
{

  /*-------.
  | Bind.  |
  `-------*/

  // FIXME: Some code was deleted here.


  /*----------------.
  | Compute types.  |
  `----------------*/

  /** \brief Check types allowing objects.

      \param tree abstract syntax tree's root.

      \return success of the type-checking.  */
  misc::error
  types_check(ast::Ast& tree);


  /*------------------.
  | Desugar objects.  |
  `------------------*/

  /// Names associated to class types.
  using class_names_type = misc::map<const type::Class*, misc::symbol>;

  /// Rename the variables of an AST so that they each have a unique
  /// name, with support for objects.
  ///
  /// \param tree  abstract syntax tree's root, whose bindings and types
  ///              have been computed.
  /// \return      a newly allocated dictionnary of class names
  class_names_type*
  rename(ast::Ast& tree);

  /** \brief Remove objects constructs from an AST.

      \param tree        abstract syntax tree's root, whose bindings
                         and types have been computed, and whose
                         identifiers are all unique.
      \param class_names the names of the class types of the AST

      \return     the desugared, bound and type-checked AST.  */
  template <typename A>
  A*
  desugar(const A& tree, const class_names_type& class_names);

  /** \brief Remove objects constructs from an AST without recomputing
      its bindings nor its types.

      This function acts like object::object_desugar, but stops just
      after the desugaring step (in fact, object::desugar is built
      upon this function).  It is meant to be used as a test of
      DesugarVisitor (i.e., even if the desugared tree is badly bound
      or typed, it can still be pretty-printed).

      \param tree        AST to desugar.
      \param class_names the names of the class types of the AST

      \return            the desugared AST.  */
  template <typename A>
  A*
  raw_desugar(const A& tree, const class_names_type& class_names);


} // namespace object
