/**
 ** \file ast/record-exp.hh
 ** \brief Declaration of ast::RecordExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/field-init.hh>
#include <ast/name-ty.hh>

namespace ast
{

  /// RecordExp.
  class RecordExp : public Exp
  {
    public:
      RecordExp(const Location& location, NameTy* namety,
          std::list<VarDec*> fields);
      RecordExp(const RecordExp&) = delete;
      RecordExp& operator=(const RecordExp&) = delete;

      virtual ~RecordExp() = default;

      void accept(ConstVisitor& v) const override;
      void accept(Visitor& v) override;

      const NameTy& namety_get() const;
      NameTy& namety_get();
      const std::list<VarDec*>& fields_get() const;
      std::list<VarDec*>& fields_get();

    private:
      NameTy* namety_;
      std::list<VarDec*> fields_;
  };

} // namespace ast

#include <ast/record-exp.hxx>

