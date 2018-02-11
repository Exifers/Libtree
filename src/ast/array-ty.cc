/**
 ** \file ast/array-ty.cc
 ** \brief Implementation of ast::ArrayTy.
 */

#include <ast/visitor.hh>
#include <ast/array-ty.hh>

namespace ast
{

  ArrayTy::ArrayTy(const Location& location, NameTy* base_type)
    : Ty(location)
    , base_type_(base_type)
  {}

  ArrayTy::~ArrayTy()
  {
    delete base_type_;
  }

  void
  ArrayTy::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  ArrayTy::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

