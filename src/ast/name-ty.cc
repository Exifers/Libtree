/**
 ** \file ast/name-ty.cc
 ** \brief Implementation of ast::NameTy.
 */

#include <ast/visitor.hh>
#include <ast/name-ty.hh>

namespace ast
{

  NameTy::NameTy(const Location& location, const misc::symbol& name)
    : Ty(location)
    , name_(name)
  {}


  void
  NameTy::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  NameTy::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

