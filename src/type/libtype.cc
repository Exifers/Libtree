/**
 ** \file type/libtype.cc
 ** \brief Define the function exported by type module.
 */

#include <ast/exp.hh>
#include <type/libtype.hh>
#include <type/type-checker.hh>

namespace type
{

  misc::error
  types_check(ast::Ast& tree)
  {
    TypeChecker type;
    type(tree);
    return type.error_get();
  }

} // namespace type
