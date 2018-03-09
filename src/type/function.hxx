/**
 ** \file type/function.hxx
 ** \brief Inline methods for type::Function.
 */
#pragma once

#include <misc/contract.hh>
#include <type/function.hh>

namespace type
{

  inline
  const Record&
  Function::formals_get() const
  {
    return *formals_;
  }

  inline
  const Type&
  Function::result_get() const
  {
    return result_;
  }

} // namespace type
