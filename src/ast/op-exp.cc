/**
 ** \file ast/op-exp.cc
 ** \brief Implementation of ast::OpExp.
 */

#include <ast/visitor.hh>
#include <ast/op-exp.hh>

namespace ast
{

  OpExp::OpExp(const Location& location, Exp* left, OpExp::Oper oper,
               Exp* right)
    : Exp(location)
    , left_(left)
    , oper_(oper)
    , right_(right)
  {}

  OpExp::~OpExp()
  {
    delete left_;
    delete right_;
  }

  void
  OpExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  OpExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast
