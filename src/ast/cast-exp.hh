/**
 ** \file ast/cast-exp.hh
 ** \brief Declaration of ast::CastExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/ty.hh>

namespace ast
{


  /** \class ast::CastExp
   ** \brief Cast the type of an expression to a given type.
   **
   ** This node is only used in the bounds checking transformation
   ** (see desugar::bounds_checks_add).  You don't need to worry
   ** about it (nor about the `cast' keyword) if you don't implement
   ** this option.
   */

  class CastExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a CastExp node.
    CastExp(const Location& location, Exp* exp, Ty* ty);
    CastExp(const CastExp&) = delete;
    CastExp& operator=(const CastExp&) = delete;
    /// Destroy a CastExp node.
    virtual ~CastExp();
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
    /// Return the cast expression.
    const Exp& exp_get() const;
    /// Return the cast expression.
    Exp& exp_get();
    /// Return the target type.
    const Ty& ty_get() const;
    /// Return the target type.
    Ty& ty_get();
    /** \} */

  protected:
    /// The cast expression.
    Exp* exp_;
    /// The target type.
    Ty* ty_;
  };

} // namespace ast

#include <ast/cast-exp.hxx>

