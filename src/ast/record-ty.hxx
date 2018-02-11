/**
 ** \file ast/record-ty.hxx
 ** \brief Inline methods of ast::RecordTy.
 */

#pragma once

#include <ast/record-ty.hh>

namespace ast
{

  inline const std::list<Field*>&
  RecordTy::tyfields_get() const
  {
    return tyfields_;
  }

  inline std::list<Field*>&
  RecordTy::tyfields_get()
  {
    return tyfields_;
  }

} // namespace ast

