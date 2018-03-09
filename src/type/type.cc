/**
 ** \file type/type.cc
 ** \brief Implementation for type/type.hh.
 */

#include <ostream>

#include <type/type.hh>

namespace type
{

  const Type&
  Type::actual() const
  {
    return *this;
  }

  bool
  Type::compatible_with(const Type& other) const
  {
    return *this == other;
  }

  const misc::xalloc<bool> hide_actual_types;

} // namespace type
