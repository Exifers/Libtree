/**
 ** \file ast/simple-var.cc
 ** \brief Implementation of ast::SimpleVar.
 */

#include <ast/visitor.hh>
#include <ast/simple-var.hh>

namespace ast
{

  SimpleVar::SimpleVar(const Location& location, const misc::symbol& name)
    : Var(location)
    , name_(name)
  {}


  void
  SimpleVar::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  SimpleVar::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

