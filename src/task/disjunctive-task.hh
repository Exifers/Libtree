/**
 ** \file task/disjunctive-task.hh
 ** \brief Declare the DisjunctiveTask class.
 **
 */
#pragma once

#include <task/simple-task.hh>

namespace task
{

  /// A Task that makes sure that AT LEAST one of its dependencies is
  /// scheduled.
  class DisjunctiveTask : public SimpleTask
  {
  public:
    DisjunctiveTask(const char* module_name, const char* desc,
                    const char* name,
                    std::string deps);

    void execute() const override;
    deps_type
    resolve_dependencies(tasks_list_type& active_tasks) const override;
  };

} //namespace task
