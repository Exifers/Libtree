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
    e.super_get().accept(*this);
    e.decs_get().accept(*this);
  }

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(const_t<MethodDecs>& e)
  {
    auto v = e.decs_get();
    for (auto it = v.begin(); it != v.end(); it++)
      (*it)->accept(*this);
  }

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(const_t<MethodDec>& e)
  {
    e.formals_get().accept(*this);
    e.result_get()->accept(*this);
    e.body_get()->accept(*this);
  }

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(const_t<MethodCallExp>& e)
  {
    e.lvalue_get().accept(*this);
  }

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(const_t<ObjectExp>& e)
  {
    e.namety_get().accept(*this);
  }

} // namespace ast
