/**
 ** \file ast/ast.cc
 ** \brief Implementation of ast::Ast.
 */

#include <ast/visitor.hh>
#include <ast/ast.hh>

namespace ast
{

  Ast::Ast(const Location& location)
    : location_(location)
  {}



} // namespace ast

