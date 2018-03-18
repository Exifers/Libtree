/**
 ** \file type/attribute.cc
 ** \brief Implementation for type/attribute.hh.
 */

#include <ostream>

#include <type/attribute.hh>

namespace type
{

  Attribute::Attribute(const ast::VarDec* def)
    : def_(def)
  {}

} // namespace type
