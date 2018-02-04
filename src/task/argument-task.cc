/**
 ** \file task/argument-task.cc
 ** \brief ArgumentTask class implementation.
 */

#include <task/argument-task.hh>
#include <task/task-register.hh>

namespace task
{

  ArgumentTask::ArgumentTask(const char* name, const char* module_name,
                             const char* desc, const char* argname,
                             std::string deps)
    : Task(name, module_name, desc, deps)
    , argname_(argname)
  {
    // Register this task.
    TaskRegister::instance().register_task(*this);
  }

  const std::string&
  ArgumentTask::arg_get() const
  {
    return arg_;
  }

  void
  ArgumentTask::arg_set(const std::string& arg) const
  {
    arg_ = arg;
  }

  const char*
  ArgumentTask::argname_get() const
  {
    return argname_;
  }

} // namespace task
