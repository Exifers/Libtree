/**
 ** \file desugar/libdesugar.cc
 ** \brief Functions exported by the desugar module.
 */

#include <memory>

#include <ast/exp.hh>
#include <ast/decs-list.hh>
#include <bind/libbind.hh>
#include <desugar/bounds-checking-visitor.hh>
#include <desugar/desugar-visitor.hh>
#include <desugar/libdesugar.hh>
#include <escapes/libescapes.hh>
#include <overload/liboverload.hh>
#include <type/libtype.hh>

namespace desugar
{

  /*----------.
  | Helpers.  |
  `----------*/

  template <typename A>
  void
  bind_and_types_check(A& tree)
  {
    misc::error e;
  // FIXME: Some code was deleted here.
    e.ice_on_error_here();
    e << type::types_check(tree);
    e.ice_on_error_here();
  }

  // Explicit instantiation.
  template void bind_and_types_check<ast::DecsList>(ast::DecsList&);

  /*----------.
  | Desugar.  |
  `----------*/

  template <typename A>
  A*
  raw_desugar(const A& tree,
              bool desugar_for_p, bool desugar_string_cmp_p)
  {
    // Desugar.
    DesugarVisitor desugar(desugar_for_p, desugar_string_cmp_p);
    desugar(tree);
    return dynamic_cast<A*>(desugar.result_get());
  }

  template <typename A>
  A*
  desugar(const A& tree,
          bool desugar_for_p, bool desugar_string_cmp_p)
  {
    // Desugar.
    A* desugared = raw_desugar(tree, desugar_for_p, desugar_string_cmp_p);
    assertion(desugared);
    std::unique_ptr<A> desugared_ptr(desugared);
    // Recompute the bindings and the types.
    bind_and_types_check(*desugared_ptr);
    return desugared_ptr.release();
  }

  /// Explicit instantiations.
  template ast::DecsList* raw_desugar(const ast::DecsList&, bool, bool);
  template ast::DecsList* desugar(const ast::DecsList&, bool, bool);

  /*-----------------------.
  | Array bounds checking.  |
  `-----------------------*/

  template <typename A>
  A*
  raw_bounds_checks_add(const A& tree)
  {
    // Add array bounds checking code.
    BoundsCheckingVisitor add_bounds_checks;
    add_bounds_checks(tree);
    return dynamic_cast<A*>(add_bounds_checks.result_get());
  }

  template <typename A>
  A*
  bounds_checks_add(const A& tree)
  {
    // Add bounds checks.
    A* transformed = raw_bounds_checks_add(tree);
    assertion(transformed);
    std::unique_ptr<A> transformed_ptr(transformed);
    // Recompute the bindings and the types.
    bind_and_types_check(*transformed_ptr);
    return transformed_ptr.release();
  }

  /// Explicit instantiations.
  template ast::DecsList* raw_bounds_checks_add(const ast::DecsList&);
  template ast::DecsList* bounds_checks_add(const ast::DecsList&);

} // namespace desugar
