/**
 ** \file type/record.hxx
 ** \brief Inline methods for type::Record.
 */
#pragma once

#include <misc/contract.hh>
#include <type/record.hh>

namespace type
{

  inline const Record::fields_type&
  Record::fields_get() const
  {
    return fields_;
  }

  inline void
  Record::field_add(const Field& field)
  {
    fields_.emplace_back(field);
  }

  inline void
  Record::field_add(const misc::symbol name, const Type& type)
  {
    fields_.emplace_back(name, type);
  }

  inline Record::const_iterator
  Record::begin() const
  {
    return fields_.begin();
  }

  inline Record::const_iterator
  Record::end() const
  {
    return fields_.end();
  }

} // namespace type
