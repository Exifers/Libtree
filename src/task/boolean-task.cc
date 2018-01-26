/**
 ** \file task/boolean-task.cc
 ** \brief Implementation of task::BooleanTask.
 **
 */

#include <task/boolean-task.hh>

namespace task
{

  BooleanTask::BooleanTask(bool& flag,
                           const char* module_name, const char* desc,
                           const char* name,
                           std::string deps)
    : SimpleTask(name, module_name, desc, deps)
    , flag_(flag)
  {}

  void
  BooleanTask::execute() const
  {
    flag_ = true;
  }

} //namespace task
