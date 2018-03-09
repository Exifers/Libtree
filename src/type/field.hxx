/**
 ** \file type/field.hxx
 ** \brief Inline methods for type::Field.
 */
#pragma once

#include <misc/contract.hh>
#include <type/field.hh>

namespace type
{

  inline misc::symbol
  Field::name_get() const
  {
    return name_;
  }

  inline const Type&
  Field::type_get() const
  {
    return type_;
  }

} // namespace type
