/**
 ** \file ast/decs.hh
 ** \brief Declare the interface for Decs class.
 */

#pragma once

#include <ast/ast.hh>

namespace ast
{

  /// Declare Decs
  class Decs: public Ast
  {
    /** \name Ctors and dtors.
     ** \{ */
  public:
    /// Construct a Decs
    Decs(const Location& location);
    /** \} */
  };

} // namespace ast

#include <ast/decs.hxx>
