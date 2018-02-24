/**
 ** \file ast/call-exp.hh
 ** \brief Declaration of ast::CallExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/function-dec.hh>
#include <misc/symbol.hh>

namespace ast
{

  /// CallExp.
  /** Represents a function call, with the following pattern 'namety ( exps ) '.
  **  exps is a list of expressions nodes.
  */
  class CallExp : public Exp
  { 
    public:
    CallExp(const Location& location, NameTy* namety, std::list<Exp*> exps);
    CallExp(const ArrayExp&) = delete;
    CallExp& operator=(const ArrayExp&) = delete;

    virtual ~CallExp() = default;
    
    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const NameTy& namety_get() const;
    NameTy& namety_get();
    const std::list<Exp*>& exps_get() const;
    std::list<Exp*>& exps_get();

    protected:
    NameTy* namety_;
    std::list<Exp*> exps_;
  };

} // namespace ast

#include <ast/call-exp.hxx>

