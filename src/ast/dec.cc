/**
 ** \file ast/dec.cc
 ** \brief Implementation of ast::Dec.
 */

#include <ast/visitor.hh>
#include <ast/dec.hh>

namespace ast
{

  Dec::Dec(const Location& location, const misc::symbol& name)
    : Ast(location)
    , name_(name)
  {}



} // namespace ast

