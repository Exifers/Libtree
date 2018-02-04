/**
 ** \file task/tasks.hh
 ** \brief Task module related tasks.
 */

#pragma once

#include <task/libtask.hh>

namespace task
{

  namespace tasks
  {

    TASK_GROUP("0. Tasks");

    /// List all the existing tasks.
    TASK_DECLARE("task-list", "list registered tasks",
                 tasks_list, "");
    /// Dump task graph.
    TASK_DECLARE("task-graph", "show task graph",
                 tasks_graph, "");
    /// List the selected tasks in order.
    TASK_DECLARE("task-selection", "list tasks to be run",
                 tasks_selection, "");
    /// Ask for a time report at the end of the execution.
    TASK_DECLARE("time-report", "report execution times",
                 time_report, "");

  } // namespace tasks

} // namespace ast
