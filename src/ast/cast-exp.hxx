/**
 ** \file ast/cast-exp.hxx
 ** \brief Inline methods of ast::CastExp.
 */

#pragma once

#include <ast/cast-exp.hh>

namespace ast
{


  inline const Exp&
  CastExp::exp_get() const
  {
    return *exp_;
  }
  inline Exp&
  CastExp::exp_get()
  {
    return *exp_;
  }

  inline const Ty&
  CastExp::ty_get() const
  {
    return *ty_;
  }
  inline Ty&
  CastExp::ty_get()
  {
    return *ty_;
  }


} // namespace ast

