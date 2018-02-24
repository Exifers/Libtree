/**
 ** \file ast/if-exp.cc
 ** \brief Implementation of ast::IfExp.
 */

#include <ast/visitor.hh>
#include <ast/if-exp.hh>

namespace ast
{

  IfExp::IfExp(const Location& location, Exp *condition, Exp *content,
               Exp *else_content)
  : Exp(location),
    condition_(condition),
    content_(content),
    else_content_(else_content)
  {}

  void
  IfExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  IfExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

