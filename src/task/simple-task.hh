/**
 ** \file task/simple-task.hh
 ** \brief Declare the task::SimpleTask class.
 */

#pragma once

#include <string>

#include <task/task.hh>

namespace task
{

  /** \brief A code factoring class for tasks without arguments.

  The purpose of this class is to avoid duplicating the code which register a
  task without arguments. The sibling class task::ArgumentTask does pretty much
  the same (with extended functionnalities) for tasks with arguments.
  */
  class SimpleTask : public Task
  {

    /** \name Ctor. */
    /** \{ */
  public:
    /// Construct and register a SimpleTask.
    SimpleTask(const char* name, const char* module_name,
               const char* desc, std::string deps = "");

    /** \} */

  };

} // namespace task
