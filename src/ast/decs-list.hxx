/**
 ** \file ast/decs-list.hxx
 ** \brief Inline methods of ast::DecsList.
 */

#pragma once

#include <ast/decs-list.hh>

namespace ast
{


  inline const DecsList::decs_type&
  DecsList::decs_get() const
  {
    return decs_;
  }
  inline DecsList::decs_type&
  DecsList::decs_get()
  {
    return decs_;
  }


} // namespace ast

