/**
 ** \file ast/nil-exp.hh
 ** \brief Declaration of ast::NilExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{

  /// NilExp.
  class NilExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a NilExp node.
    NilExp(const Location& location);
    NilExp(const NilExp&) = delete;
    NilExp& operator=(const NilExp&) = delete;
    /// Destroy a NilExp node.
    virtual ~NilExp() = default;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}
  };

} // namespace ast

#include <ast/nil-exp.hxx>

