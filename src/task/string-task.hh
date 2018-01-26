/**
 ** \file task/string-task.hh
 ** \brief Declare the task::StringTask class.
 **
 */
#pragma once

#include <task/argument-task.hh>

namespace task
{

  /// A simple Task that sets a String variable.
  class StringTask : public ArgumentTask
  {
  public:
    StringTask(std::string& var,
               const char* module_name, const char* desc,
               const char* name,
               std::string deps);

    void execute() const override;

  private:
    std::string& var_;
  };

} //namespace task
