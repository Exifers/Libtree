/**
 ** \file ast/let-exp.cc
 ** \brief Implementation of ast::LetExp.
 */

#include <ast/visitor.hh>
#include <ast/let-exp.hh>

namespace ast
{
  LetExp::LetExp(const Location& location, DecsList* decs, std::list<Exp*> exps)
  : Exp(location), decs_(decs), exps_(exps)
  {}

  void
  LetExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }
  void
  LetExp::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace ast
