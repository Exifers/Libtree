/**
 ** \file ast/seq-exp.hxx
 ** \brief Inline methods of ast::SeqExp.
 */

#pragma once

#include <ast/seq-exp.hh>

namespace ast
{
  inline const std::list<FieldInit*>
  SeqExp::lvalue_get() const
  {
    return lvalue_;
  }

  inline std::list<FieldInit*>
  SeqExp::lvalue_get()
  {
    return lvalue_;
  }
} // namespace ast

