/**
 ** \file ast/dec.hxx
 ** \brief Inline methods of ast::Dec.
 */

#pragma once

#include <ast/dec.hh>

namespace ast
{

  inline const misc::symbol&
  Dec::name_get() const
  {
    return name_;
  }
  inline void
  Dec::name_set(const misc::symbol& name)
  {
    name_ = name;
  }


} // namespace ast

