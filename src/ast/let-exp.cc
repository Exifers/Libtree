/**
 ** \file ast/let-exp.cc
 ** \brief Implementation of ast::LetExp.
 */

#include <algorithm>
#include <ast/visitor.hh>
#include <ast/let-exp.hh>

namespace ast
{
  LetExp::LetExp(const Location& location, DecsList* decs, std::list<Exp*> exps)
  : Exp(location), decs_(decs), exps_(exps)
  {}

  LetExp::LetExp(const Location& location, DecsList* decs,
      std::vector<Exp*>* exps)
    : Exp(location), decs_(decs)
  {
    auto l = std::list<Exp*>{};
    std::copy(exps->begin(), exps->end(), std::back_inserter(l));
    exps_ = l;
  }

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
