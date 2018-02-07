/**
 ** \file ast/record-ty.hh
 ** \brief Declaration of ast::RecordTy.
 */

#pragma once

#include <ast/field.hh>
#include <ast/ty.hh>

namespace ast
{

  /// RecordTy.
  class RecordTy : public Ty
  {
    public:
    RecordTy(const Location& location, std::list<Field*> tyfields);
    RecordTy(const RecordTy&) = delete;
    RecordTy& operator=(const RecordTy&) = delete;

    virtual ~RecordTy();

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;


    const std::list<Field*>& tyfields_get() const;
    std::list<Field*>& tyfields_get();


    protected:
    std::list<Field*> tyfields_;
  };

} // namespace ast

#include <ast/record-ty.hxx>

