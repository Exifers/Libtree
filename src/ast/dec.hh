/**
 ** \file ast/dec.hh
 ** \brief Declaration of ast::Dec.
 */

#pragma once

#include <ast/ast.hh>
#include <ast/typable.hh>
#include <misc/symbol.hh>

namespace ast
{

  /// Dec.
  class Dec : public Ast, public Typable
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a Dec node.
    Dec(const Location& location, const misc::symbol& name);
    Dec(const Dec&) = delete;
    Dec& operator=(const Dec&) = delete;
    /// Destroy a Dec node.
    virtual ~Dec() = default;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override = 0;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override = 0;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return name of the defined entity.
    const misc::symbol& name_get() const;
    /// Set name of the defined entity.
    void name_set(const misc::symbol&);
    /** \} */

  protected:
    /// Name of the defined entity.
    misc::symbol name_;
  };

} // namespace ast

#include <ast/dec.hxx>

