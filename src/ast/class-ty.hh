/**
 ** \file ast/class-ty.hh
 ** \brief Declaration of ast::ClassTy.
 */

#pragma once

#include <ast/decs-list.hh>
#include <ast/name-ty.hh>
#include <ast/ty.hh>

namespace ast
{

  /// ClassTy.
  class ClassTy : public Ty
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a ClassTy node.
    ClassTy(const Location& location, NameTy* super, DecsList* decs);
    ClassTy(const ClassTy&) = delete;
    ClassTy& operator=(const ClassTy&) = delete;
    /// Destroy a ClassTy node.
    virtual ~ClassTy();
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
    /// Return super class.
    const NameTy& super_get() const;
    /// Return super class.
    NameTy& super_get();
    /// Return list of declarations.
    const DecsList& decs_get() const;
    /// Return list of declarations.
    DecsList& decs_get();
    /** \} */

  protected:
    /// Super class.
    NameTy* super_;
    /// List of declarations.
    DecsList* decs_;
  };

} // namespace ast

#include <ast/class-ty.hxx>

