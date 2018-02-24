/**
 ** \file ast/record-exp.cc
 ** \brief Implementation of ast::RecordExp.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/record-exp.hh>

namespace ast
{
  RecordExp::RecordExp(const Location& location,
                     NameTy* namety,
                     std::list<FieldInit*> fields)
  : Exp(location), namety_(namety), fields_(fields)
  {}
 
  void
  RecordExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  RecordExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast
