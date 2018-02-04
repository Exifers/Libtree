/**
 ** \file task/argument-task.hh
 ** \brief Declare the task::ArgumentTask class.
 */

#pragma once

#include <string>

#include <task/task.hh>

namespace task
{

  /** \brief A `Task' expecting arguments prior to be executed.

  This class embodies tasks which need an additional parameter for their
  `execute()' method. Therefore a call to `arg_set()' must be made prior to
  the `execute()' method, to set the value of this expected argument.
  This class also automates the registering of its derived classes, as does its
  sibling class `SimpleTask' for tasks without additional argument.
  */
  class ArgumentTask : public Task
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct and register an ArgumentTask.
    ArgumentTask(const char* name, const char* module_name,
                 const char* desc, const char* argname,
                 std::string deps = "");

    /** \} */


    /** \name Accessors.
     ** \{ */
  public:
    /// Access to 'arg'.
    const std::string& arg_get() const;

    /// Access to `arg'.
    virtual void arg_set(const std::string& arg) const;

    /// Access to `argname'.
    const char* argname_get() const;

    /** \} */


  protected:
    /// ArgumentTask argument value.
    mutable std::string arg_;

    /// Argument name to be displayed when printing.
    const char* argname_;
  };

} // namespace task
