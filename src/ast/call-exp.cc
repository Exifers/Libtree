/**
 ** \file ast/call-exp.cc
 ** \brief Implementation of ast::CallExp.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/call-exp.hh>

namespace ast
{

  CallExp::CallExp(const Location& location,
      misc::symbol name,
      std::list<Exp*> exps)
    : Exp(location), name_(name), exps_(exps)
  {}

  CallExp::CallExp(const Location& location, misc::symbol name,
      std::vector<Exp*>* exps)
    : Exp(location), name_(name)
  {
    auto l = std::list<Exp*>{};
    std::copy(exps->begin(), exps->end(), std::back_inserter(l));
    exps_ = l;
  }

  void CallExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void CallExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

