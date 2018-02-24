/**
 ** \file ast/name-ty.hh
 ** \brief Declaration of ast::NameTy.
 */

#pragma once

#include <ast/ty.hh>
#include <ast/type-dec.hh>
#include <misc/symbol.hh>

namespace ast
{

  /// NameTy.
  class NameTy : public Ty
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a NameTy node.
    NameTy(const Location& location, const misc::symbol& name);
    NameTy(const NameTy&) = delete;
    NameTy& operator=(const NameTy&) = delete;
    /// Destroy a NameTy node.
    virtual ~NameTy() = default;
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
    /// Return the name of the type.
    const misc::symbol& name_get() const;
    /// Set the name of the type.
    void name_set(const misc::symbol&);
    /// Return definition site.
    const TypeDec* def_get() const;
    /// Return definition site.
    TypeDec* def_get();
    /// Set definition site.
    void def_set(TypeDec*);
    /** \} */

  protected:
    /// The name of the type.
    misc::symbol name_;
    /// Definition site.
    TypeDec* def_ = nullptr;
  };

} // namespace ast

#include <ast/name-ty.hxx>

