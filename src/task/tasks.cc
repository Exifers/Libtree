/**
 ** \file task/tasks.cc
 ** \brief Task module related tasks.
 */

#include <iostream>

#include <common.hh>
#include <task/task-register.hh>
#define DEFINE_TASKS 1
#include <task/tasks.hh>
#undef DEFINE_TASKS

// Ast module related tasks' implementation.
namespace task
{

  namespace tasks
  {

    void
    tasks_list()
    {
      TaskRegister::instance().print_task_list(std::cout);
    }

    void
    tasks_graph()
    {
      TaskRegister::instance().print_task_graph(std::cout);
    }

    void
    tasks_selection()
    {
      TaskRegister::instance().print_task_order(std::cout);
    }

    void
    time_report()
    {
      task_timer.dump_on_destruction(std::cerr);
    }

  } // namespace tasks

} // namespace task
