/**
 ** \file inlining/tasks.cc
 ** \brief Inlining module related tasks' implementation.
 **/


#include <ast/tasks.hh>
#include <astclone/libastclone.hh>
#include <common.hh>
#include <inlining/libinlining.hh>
#define DEFINE_TASKS 1
#include <inlining/tasks.hh>
#undef DEFINE_TASKS

namespace inlining::tasks
{

  /*-----------.
    | Inlining.  |
    `-----------*/

  void
  inline_expand()
  {
    astclone::apply(::inlining::inline_expand, ast::tasks::the_program);
  }

#warning // FIXME: Some code was deleted here (Overload and inline).


  /*-------------------.
    | Function pruning.  |
    `-------------------*/

  void
  prune()
  {
    astclone::apply(::inlining::prune, ast::tasks::the_program);
  }

#warning // FIXME: Some code was deleted here (Overload and prune).

} // namespace inlining::tasks
