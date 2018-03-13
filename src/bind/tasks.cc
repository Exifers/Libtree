/**
 ** \file bind/tasks.cc
 ** \brief Bind module tasks implementation.
 */


#define DEFINE_TASKS 1
#include <bind/tasks.hh>
#undef DEFINE_TASKS

#include "libbind.hh"

namespace bind::tasks
{ 

  void
  bindings_compute()
  {
    bind::tasks::bind_ast();
  }

  void
  bindings_display()
  {
  }
}
