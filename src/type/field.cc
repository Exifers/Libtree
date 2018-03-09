/**
 ** \file type/field.cc
 ** \brief Implementation for type/field.hh.
 */

#include <ostream>

#include <type/field.hh>

namespace type
{

  Field::Field(misc::symbol name, const Type& type)
    : name_(name)
    , type_(type)
  {}

} // namespace type
