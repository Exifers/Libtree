/**
 ** \file ast/cast-var.hxx
 ** \brief Inline methods of ast::CastVar.
 */

#pragma once

#include <ast/cast-var.hh>

namespace ast
{


  inline const Var&
  CastVar::var_get() const
  {
    return *var_;
  }
  inline Var&
  CastVar::var_get()
  {
    return *var_;
  }

  inline const Ty&
  CastVar::ty_get() const
  {
    return *ty_;
  }
  inline Ty&
  CastVar::ty_get()
  {
    return *ty_;
  }


} // namespace ast

