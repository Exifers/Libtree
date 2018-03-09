/**
 ** \file ast/ty.hh
 ** \brief Declaration of ast::Ty.
 */

#pragma once

#include <ast/ast.hh>
#include <ast/typable.hh>
#include <ast/type-constructor.hh>

namespace ast
{

  /// Ty.
  class Ty : public Ast, public Typable, public TypeConstructor
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a Ty node.
    Ty(const Location& location);
    Ty(const Ty&) = delete;
    Ty& operator=(const Ty&) = delete;
    /// Destroy a Ty node.
    virtual ~Ty() = default;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override = 0;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override = 0;
    /// \}
  };

} // namespace ast

#include <ast/ty.hxx>

