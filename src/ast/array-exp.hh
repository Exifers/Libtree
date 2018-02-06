/**
 ** \file ast/array-exp.hh
 ** \brief Declaration of ast::ArrayExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{

  /// ArrayExp.
  class ArrayExp : public Exp
  {
    public:
    ArrayExp(const Location& location, NameTy* namety, Exp* size_exp, Exp* type_exp);
    ArrayExp(const ArrayExp&) = delete;
    ArrayExp& operator=(const ArrayExp&) = delete;

    virtual ~ArrayExp() = default;
    
    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const NameTy& namety_get() const;
    NameTy& namety_get();
    const Exp& size_exp_get() const;
    Exp& size_exp_get();
    const Exp& type_exp_get() const;
    Exp& type_exp_get();

    protected:
    NameTy* namety_;
    Exp* size_exp_;
    Exp* type_exp_;
  };

} // namespace ast

#include <ast/array-exp.hxx>

