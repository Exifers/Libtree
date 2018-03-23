/**
 ** \file ast/typable.cc
 ** \brief Implementation of ast::Typable.
 */

#include <ast/visitor.hh>
#include <ast/typable.hh>

namespace ast
{

  Typable::Typable(const type::Type *type)
    : type_(type)
  {}

  /*
  void
  Typable::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  Typable::accept(Visitor& v)
  {
    v(*this);
  }
  */

} // namespace ast

