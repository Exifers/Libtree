/**
 ** \file ast/object-exp.hxx
 ** \brief Inline methods of ast::ObjectExp.
 */

#pragma once

#include <ast/object-exp.hh>

namespace ast
{
  inline const NameTy&
  ObjectExp::namety_get() const
  {
    return *namety_;
  }
  
  inline NameTy&
  ObjectExp::namety_get()
  {
    return *namety_;
  }

} // namespace ast

