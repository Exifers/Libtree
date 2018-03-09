/**
 ** \file inlining/libinlining.cc
 ** \brief Functions exported by the inlining module.
 */

#include <memory>

#include <ast/exp.hh>
#include <desugar/libdesugar.hh>
#include <inlining/inliner.hh>
#include <inlining/libinlining.hh>
#include <inlining/pruner.hh>

namespace inlining
{

  /*-----------.
  | Inlining.  |
  `-----------*/

  template <typename A>
  A*
  inline_expand(const A& tree)
  {
    // Inline.
    Inliner inline_expand(tree);
    inline_expand(tree);
    A* inlined = dynamic_cast<A*>(inline_expand.result_get());
    assertion(inlined);
    std::unique_ptr<A> inlined_ptr(inlined);
    // Recompute the bindings and the types.
    desugar::bind_and_types_check(*inlined_ptr);
    return inlined_ptr.release();
  }

  template ast::DecsList* inline_expand(const ast::DecsList&);

  /*-------------------.
  | Function pruning.  |
  `-------------------*/

  template <typename A>
  A*
  prune(const A& tree)
  {
    // Prune unused functions.
    Pruner prune;
    prune(tree);
    A* pruned = dynamic_cast<A*>(prune.result_get());
    assertion(pruned);
    std::unique_ptr<A> pruned_ptr(pruned);
    // Recompute the bindings and the types.
    desugar::bind_and_types_check(*pruned_ptr);
    return pruned_ptr.release();
  }

  template ast::DecsList* prune(const ast::DecsList&);

} // namespace inlining
