/**
 ** \file task/multiple-string-task.cc
 ** \brief Implementation of task::MultipleStringTask.
 */

#include <task/multiple-string-task.hh>

namespace task
{

  MultipleStringTask::MultipleStringTask(callback_type& cb,
                                         const char* module_name,
                                         const char* desc,
                                         const char* name,
                                         std::string deps)
    : ArgumentTask(name, module_name, desc, "DIR", deps)
    , execute_(cb)
  {}

  void
  MultipleStringTask::execute() const
  {
    execute_(arg_get());
  }

} //namespace task
