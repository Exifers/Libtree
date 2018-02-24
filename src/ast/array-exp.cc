/**
 ** \file ast/array-exp.cc
 ** \brief Implementation of ast::ArrayExp.
 */

#include <ast/visitor.hh>
#include <ast/array-exp.hh>

namespace ast
{
  ArrayExp::ArrayExp(const Location& location,
                     NameTy* namety,
                     Exp* size_exp,
                     Exp* type_exp)
  : Exp(location), namety_(namety), size_exp_(size_exp), type_exp_(type_exp)
  {}
 
  void
  ArrayExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  ArrayExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast
