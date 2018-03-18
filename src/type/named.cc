/**
 ** \file type/named.cc
 ** \brief Implementation for type/named.hh.
 */

#include <ostream>
#include <set>

#include <type/named.hh>
#include <type/visitor.hh>

namespace type
{

  Named::Named(misc::symbol name)
    : name_(name)
    , type_(nullptr)
  {}

  Named::Named(misc::symbol name, const Type* type)
    : name_(name)
  {
    type_set(type);
  }

#warning // FIXME: Some code was deleted here (Inherited functions).

#warning // FIXME: Some code was deleted here (Sound).

#warning // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Named).

} // namespace type
