/**
 ** \file ast/seq-exp.hxx
 ** \brief Inline methods of ast::SeqExp.
 */

#pragma once

#include <ast/seq-exp.hh>

namespace ast
{
  inline const std::list<Exp*>
  SeqExp::exps_get() const
  {
    return exps_;
  }

  inline std::list<Exp*>
  SeqExp::exps_get()
  {
    return exps_;
  }
} // namespace ast

