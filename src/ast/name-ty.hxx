/**
 ** \file ast/name-ty.hxx
 ** \brief Inline methods of ast::NameTy.
 */

#pragma once

#include <ast/name-ty.hh>

namespace ast
{


  inline const misc::symbol&
  NameTy::name_get() const
  {
    return name_;
  }
  inline void
  NameTy::name_set(const misc::symbol& name)
  {
    name_ = name;
  }

  inline const TypeDec*
  NameTy::def_get() const
  {
    return def_;
  }
  inline TypeDec*
  NameTy::def_get()
  {
    return def_;
  }
  inline void
  NameTy::def_set(TypeDec* def)
  {
    def_ = def;
  }


} // namespace ast

