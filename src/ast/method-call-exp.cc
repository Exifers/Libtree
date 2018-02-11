/**
 ** \file ast/method-call-exp.cc
 ** \brief Implementation of ast::MethodCallExp.
 */

#include <ast/visitor.hh>
#include <ast/method-call-exp.hh>

namespace ast
{
  MethodCallExp::MethodCallExp(const Location& location, NameTy* namety,
      std::list<Exp*> exps,
      std::list<FieldInit*> lvalue)
  : CallExp(location, namety, exps), lvalue_(lvalue)
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

