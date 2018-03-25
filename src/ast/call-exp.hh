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
    CallExp(const Location& location, misc::symbol name, std::list<Exp*> exps);
    CallExp(const Location& location, misc::symbol name,
        std::vector<Exp*>* exps);
    CallExp(const CallExp&) = delete;
    CallExp& operator=(const CallExp&) = delete;

    virtual ~CallExp() = default;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const misc::symbol& name_get() const;
    misc::symbol& name_get();
    void name_set(misc::symbol &name);
    const std::list<Exp*>& exps_get() const;
    std::list<Exp*>& exps_get();
    void def_set(FunctionDec *def);
    FunctionDec *def_get() const;

    protected:
    misc::symbol name_;
    std::list<Exp*> exps_;
    FunctionDec *def_ = nullptr;
  };

} // namespace ast

#include <ast/call-exp.hxx>

