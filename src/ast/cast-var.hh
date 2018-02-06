/**
 ** \file ast/cast-var.hh
 ** \brief Declaration of ast::CastVar.
 */

#pragma once

#include <ast/ty.hh>
#include <ast/var.hh>

namespace ast
{


  /** \class ast::CastVar
   ** \brief Cast the type of an l-value to a given type.
   **
   ** This node is only used in the bounds checking transformation
   ** (see desugar::bounds_checks_add).  You don't need to worry
   ** about it (nor about the `cast' keyword) if you don't implement
   ** this option.
   */

  class CastVar : public Var
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a CastVar node.
    CastVar(const Location& location, Var* var, Ty* ty);
    CastVar(const CastVar&) = delete;
    CastVar& operator=(const CastVar&) = delete;
    /// Destroy a CastVar node.
    virtual ~CastVar();
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
    /// Return the cast variable.
    const Var& var_get() const;
    /// Return the cast variable.
    Var& var_get();
    /// Return the target type.
    const Ty& ty_get() const;
    /// Return the target type.
    Ty& ty_get();
    /** \} */

  protected:
    /// The cast variable.
    Var* var_;
    /// The target type.
    Ty* ty_;
  };

} // namespace ast

#include <ast/cast-var.hxx>

