/**
 ** \file escapes/tasks.cc
 ** \brief Escapes module related tasks' implementation.
 */

#include <ostream>

#include <ast/libast.hh>
#include <ast/tasks.hh>
#include <escapes/libescapes.hh>
#define DEFINE_TASKS 1
#include <escapes/tasks.hh>
#undef DEFINE_TASKS
#include <misc/xalloc.hh>

namespace escapes::tasks
{



  /*--------------------.
    | Static Link tasks.  |
    `--------------------*/

  void
  escapes_compute()
  {
    escapes::escapes_compute(*ast::tasks::the_program);
  }

  /* WARNING.  It is very tempting to use BOOLEAN_TASK_DECLARE with
     these stream flags, since it factors out the need for the
     following routines.  Unfortunately when the Tasks are created,
     not all the misc::xalloc are instantiated, so the registered
     address of these flags is likely to change if there are other
     xalloc in between.  It is the index that is constant, not the
     address of the pword.

     Of course we could have Tasks dedicated to misc::xalloc, but
     that's not nice.  */

  void
  escapes_display()
  {
    ast::escapes_display(std::cout) = true;
  }


} // namespace escapes::tasks
