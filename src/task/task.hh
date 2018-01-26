/**
 ** \file task/task.hh
 ** \brief Declare the task::Task class.
 */

#pragma once

#include <string>
#include <vector>

#include <task/task-register.hh>

namespace task
{

  /** \brief A function bound to a command line option.

  The purpose of the Task class is to abstract the execution of a module
  and the tasks on which its execution depends.  This is an implementation
  of the Command Design Pattern.
  */
  class Task
  {
    /** \name Ctor & dtor. */
    /** \{ */
  public:
    /** \brief Construct a Task.

    \param name      name of this task (used for long option)
    \param module_name     name of the module to which the task belongs.
    \param desc      description of this task
    \param deps            optional space separated list of task names
    */
    Task(const char* name, const char* module_name, const char* desc,
         const std::string& deps = "");

    /// Destroy this Task.
    virtual ~Task() = default;
    /** \}*/


    /** \name Abstract methods.
     ** \{ */
  public:
    /// Execute this task.
    virtual void execute() const = 0;
    /** \} */

    using tasks_list_type = TaskRegister::tasks_list_type;

    using deps_type = std::vector<std::string>;

    virtual deps_type
    resolve_dependencies(tasks_list_type& active_tasks) const;


    /** \name Accessors.
     ** \{ */
  public:
    /** Access to 'name'.

    'const char*' is preferred to 'std::string' because TaskRegister
    calls function requiring 'const char*'.
    The use of 'std::string::c_str()' is so forbidden and a call to
    'strdup(std::string::c_str())' would imply dummy memory leaks. */
    const char* name_get() const;

    /// Access to 'module_name'.
    const char* module_name_get() const;

    /// Access to 'fullname'.
    const char* fullname_get() const;

    /// Access to 'desc'.
    const char* desc_get() const;

    /// Access to tasks dependencies.
    const deps_type& dependencies_get() const;

    /** \} */

  public:
    /// Display dependencies of this task .
    void print_dependencies() const;

  public:
    /// Normalize the name of a task.
    static std::string normalize(const std::string& task_name);

  protected:
    /// Task name.
    std::string name_;
    /// Task name plus short name.
    std::string fullname_;
    /// Module name to which the task belongs.
    const char* module_name_;
    /// A short description of this task (displayed in program usage).
    const char* desc_;
    /// Contains the name of the tasks on which this one depends.
    deps_type dependencies_;
  };

} // namespace task

#include <task/task.hxx>
