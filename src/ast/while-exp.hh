/**
 ** \file ast/while-exp.hh
 ** \brief Declaration of ast::WhileExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{

  /// WhileExp.
  class WhileExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a WhileExp node.
    WhileExp(const Location& location, Exp* test, Exp* body);
    WhileExp(const WhileExp&) = delete;
    WhileExp& operator=(const WhileExp&) = delete;
    /// Destroy a WhileExp node.
    virtual ~WhileExp();
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
    /// Return exit condition of the loop.
    const Exp& test_get() const;
    /// Return exit condition of the loop.
    Exp& test_get();
    /// Return instructions executed in the loop.
    const Exp& body_get() const;
    /// Return instructions executed in the loop.
    Exp& body_get();
    /** \} */

  protected:
    /// Exit condition of the loop.
    Exp* test_;
    /// Instructions executed in the loop.
    Exp* body_;
  };

} // namespace ast

#include <ast/while-exp.hxx>

