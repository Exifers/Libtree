/**
 ** \file ast/seq-exp.cc
 ** \brief Implementation of ast::SeqExp.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/seq-exp.hh>

namespace ast
{
  SeqExp::SeqExp(const Location& location, std::list<Exp*> exps)
  : Exp(location), exps_(exps)
  {}

  SeqExp::SeqExp(const Location& location, std::vector<Exp*> exps)
    : Exp(location)
  {
    auto l = std::list<Exp*>{};
    std::copy(exps.begin(), exps.end(), std::back_inserter(l));
    exps_ = l;
  }

  SeqExp::SeqExp(const Location& location, std::vector<Exp*>* exps)
    : Exp(location)
  {
    auto l = std::list<Exp*>{};
    std::copy(exps->begin(), exps->end(), std::back_inserter(l));
    exps_ = l;
  }

  void
  SeqExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  SeqExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

