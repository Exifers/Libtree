/**
 ** \file ast/field-init.cc
 ** \brief Implementation of ast::FieldInit.
 */

#include <ast/visitor.hh>
#include <ast/field-init.hh>

namespace ast
{

  FieldInit::FieldInit(const Location& location, const misc::symbol& name,
                       Exp* init)
    : Ast(location)
    , name_(name)
    , init_(init)
  {}

  FieldInit::~FieldInit()
  {
    delete init_;
  }

  void
  FieldInit::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  FieldInit::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

