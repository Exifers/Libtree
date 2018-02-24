/**
 ** \file ast/exp.hh
 ** \brief Declaration of ast::Exp.
 */

#pragma once

#include <ast/ast.hh>

namespace ast
{

  /// Exp.
  class Exp : public Ast
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an Exp node.
    Exp(const Location& location);
    Exp(const Exp&) = delete;
    Exp& operator=(const Exp&) = delete;
    /// Destroy an Exp node.
    virtual ~Exp() = default;
    /** \} */
  };

} // namespace ast

#include <ast/exp.hxx>

