/**
 ** \file ast/let-exp.hh
 ** \brief Declaration of ast::LetExp.
 */

#pragma once

#include <ast/decs-list.hh>
#include <ast/exp.hh>
#include <misc/contract.hh>

namespace ast
{

  /// LetExp.
  class LetExp : public Exp
  {
    public:
    /* FIXME adapt this code : */
    LetExp(const Location& location, int value);
    LetExp(const LetExp&) = delete;
    LetExp& operator=(const LetExp&) = delete;

    virtual ~LetExp() = default;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    private:
    DecsList decs_;
    /* List of exp ???? */
  };

} // namespace ast

#include <ast/let-exp.hxx>

