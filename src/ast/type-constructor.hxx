/**
 ** \file ast/type-constructor.hxx
 ** \brief Inline methods of ast::TypeConstructor.
 */

#pragma once

#include <ast/type-constructor.hh>
#include <type/types.hh>

namespace ast
{
  inline void
  TypeConstructor::created_type_set(const type::Type *created_type)
  {
    created_type_ = created_type;
  }

  inline const type::Type *
  TypeConstructor::created_type_get() const
  {
    return created_type_;
  }

} // namespace ast

