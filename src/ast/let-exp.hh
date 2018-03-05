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
  /** Represents a let in end statement with the following pattern : 'let decs
  **  in exps end'.
  */
  class LetExp : public Exp
  {
    public:
    LetExp(const Location& location, DecsList* decs, std::list<Exp*> exps);
    LetExp(const LetExp&) = delete;
    LetExp& operator=(const LetExp&) = delete;

    virtual ~LetExp() = default;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const DecsList& decs_get(void) const;
    DecsList& decs_get(void);
    const std::list<Exp*>& exps_get(void) const;
    std::list<Exp*>& exps_get(void);

    private:
    DecsList* decs_;
    std::list<Exp*> exps_;
  };

} // namespace ast

#include <ast/let-exp.hxx>

