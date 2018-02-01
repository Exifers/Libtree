/**
 ** \file ast/subscript-var.hxx
 ** \brief Inline methods of ast::SubscriptVar.
 */

#pragma once

#include <ast/subscript-var.hh>

namespace ast
{


  inline const Var&
  SubscriptVar::var_get() const
  {
    return *var_;
  }
  inline Var&
  SubscriptVar::var_get()
  {
    return *var_;
  }

  inline const Exp&
  SubscriptVar::index_get() const
  {
    return *index_;
  }
  inline Exp&
  SubscriptVar::index_get()
  {
    return *index_;
  }


} // namespace ast

