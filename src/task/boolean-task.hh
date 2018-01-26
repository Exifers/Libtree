/**
 ** \file task/boolean-task.hh
 ** \brief Declare the task::BooleanTask class.
 **
 */
#pragma once

#include <task/simple-task.hh>

namespace task
{

  /// A simple Task that sets a Boolean variable to true.
  class BooleanTask : public SimpleTask
  {
  public:
    BooleanTask(bool& flag,
                const char* module_name, const char* desc,
                const char* name,
                std::string deps);

    void execute() const override;

  private:
    bool& flag_;
  };

} // namespace task
