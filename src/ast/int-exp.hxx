/**
 ** \file ast/int-exp.hxx
 ** \brief Inline methods of ast::IntExp.
 */

#pragma once

#include <ast/int-exp.hh>

namespace ast
{


  inline int
  IntExp::value_get() const
  {
    return value_;
  }


} // namespace ast

