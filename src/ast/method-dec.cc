/**
 ** \file ast/method-dec.cc
 ** \brief Implementation of ast::MethodDec.
 */

#include <ast/visitor.hh>
#include <ast/method-dec.hh>

namespace ast
{

  MethodDec::MethodDec(const Location& location, const misc::symbol& name,
                       VarDecs* formals, NameTy* result, Exp* body)
    : FunctionDec(location, name, formals, result, body)
  {}


  void
  MethodDec::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  MethodDec::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

