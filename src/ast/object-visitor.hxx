/**
 ** \file ast/object-visitor.hxx
 ** \brief Implementation for ast/object-visitor.hh.
 */

#pragma once

#include <misc/contract.hh>
#include <ast/all.hh>
#include <ast/object-visitor.hh>

namespace ast
{

  template <template <typename> class Const>
  GenObjectVisitor<Const>::GenObjectVisitor()
    : GenVisitor<Const>()
  {}

  template <template <typename> class Const>
  GenObjectVisitor<Const>::~GenObjectVisitor()
  {}


  /*-------------------------------.
  | Object-related visit methods.  |
  `-------------------------------*/

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(const_t<ClassTy>& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(const_t<MethodDecs>& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(const_t<MethodDec>& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(const_t<MethodCallExp>& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(const_t<ObjectExp>& e)
  {
  // FIXME: Some code was deleted here.
  }


} // namespace ast
