/**
 ** \file ast/object-exp.hh
 ** \brief Declaration of ast::ObjectExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// ObjectExp.
  class ObjectExp : public Exp
  {
    public:
    ObjectExp(const Location& location, NameTy* namety);
    ObjectExp(const ObjectExp&) = delete;
    ObjectExp& operator=(const ObjectExp&) = delete;
    virtual ~ObjectExp() = default;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const NameTy& namety_get() const;
    NameTy& namety_get();

    protected:
    NameTy* namety_;
  };

} // namespace ast

#include <ast/object-exp.hxx>

