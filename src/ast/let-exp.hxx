/**
 ** \file ast/let-exp.hxx
 ** \brief Inline methods of ast::LetExp.
 */

#pragma once

#include <ast/let-exp.hh>

namespace ast
{
  inline const DecsList&
  LetExp::decs_get(void) const
  {
    return *decs_;
  }

  inline DecsList&
  LetExp::decs_get(void)
  {
    return *decs_;
  }

  inline const std::list<Exp*>&
  LetExp::exps_get(void) const
  {
    return exps_;
  }

  inline std::list<Exp*>&
  LetExp::exps_get(void)
  {
    return exps_;
  }

} // namespace ast

