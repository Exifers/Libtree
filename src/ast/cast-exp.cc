/**
 ** \file ast/cast-exp.cc
 ** \brief Implementation of ast::CastExp.
 */

#include <ast/visitor.hh>
#include <ast/cast-exp.hh>

namespace ast
{

  CastExp::CastExp(const Location& location, Exp* exp, Ty* ty)
    : Exp(location)
    , exp_(exp)
    , ty_(ty)
  {}

  CastExp::~CastExp()
  {
    delete exp_;
    delete ty_;
  }

  void
  CastExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  CastExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

