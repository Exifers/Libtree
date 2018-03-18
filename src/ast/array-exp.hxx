/**
 ** \file ast/array-exp.hxx
 ** \brief Inline methods of ast::ArrayExp.
 */

#pragma once

#include <ast/array-exp.hh>

namespace ast
{
  inline const NameTy&
  ArrayExp::namety_get() const
  {
    return *namety_;
  }

  inline NameTy&
  ArrayExp::namety_get()
  {
    return *namety_;
  }

  inline const Exp&
  ArrayExp::size_exp_get() const
  {
    return *size_exp_;
  }

  inline Exp&
  ArrayExp::size_exp_get()
  {
    return *size_exp_;
  }

  inline const Exp&
  ArrayExp::type_exp_get() const
  {
    return *type_exp_;
  }

  inline Exp&
  ArrayExp::type_exp_get()
  {
    return *type_exp_;
  }

} // namespace ast
