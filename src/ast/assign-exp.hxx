/**
 ** \file ast/assign-exp.hxx
 ** \brief Inline methods of ast::AssignExp.
 */

#pragma once

#include <ast/assign-exp.hh>

namespace ast
{
  inline const Var& AssignExp::lvalue_get() const
  {
    return *lvalue_;
  }

  inline Var& AssignExp::lvalue_get()
  {
    return *lvalue_;
  }

  inline const Exp& AssignExp::exp_get() const
  {
    return *exp_;
  }

  inline Exp& AssignExp::exp_get()
  {
    return *exp_;
  }

} // namespace ast

