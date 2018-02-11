/**
 ** \file ast/var-dec.hxx
 ** \brief Inline methods of ast::VarDec.
 */

#pragma once

#include <ast/var-dec.hh>

namespace ast
{


  inline const NameTy*
  VarDec::type_name_get() const
  {
    return type_name_;
  }
  inline NameTy*
  VarDec::type_name_get()
  {
    return type_name_;
  }

  inline const Exp*
  VarDec::init_get() const
  {
    return init_;
  }
  inline Exp*
  VarDec::init_get()
  {
    return init_;
  }


} // namespace ast

