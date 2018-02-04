/**
 ** \file task/simple-task.cc
 ** \brief SimpleTask class implementation.
 */

#include <task/simple-task.hh>
#include <task/task-register.hh>

namespace task
{

  SimpleTask::SimpleTask(const char* name, const char* module_name,
                         const char* desc,
                         std::string deps)
    : Task(name, module_name, desc, deps)
  {
    // Register this task.
    TaskRegister::instance().register_task(*this);
  }

} // namespace task
