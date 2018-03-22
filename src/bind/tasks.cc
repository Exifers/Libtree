/**
 ** \file bind/tasks.cc
 ** \brief Bind module tasks implementation.
 */

#define DEFINE_TASKS 1
#include <bind/tasks.hh>
#undef DEFINE_TASKS

#include "libbind.hh"

namespace ast
{
  extern const misc::xalloc<bool> bindings_display;
  extern bool g_bindings_display;
  extern bool g_escape_display;
}

namespace bind::tasks
{

  void
  bindings_compute()
  {
    bind::tasks::bind_ast();
  }

  void
  bindings_display_task()
  {
    ast::g_bindings_display = true;
  }

  void
  rename_task()
  {
    bind::tasks::rename_ast();
  }
}
