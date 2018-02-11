/**
 ** \file ast/class-ty.hxx
 ** \brief Inline methods of ast::ClassTy.
 */

#pragma once

#include <ast/class-ty.hh>

namespace ast
{

  inline const NameTy&
  ClassTy::super_get() const
  {
    return *super_;
  }
  inline NameTy&
  ClassTy::super_get()
  {
    return *super_;
  }

  inline const DecsList&
  ClassTy::decs_get() const
  {
    return *decs_;
  }
  inline DecsList&
  ClassTy::decs_get()
  {
    return *decs_;
  }

} // namespace ast

