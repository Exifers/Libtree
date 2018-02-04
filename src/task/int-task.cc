/**
 ** \file task/int-task.cc
 ** \brief IntTask class implementation.
 **
 */

#include <iostream>
#include <exception>

#include <common.hh>
#include <task/int-task.hh>

namespace task
{

  IntTask::IntTask(int& var, int min, int max,
                   const char* module_name, const char* desc,
                   const char* name,
                   std::string deps)
    : ArgumentTask(name, module_name, desc, "NUM", deps)
    , var_(var)
    , min_(min)
    , max_(max)
  {}

  void
  IntTask::arg_set(const std::string& arg) const
  {
    arg_ = arg;

    try
      {
        var_ = stol(arg);
      }
    catch (std::invalid_argument& e)
      {
        std::cerr << program_name << ": expected an integer: " << arg << '\n';
        throw;
      }

    if (!(min_ <= var_ && var_ <= max_))
      {
        std::cerr << program_name << ": invalid integer: " << var_ << '\n';

        throw std::invalid_argument(std::string("invalid integer: ") + arg_);
      }
  }

  void
  IntTask::execute() const
  {
    // Assignment done in arg_set.
  }

} //namespace task
