/**
 ** \file ast/record-exp.hxx
 ** \brief Inline methods of ast::RecordExp.
 */

#pragma once

#include <ast/record-exp.hh>

namespace ast
{
  inline const NameTy&
  RecordExp::namety_get() const
  {
    return *namety_;
  }

  inline NameTy&
  RecordExp::namety_get()
  {
    return *namety_;
  }
} // namespace ast

