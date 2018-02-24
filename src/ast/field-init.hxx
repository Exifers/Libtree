/**
 ** \file ast/field-init.hxx
 ** \brief Inline methods of ast::FieldInit.
 */

#pragma once

#include <ast/field-init.hh>

namespace ast
{


  inline const misc::symbol&
  FieldInit::name_get() const
  {
    return name_;
  }
  inline void
  FieldInit::name_set(const misc::symbol& name)
  {
    name_ = name;
  }

  inline const Exp&
  FieldInit::init_get() const
  {
    return *init_;
  }
  inline Exp&
  FieldInit::init_get()
  {
    return *init_;
  }


} // namespace ast

