/**
 ** \file ast/if-exp.hh
 ** \brief Declaration of ast::IfExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/seq-exp.hh>

namespace ast
{

  /// IfExp.
  class IfExp : public Exp
  {
     public:
     IfExp(const Location& location, Exp *condition, Exp *content,
           Exp *else_content);
     IfExp(const IfExp&) = delete;
     IfExp& operator=(const IfExp&) = delete;

     virtual ~IfExp() = default;

     void accept(ConstVisitor& v) const override;
     void accept(Visitor& v) override;

     const Exp& condition_get() const;
     Exp& condition_get();
     const Exp& content_get() const;
     Exp& content_get();
     const Exp& else_content_get() const;
     Exp& else_content_get();

     protected:
     Exp* condition_;
     Exp* content_;
     Exp* else_content_;
  };

} // namespace ast

#include <ast/if-exp.hxx>

