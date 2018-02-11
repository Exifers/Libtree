/**
 ** \file ast/cast-var.cc
 ** \brief Implementation of ast::CastVar.
 */

#include <ast/visitor.hh>
#include <ast/cast-var.hh>

namespace ast
{

  CastVar::CastVar(const Location& location, Var* var, Ty* ty)
    : Var(location)
    , var_(var)
    , ty_(ty)
  {}

  CastVar::~CastVar()
  {
    delete var_;
    delete ty_;
  }

  void
  CastVar::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  CastVar::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

