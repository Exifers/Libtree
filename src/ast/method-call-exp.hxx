/**
 ** \file ast/method-call-exp.hxx
 ** \brief Inline methods of ast::MethodCallExp.
 */

#pragma once

#include <ast/method-call-exp.hh>

namespace ast
{
  inline const std::list<FieldInit*>
  MethodCallExp::lvalue_get() const
  {
    return lvalue_;
  }

  inline std::list<FieldInit*>
  MethodCallExp::lvalue_get()
  {
    return lvalue_;
  }

} // namespace ast

