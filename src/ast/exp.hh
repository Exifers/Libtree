/**
 ** \file ast/exp.hh
 ** \brief Declaration of ast::Exp.
 */

#pragma once

#include <ast/ast.hh>
#include <ast/typable.hh>

namespace ast
{

  /// Exp.
  class Exp : public Ast, public Typable
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

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override = 0;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override = 0;
    /// \}
  };

} // namespace ast

#include <ast/exp.hxx>

