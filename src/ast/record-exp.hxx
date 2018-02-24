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

  inline const std::list<VarDec*>&
  RecordExp::fields_get() const
  {
    return fields_;
  }

  inline std::list<VarDec*>&
  RecordExp::fields_get()
  {
    return fields_;
  }
} // namespace ast

