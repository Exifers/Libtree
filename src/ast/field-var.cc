/**
 ** \file ast/field-var.cc
 ** \brief Implementation of ast::FieldVar.
 */

#include <ast/visitor.hh>
#include <ast/field-var.hh>

namespace ast
{

  FieldVar::FieldVar(const Location& location,
    const misc::symbol& name, Var *var)
    : Var(location), name_(name), var_(var)
  {}

  void FieldVar::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void FieldVar::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

