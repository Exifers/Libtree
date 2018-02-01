/**
 ** \file ast/subscript-var.hh
 ** \brief Declaration of ast::SubscriptVar.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/var.hh>

namespace ast
{

  /// SubscriptVar.
  class SubscriptVar : public Var
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a SubscriptVar node.
    SubscriptVar(const Location& location, Var* var, Exp* index);
    SubscriptVar(const SubscriptVar&) = delete;
    SubscriptVar& operator=(const SubscriptVar&) = delete;
    /// Destroy a SubscriptVar node.
    virtual ~SubscriptVar();
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
    /// Return the mother variable.
    const Var& var_get() const;
    /// Return the mother variable.
    Var& var_get();
    /// Return the offset expression.
    const Exp& index_get() const;
    /// Return the offset expression.
    Exp& index_get();
    /** \} */

  protected:
    /// The mother variable.
    Var* var_;
    /// The offset expression.
    Exp* index_;
  };

} // namespace ast

#include <ast/subscript-var.hxx>

