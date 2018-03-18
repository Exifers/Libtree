/**
 ** \file overload/liboverload.cc
 ** \brief Define exported type functions.
 */

#include <overload/binder.hh>
#include <overload/liboverload.hh>
#include <overload/type-checker.hh>

namespace overload
{

  std::pair<overfun_bindings_type, misc::error>
  bind(ast::Ast& tree)
  {
    Binder bind;
    bind(tree);
    return std::pair(std::move(bind.overfun_bindings_get()),
                std::move(bind.error_get()));
  }

  misc::error
  types_check(ast::Ast& tree,
              const overfun_bindings_type& overfun_bindings)
  {
    TypeChecker type{overfun_bindings};
    type(tree);
    return type.error_get();
  }

} // namespace overload
