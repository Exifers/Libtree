/**
 ** \file ast/ast.hh
 ** \brief Declaration of ast::Ast.
 */

#pragma once

#include <ast/location.hh>
#include <ast/fwd.hh>

namespace ast
{

  /// Ast.
  class Ast
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an Ast node.
    Ast(const Location& location);
    Ast(const Ast&) = delete;
    Ast& operator=(const Ast&) = delete;
    /// Destroy an Ast node.
    virtual ~Ast() = default;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    virtual void accept(ConstVisitor& v) const = 0;
    /// Accept a non-const visitor \a v.
    virtual void accept(Visitor& v) = 0;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return scanner position information.
    const Location& location_get() const;
    /// Set scanner position information.
    void location_set(const Location&);
    /** \} */

  protected:
    /// Scanner position information.
    Location location_;
  };

} // namespace ast

#include <ast/ast.hxx>

