/**
 ** \file ast/function-dec.hxx
 ** \brief Inline methods of ast::FunctionDec.
 */

#pragma once

#include <ast/function-dec.hh>

namespace ast
{


  inline const VarDecs&
  FunctionDec::formals_get() const
  {
    return *formals_;
  }
  inline VarDecs&
  FunctionDec::formals_get()
  {
    return *formals_;
  }

  inline const NameTy*
  FunctionDec::result_get() const
  {
    return result_;
  }
  inline NameTy*
  FunctionDec::result_get()
  {
    return result_;
  }

  inline const Exp*
  FunctionDec::body_get() const
  {
    return body_;
  }
  inline Exp*
  FunctionDec::body_get()
  {
    return body_;
  }
  inline void
  FunctionDec::body_set(Exp* body)
  {
    body_ = body;
  }




} // namespace ast

