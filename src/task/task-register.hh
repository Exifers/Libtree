/**
 ** \file task/task-register.hh
 ** \brief Declare the task::TaskRegister class.
 **
 */

#pragma once

#include <iosfwd>
#include <map>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

#include <misc/timer.hh>
#include <task/fwd.hh>

namespace task
{

  /** \brief Register Tasks.

  The purpose of the TaskRegister class is to collect tasks
  and organize their execution using their dependencies (like 'make').
  For modeling details, see Design Patterns: singleton.
  */
  class TaskRegister
  {
    // Make it non-copyable.
    TaskRegister(const TaskRegister&) = delete;
    TaskRegister & operator=(const TaskRegister&) = delete;

    /// \name Ctor & dtor.
  private:
    /// Construct a TaskRegister.
    TaskRegister() = default;
  public:
    /// Access to the unique TaskRegister.
    static TaskRegister& instance();

    /** \name Tasks registering.
     ** \{ */
    /// Register task \a task.
    void register_task(const SimpleTask& task);
    void register_task(const ArgumentTask& task);
    /// Register the task \a task_name for execution.
    void enable_task(const std::string& task_name);

    /// Return the number of tasks to execute.
    int nb_of_task_to_execute_get();
    /** \} */


    /// \name Task reordering.
  private:
    /** \brief Resolve dependencies between tasks.
     **
     ** Resolve dependencies on tasks registered for execution.
     ** Make a depth first search of implicit tasks graph,
     ** check cycles and build an ordered list of tasks. */
    void resolve_dependencies(const Task& task);

  public:
    /** \brief Parse \a argv and determine which tasks to execute.
     **
     ** Use boost::program_options. */
    char* parse_arg(int argc, char* argv[]);


    /** \name Display TaskRegister content.
     ** \{ */
    /// Display registered Tasks.
    std::ostream& print_task_list(std::ostream& ostr);
    /// Display task graph.
    std::ostream& print_task_graph(std::ostream& ostr);
    /// Display registered Tasks execution order.
    std::ostream& print_task_order(std::ostream& ostr);

    /** \name Using registered Tasks.
     ** \{ */
    /// Execute tasks, checking dependencies.
    void execute();
    /** \} */

    /** \name Time management.
     ** \{ */
    /// Access to the tasks timer.
    const misc::timer& timer_get() const;
    /** \} */

    /// Ordered vector of tasks.
    using tasks_list_type = std::vector<const Task*>;
    /// Associate an integer key to a task
    using tasks_by_key_type = std::map<int, Task const*>;


  private:
    /// Associate a task name to a task.
    using tasks_by_name_type = std::map<const std::string, Task const*>;
    /// Associate a module name to a task module.
    using indexed_module_type =
      std::map<const std::string, boost::program_options::options_description>;

    // Common code between the two overload of `register_task'.
    indexed_module_type::iterator register_task_(const Task& task);

    /// 'string to task' map.
    tasks_by_name_type task_list_;

    /// 'ordered for execution' tasks list.
    tasks_list_type task_order_;

    /// Tasks timer.
    misc::timer timer_;

    /// Task modules.
    indexed_module_type modules_;
  };

} // namespace task

#include <task/task-register.hxx>
