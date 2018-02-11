/**
 ** \file ast/int-exp.hh
 ** \brief Declaration of ast::IntExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{

  /// IntExp.
  class IntExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an IntExp node.
    IntExp(const Location& location, int value);
    IntExp(const IntExp&) = delete;
    IntExp& operator=(const IntExp&) = delete;
    /// Destroy an IntExp node.
    virtual ~IntExp() = default;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return stored integer value.
    int value_get() const;
    /** \} */

  protected:
    /// Stored integer value.
    int value_;
  };

} // namespace ast

#include <ast/int-exp.hxx>

