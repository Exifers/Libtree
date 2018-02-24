/**
 ** \file ast/subscript-var.cc
 ** \brief Implementation of ast::SubscriptVar.
 */

#include <ast/visitor.hh>
#include <ast/subscript-var.hh>

namespace ast
{

  SubscriptVar::SubscriptVar(const Location& location, Var* var,
                             Exp* index)
    : Var(location)
    , var_(var)
    , index_(index)
  {}

  SubscriptVar::~SubscriptVar()
  {
    delete var_;
    delete index_;
  }

  void
  SubscriptVar::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  SubscriptVar::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

