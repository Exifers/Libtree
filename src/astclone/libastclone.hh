/**
 ** \file astclone/libastclone.hh
 ** \brief Declare functions and variables exported by the Astclone module.
 */

#pragma once

#include <memory>

#include <ast/fwd.hh>

/// Cloning an ast::Ast.
namespace astclone
{

  /** \brief Make a deep copy of an AST.
   ** \param tree abstract syntax tree's root.
   ** \return the cloned AST.  */
  template <typename T>
  T*
  clone(const T& tree);

  template <typename A>
  using applicable = auto(const A&) -> A*;

  template <typename A>
  using applicable_with_bools = auto(const A&, bool, bool) -> A*;

  template <typename A, typename B>
  using applicable_object = auto(const A&, const B&) -> A*;

  /// Have the pure function \a f side effect on \a t.
  template <typename A>
  void
  apply(applicable<A> f, std::unique_ptr<A>& t1);

  template <typename A>
  void
  apply(applicable_with_bools<A> f, std::unique_ptr<A>& t1, bool cond_1, bool cond_2);

  template <typename A, typename B>
  void
  apply(applicable_object<A, B> f, std::unique_ptr<A>& t1, const B& t3);

} // namespace astclone

#include <astclone/libastclone.hxx>
