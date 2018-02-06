/**
 ** \file ast/libast.hh
 ** \brief Public ast interface declaration.
 */

#pragma once

#include <iosfwd>

#include <misc/xalloc.hh>

#include <ast/fwd.hh>

/// Ast management.
namespace ast
{

  extern const misc::xalloc<bool> escapes_display;

  /// Output \a a on \a ostr.
  std::ostream& operator<<(std::ostream& ostr, const Ast& tree);


} // namespace ast
