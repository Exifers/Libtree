/**
 ** \file task/function-task.hh
 ** \brief Declare the task::FunctionTask class.
 **
 */
#pragma once

#include <task/simple-task.hh>

namespace task
{

  /// A simple Task that invokes a callback function.
  class FunctionTask : public SimpleTask
  {
  public:
    using callback_type = auto() -> void;

    FunctionTask(callback_type& callback,
                 const char* module_name, const char* desc,
                 const char* name,
                 std::string deps);

  public:
    void execute() const override;

  private:
    callback_type& execute_;
  };

} //namespace task
