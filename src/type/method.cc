/**
 ** \file type/method.cc
 ** \brief Implementation for type/method.hh.
 */

#include <iostream>

#include <type/method.hh>
#include <type/visitor.hh>

namespace type
{

  Method::Method(const misc::symbol& name, const Class* owner,
                 const Record* formals, const Type& result,
                 ast::MethodDec* def)
    : Function(formals, result)
    , name_(name)
    , owner_(owner)
    , def_(def)
  {}

  void
  Method::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  Method::accept(Visitor& v)
  {
    v(*this);
  }

#warning // FIXME: Some code was deleted here.

} // namespace type
