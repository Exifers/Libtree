/**
 ** \file ast/call-exp.hxx
 ** \brief Inline methods of ast::CallExp.
 */

#pragma once

#include <ast/call-exp.hh>

namespace ast
{

  inline const NameTy&
  CallExp::namety_get() const
  {
    return *namety_;
  }

  inline NameTy&
  CallExp::namety_get()
  {
    return *namety_;
  }

  inline const std::list<Exp*>&
  CallExp::exps_get() const
  {
    return exps_;
  }

  inline std::list<Exp*>&
  CallExp::exps_get()
  {
    return exps_;
  }

} // namespace ast

