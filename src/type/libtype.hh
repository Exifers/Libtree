/**
 ** \file type/libtype.hh
 ** \brief Declare the function exported by type module.
 */

#pragma once

#include <ast/fwd.hh>
#include <misc/error.hh>

/// Type-checking an ast::Ast.
namespace type
{

  /** \brief Check types in a (bound) AST.
   ** \param tree   abstract syntax tree's root.
   ** \return       synthesis of the errors possibly found. */
  misc::error types_check(::ast::Ast& tree);

} // namespace type
