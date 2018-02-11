/**
 ** \file ast/nil-exp.cc
 ** \brief Implementation of ast::NilExp.
 */

#include <ast/visitor.hh>
#include <ast/nil-exp.hh>

namespace ast
{

  NilExp::NilExp(const Location& location)
    : Exp(location)
  {}


  void
  NilExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  NilExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

