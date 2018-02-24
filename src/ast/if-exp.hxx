/**
 ** \file ast/if-exp.hxx
 ** \brief Inline methods of ast::IfExp.
 */

#pragma once

#include <ast/if-exp.hh>

namespace ast
{

  inline const Exp&
  IfExp::condition_get() const
  {
    return *condition_;
  }

  inline Exp&
  IfExp::condition_get()
  {
    return *condition_;
  }


  inline const Exp&
  IfExp::content_get() const
  {
    return *content_;
  }

  inline Exp&
  IfExp::content_get()
  {
    return *content_;
  }

  inline const Exp&
  IfExp::else_content_get() const
  {
    return *else_content_;
  }

  inline Exp&
  IfExp::else_content_get()
  {
    return *else_content_;
  }
} // namespace ast
