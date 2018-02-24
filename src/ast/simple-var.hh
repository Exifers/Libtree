/**
 ** \file ast/simple-var.hh
 ** \brief Declaration of ast::SimpleVar.
 */

#pragma once

#include <ast/var-dec.hh>
#include <ast/var.hh>
#include <misc/symbol.hh>

namespace ast
{

  /// SimpleVar.
  class SimpleVar : public Var
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a SimpleVar node.
    SimpleVar(const Location& location, const misc::symbol& name);
    SimpleVar(const SimpleVar&) = delete;
    SimpleVar& operator=(const SimpleVar&) = delete;
    /// Destroy a SimpleVar node.
    virtual ~SimpleVar() = default;
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
    /// Return variable's name.
    const misc::symbol& name_get() const;
    /// Set variable's name.
    void name_set(const misc::symbol&);
    /// Return definition site.
    const VarDec* def_get() const;
    /// Return definition site.
    VarDec* def_get();
    /// Set definition site.
    void def_set(VarDec*);
    /** \} */

  protected:
    /// Variable's name.
    misc::symbol name_;
    /// Definition site.
    VarDec* def_ = nullptr;
  };

} // namespace ast

#include <ast/simple-var.hxx>

