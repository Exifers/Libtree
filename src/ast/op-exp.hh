/**
 ** \file ast/op-exp.hh
 ** \brief Declaration of ast::OpExp.
 */

#pragma once

#include <ast/exp.hh>
#include <map>

namespace ast
{

  /// OpExp.
  /** Represents a binary operation, as 'left oper right'.\a oper can be
  **  arithmetical operations (+ - * /) or comparisons (=, <=, <>, ...). */
  class OpExp : public Exp
  {

  public:
    /// Operator qualifier.
    enum class Oper
      {
        // Arithmetics.
        /** \brief "+" */ add,
        /** \brief "-" */ sub,
        /** \brief "*" */ mul,
        /** \brief "/" */ div,

        // Comparison.
        /** \brief "=" */  eq,
        /** \brief "<>" */ ne,
        /** \brief "<" */  lt,
        /** \brief "<=" */ le,
        /** \brief ">" */  gt,
        /** \brief ">=" */ ge
      };

  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an OpExp node.
    OpExp(const Location& location, Exp* left, OpExp::Oper oper,
          Exp* right);
    OpExp(const OpExp&) = delete;
    OpExp& operator=(const OpExp&) = delete;
    /// Destroy an OpExp node.
    virtual ~OpExp();
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
    /// Return left operand.
    const Exp& left_get() const;
    /// Return left operand.
    Exp& left_get();
    /// Return operator.
    OpExp::Oper oper_get() const;
    /// Return right operand.
    const Exp& right_get() const;
    /// Return right operand.
    Exp& right_get();
    /** \} */

  protected:
    /// Left operand.
    Exp* left_;
    /// Operator.
    OpExp::Oper oper_;
    /// Right operand.
    Exp* right_;
  };

} // namespace ast


// Return a representation of an operator.
std::string
str(ast::OpExp::Oper oper);

#include <ast/op-exp.hxx>

