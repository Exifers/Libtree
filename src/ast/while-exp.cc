/**
 ** \file ast/while-exp.cc
 ** \brief Implementation of ast::WhileExp.
 */

#include <ast/visitor.hh>
#include <ast/while-exp.hh>

namespace ast
{

  WhileExp::WhileExp(const Location& location, Exp* test, Exp* body)
    : Exp(location)
    , test_(test)
    , body_(body)
  {}

  WhileExp::~WhileExp()
  {
    delete test_;
    delete body_;
  }

  void
  WhileExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  WhileExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

