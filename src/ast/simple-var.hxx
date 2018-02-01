/**
 ** \file ast/simple-var.hxx
 ** \brief Inline methods of ast::SimpleVar.
 */

#pragma once

#include <ast/simple-var.hh>

namespace ast
{


  inline const misc::symbol&
  SimpleVar::name_get() const
  {
    return name_;
  }
  inline void
  SimpleVar::name_set(const misc::symbol& name)
  {
    name_ = name;
  }

  inline const VarDec*
  SimpleVar::def_get() const
  {
    return def_;
  }
  inline VarDec*
  SimpleVar::def_get()
  {
    return def_;
  }
  inline void
  SimpleVar::def_set(VarDec* def)
  {
    def_ = def;
  }


} // namespace ast

