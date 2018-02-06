/**
 ** \file ast/function-dec.cc
 ** \brief Implementation of ast::FunctionDec.
 */

#include <ast/visitor.hh>
#include <ast/function-dec.hh>

namespace ast
{

  FunctionDec::FunctionDec(const Location& location,
                           const misc::symbol& name, VarDecs* formals,
                           NameTy* result, Exp* body)
    : Dec(location, name)
    , formals_(formals)
    , result_(result)
    , body_(body)
  {}

  FunctionDec::~FunctionDec()
  {
    delete formals_;
    delete result_;
    delete body_;
  }

  void
  FunctionDec::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  FunctionDec::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

