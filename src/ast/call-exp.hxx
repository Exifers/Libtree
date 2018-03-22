/**
 ** \file ast/call-exp.hxx
 ** \brief Inline methods of ast::CallExp.
 */

#pragma once

#include <ast/call-exp.hh>

namespace ast
{

  inline const misc::symbol&
  CallExp::name_get() const
  {
    return name_;
  }

  inline misc::symbol&
  CallExp::name_get()
  {
    return name_;
  }

  inline void
  CallExp::name_set(misc::symbol &name)
  {
    name_ = name;
  }

  inline const std::list<Exp*>&
  CallExp::exps_get() const
  {
    return exps_;
  }

  inline std::list<Exp*>&
  CallExp::exps_get()
  {
    return exps_;
  }

  inline void
  CallExp::def_set(FunctionDec *def)
  {
    def_ = def;
  }

  inline FunctionDec *
  CallExp::def_get() const
  {
    return def_;
  }

} // namespace ast
