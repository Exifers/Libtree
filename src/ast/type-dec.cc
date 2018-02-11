/**
 ** \file ast/type-dec.cc
 ** \brief Implementation of ast::TypeDec.
 */

#include <ast/visitor.hh>
#include <ast/type-dec.hh>

namespace ast
{

  TypeDec::TypeDec(const Location& location, const misc::symbol& name,
                   Ty* ty)
    : Dec(location, name)
    , ty_(ty)
  {}

  TypeDec::~TypeDec()
  {
    delete ty_;
  }

  void
  TypeDec::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  TypeDec::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

