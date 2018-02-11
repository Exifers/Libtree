/**
 ** \file ast/for-exp.cc
 ** \brief Implementation of ast::ForExp.
 */

#include <ast/visitor.hh>
#include <ast/for-exp.hh>

namespace ast
{

  ForExp::ForExp(const Location& location, VarDec* vardec, Exp* hi,
                 Exp* body)
    : Exp(location)
    , vardec_(vardec)
    , hi_(hi)
    , body_(body)
  {}

  ForExp::~ForExp()
  {
    delete vardec_;
    delete hi_;
    delete body_;
  }

  void
  ForExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  ForExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

