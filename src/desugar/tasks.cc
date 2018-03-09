/**
 ** \file desugar/tasks.cc
 ** \brief Desugar module related tasks' implementation.
 **/

#include <ast/tasks.hh>
#include <astclone/libastclone.hh>
#include <common.hh>
#include <desugar/libdesugar.hh>
#define DEFINE_TASKS 1
#include <desugar/tasks.hh>
#undef DEFINE_TASKS

namespace desugar::tasks
{

  /*-------------.
    | Desugaring.  |
    `-------------*/

  void
  desugar()
  {
    astclone::apply(::desugar::desugar, ast::tasks::the_program,
                    desugar_for_p, desugar_string_cmp_p);
  }

  // FIXME: Some code was deleted here (Overload and desugar).

  void
  raw_desugar()
  {
    astclone::apply(::desugar::raw_desugar, ast::tasks::the_program,
                    desugar_for_p, desugar_string_cmp_p);
  }


  /*-----------------------.
    | Array bounds checking.  |
    `-----------------------*/

  void
  bounds_checks_add()
  {
    astclone::apply(::desugar::bounds_checks_add, ast::tasks::the_program);
  }

  // FIXME: Some code was deleted here (Overload and bound check).

  void
  raw_bounds_checks_add()
  {
    astclone::apply(::desugar::raw_bounds_checks_add,
                    ast::tasks::the_program);
  }

} // namespace desugar::tasks
