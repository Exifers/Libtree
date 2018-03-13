/**
 ** \file bind/tasks.hh
 ** \brief Bind module related tasks.
 */

#include <task/libtask.hh>

namespace bind::tasks
{
  TASK_GROUP("4. Binding");
  TASK_DECLARE("b|bind", "bind the ast", bind, "")
} // namespace bind::tasks
