/**
 ** \file ast/method-call-exp.cc
 ** \brief Implementation of ast::MethodCallExp.
 */

#include <ast/visitor.hh>
#include <ast/method-call-exp.hh>

namespace ast
{
  MethodCallExp::MethodCallExp(const Location& location,
      misc::symbol name,
      std::list<Exp*> exps,
      Var *lvalue)
  : CallExp(location, name, exps), lvalue_(lvalue)
  {}
  
  void
  MethodCallExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  MethodCallExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

