/**
 ** \file ast/string-exp.cc
 ** \brief Implementation of ast::StringExp.
 */

#include <ast/visitor.hh>
#include <ast/string-exp.hh>

namespace ast
{
  StringExp::StringExp(const Location& location, std::string value)
  : Exp(location), value_(value)
  {}


  void StringExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }
  void StringExp::accept(Visitor& v)
  {
    v(*this);
  }

  std::string StringExp::value_get() const
  {
    return value_;
  }

} // namespace ast

