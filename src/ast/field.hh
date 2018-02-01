/**
 ** \file ast/field.hh
 ** \brief Declaration of ast::Field.
 */

#pragma once

#include <ast/ast.hh>
#include <ast/name-ty.hh>
#include <misc/symbol.hh>

namespace ast
{

  /// Field.
  class Field : public Ast
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a Field node.
    Field(const Location& location, const misc::symbol& name,
          NameTy* type_name);
    Field(const Field&) = delete;
    Field& operator=(const Field&) = delete;
    /// Destroy a Field node.
    virtual ~Field();
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
    /// Return the field name.
    const misc::symbol& name_get() const;
    /// Set the field name.
    void name_set(const misc::symbol&);
    /// Return the field type name.
    const NameTy& type_name_get() const;
    /// Return the field type name.
    NameTy& type_name_get();
    /** \} */

  protected:
    /// The field name.
    misc::symbol name_;
    /// The field type name.
    NameTy* type_name_;
  };

} // namespace ast

#include <ast/field.hxx>

