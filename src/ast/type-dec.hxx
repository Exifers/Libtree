/**
 ** \file ast/type-dec.hxx
 ** \brief Inline methods of ast::TypeDec.
 */

#pragma once

#include <ast/type-dec.hh>

namespace ast
{


  inline const Ty&
  TypeDec::ty_get() const
  {
    return *ty_;
  }
  inline Ty&
  TypeDec::ty_get()
  {
    return *ty_;
  }


} // namespace ast

