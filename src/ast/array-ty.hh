/**
 ** \file ast/array-ty.hh
 ** \brief Declaration of ast::ArrayTy.
 */

#pragma once

#include <ast/name-ty.hh>
#include <ast/ty.hh>

namespace ast
{

  /// ArrayTy.
  class ArrayTy : public Ty
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an ArrayTy node.
    ArrayTy(const Location& location, NameTy* base_type);
    ArrayTy(const ArrayTy&) = delete;
    ArrayTy& operator=(const ArrayTy&) = delete;
    /// Destroy an ArrayTy node.
    virtual ~ArrayTy();
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
    /// Return name of the base type.
    const NameTy& base_type_get() const;
    /// Return name of the base type.
    NameTy& base_type_get();
    /** \} */

  protected:
    /// Name of the base type.
    NameTy* base_type_;
  };

} // namespace ast

#include <ast/array-ty.hxx>

