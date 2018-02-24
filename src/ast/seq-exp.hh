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
    SeqExp(const Location& location, std::list<FieldInit*> lvalue);
    SeqExp(const SeqExp&) = delete;
    SeqExp& operator=(const SeqExp&) = delete;

    virtual ~SeqExp() = default;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const std::list<FieldInit*> lvalue_get() const;
    std::list<FieldInit*> lvalue_get();

    protected:
    std::list<FieldInit*> lvalue_;
  };

} // namespace ast

#include <ast/seq-exp.hxx>

