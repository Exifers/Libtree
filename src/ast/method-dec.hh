/**
 ** \file ast/method-dec.hh
 ** \brief Declaration of ast::MethodDec.
 */

#pragma once

#include <ast/function-dec.hh>

namespace ast
{

  /** \class ast::MethodDec
   ** \brief Method declaration.
   **
   ** A method declaration is \em not a function in the strict
   ** sense of object-oriented programming.  Inheritance is used
   ** as a factoring tool here.
   */

  class MethodDec : public FunctionDec
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a MethodDec node.
    MethodDec(const Location& location, const misc::symbol& name,
              VarDecs* formals, NameTy* result, Exp* body);
    MethodDec(const MethodDec&) = delete;
    MethodDec& operator=(const MethodDec&) = delete;
    /// Destroy a MethodDec node.
    virtual ~MethodDec() = default;
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

#include <ast/method-dec.hxx>

