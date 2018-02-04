/**
 ** \file task/int-task.hh
 ** \brief Declare the IntTask class.
 **
 */
#pragma once

#include <task/argument-task.hh>

namespace task
{

  /// A simple Task that sets an Int variable.
  class IntTask : public ArgumentTask
  {
  public:
    IntTask(int& var, int min, int max,
            const char* module_name, const char* desc,
            const char* name,
            std::string deps);

    void execute() const override;
    void arg_set(const std::string& arg) const override;

  private:
    int& var_;
    int min_;
    int max_;
  };

} //namespace task
