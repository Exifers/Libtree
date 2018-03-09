/**
 ** \file type/visitor.hxx
 ** \brief Definition of type::Visitor.
 */

#pragma once

#include <type/type.hh>
#include <type/visitor.hh>

namespace type
{

  template <template <typename> class Const>
  GenVisitor<Const>::~GenVisitor() = default;

  template <template <typename> class Const>
  void
  GenVisitor<Const>::operator()(const_t<Type>& e)
  {
    e.accept(*this);
  }

  template <template <typename> class Const>
  template <class E>
  void
  GenVisitor<Const>::operator()(E* e)
  {
    e->accept(*this);
  }

} // namespace type
