/**
 ** \file ast/var.cc
 ** \brief Implementation of ast::Var.
 */

#include <ast/visitor.hh>
#include <ast/var.hh>

namespace ast
{

  Var::Var(const Location& location)
    : Exp(location)
  {}



} // namespace ast

