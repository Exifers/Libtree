/**
 ** \file ast/method-call-exp.hxx
 ** \brief Inline methods of ast::MethodCallExp.
 */

#pragma once

#include <ast/method-call-exp.hh>

namespace ast
{
  inline const Var&
  MethodCallExp::lvalue_get() const
  {
    return *lvalue_;
  }

  inline Var&
  MethodCallExp::lvalue_get()
  {
    return *lvalue_;
  }

} // namespace ast

