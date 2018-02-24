/**
 ** \file ast/assign-exp.hh
 ** \brief Declaration of ast::AssignExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/var.hh>

#include <misc/variant.hh>

namespace ast
{

  /// AssignExp.
  class AssignExp : public Exp
  {
    public:
    AssignExp(const Location& location,
              Var *lvalue,
              Exp *exp);

    AssignExp(const AssignExp&) = delete;
    AssignExp& operator=(const AssignExp&) = delete;

    virtual ~AssignExp() = default;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const Var& lvalue_get() const;
    Var& lvalue_get();
    const Exp& exp_get() const;
    Exp& exp_get();

    protected:
    Var *lvalue_;
    Exp *exp_;
  };

} // namespace ast

#include <ast/assign-exp.hxx>

