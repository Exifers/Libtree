/**
 ** \file ast/ast.hxx
 ** \brief Inline methods of ast::Ast.
 */

#pragma once

#include <ast/ast.hh>

namespace ast
{

  inline const Location&
  Ast::location_get() const
  {
    return location_;
  }
  inline void
  Ast::location_set(const Location& location)
  {
    location_ = location;
  }


} // namespace ast

