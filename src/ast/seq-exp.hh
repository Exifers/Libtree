/**
 ** \file ast/seq-exp.hh
 ** \brief Declaration of ast::SeqExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{

  /// SeqExp.
  class SeqExp : public Exp
  {
    public:
    SeqExp(const Location& location, std::list<Exp*> exps);
    SeqExp(const SeqExp&) = delete;
    SeqExp& operator=(const SeqExp&) = delete;

    virtual ~SeqExp() = default;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const std::list<Exp*> exps_get() const;
    std::list<Exp*> exps_get();

    protected:
    std::list<Exp*> exps_;
  };

} // namespace ast

#include <ast/seq-exp.hxx>

