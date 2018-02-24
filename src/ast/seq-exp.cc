/**
 ** \file ast/seq-exp.cc
 ** \brief Implementation of ast::SeqExp.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/seq-exp.hh>

namespace ast
{
  
  SeqExp::SeqExp(const Location& location, std::list<FieldInit*> lvalue)
  : Exp(location), lvalue_(lvalue)
  {}

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

