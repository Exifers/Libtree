/**
 ** \file task/disjunctive-task.cc
 ** \brief Implementation of task::DisjunctiveTask.
 **
 */

#include <task/disjunctive-task.hh>

namespace task
{

  DisjunctiveTask::DisjunctiveTask(const char* module_name, const char* desc,
                                   const char* name,
                                   std::string deps)
    : SimpleTask(name, module_name, desc, deps)
  {}

  void
  DisjunctiveTask::execute() const
  {
    // Nothing to do.
  }


  Task::deps_type
  DisjunctiveTask::resolve_dependencies(tasks_list_type& active_tasks) const
  {
    if (!active_tasks.empty() || dependencies_.empty())
      return Task::deps_type();
    else
      return Task::deps_type(1, *dependencies_.begin());
  }

}
