/**
 ** \file task/string-task.cc
 ** \brief Implementation of task::StringTask.
 **
 */

#include <task/string-task.hh>

namespace task
{

  StringTask::StringTask(std::string& var,
                         const char* module_name, const char* desc,
                         const char* name,
                         std::string deps)
    : ArgumentTask(name, module_name, desc, "STRING", deps)
    , var_(var)
  {}

  void
  StringTask::execute() const
  {
    var_ = arg_get();
  }

} //namespace task
