/**
 ** \file task/function-task.cc
 ** \brief Implementation of task::FunctionTask.
 **
 */

#include <task/function-task.hh>

namespace task
{

  FunctionTask::FunctionTask(callback_type& callback,
                             const char* module_name, const char* desc,
                             const char* name,
                             std::string deps)
    : SimpleTask(name, module_name, desc, deps)
    , execute_(callback)
  {}

  void
  FunctionTask::execute() const
  {
    execute_();
  }

} //namespace task
