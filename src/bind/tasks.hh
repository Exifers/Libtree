/**
 ** \file bind/tasks.hh
 ** \brief Bind module related tasks.
 */

#include <task/libtask.hh>

namespace bind::tasks
{
  TASK_GROUP("3. Binding");
  TASK_DECLARE("b|bindings-compute", "bind the ast", bindings_compute, "parse");
  TASK_DECLARE("B|bindings-display",
      "display bindings in the ast pretty print", bindings_display_task, "parse");
} // namespace bind::tasks
