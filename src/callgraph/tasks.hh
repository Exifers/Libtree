/**
 ** \file callgraph/tasks.hh
 ** \brief Callgraph module related tasks.
 */

#pragma once

#include <callgraph/fundec-graph.hh>
#include <task/libtask.hh>

/// The Tasks of the escapes module.
namespace callgraph::tasks
{

  TASK_GROUP("3. Callgraph");


  /*-------------.
    | Call graph.  |
    `-------------*/

  /// Build the call graph.
  TASK_DECLARE("callgraph-compute", "build the call graph",
               callgraph_compute, "bindings-compute");
  /// Dump the callgraph.
  TASK_DECLARE("callgraph-dump", "dump the call graph",
               callgraph_dump, "callgraph-compute");



} // namespace callgraph
