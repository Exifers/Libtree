/**
 ** \file ast/class-ty.cc
 ** \brief Implementation of ast::ClassTy.
 */

#include <ast/visitor.hh>
#include <ast/class-ty.hh>

namespace ast
{

  ClassTy::ClassTy(const Location& location, NameTy* super, DecsList* decs)
    : Ty(location)
    , super_(super)
    , decs_(decs)
  {}

  ClassTy::~ClassTy()
  {
    delete decs_;
  }

  void
  ClassTy::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  ClassTy::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

