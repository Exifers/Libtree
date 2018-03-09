/**
 ** \file overload/tasks.hh
 ** \brief Overload module tasks.
 */

#pragma once

#include <overload/binder.hh>
#include <task/libtask.hh>

namespace overload::tasks
{

  TASK_GROUP("4.5 Type checking with overloading");

  /// Compute bindings, allowing function overloading.
  TASK_DECLARE("overfun-bindings-compute", "bind the identifiers, "
               "allowing function overloading",
               overfun_bindings_compute, "parse");

  /// Check for type violation, allowing function overloading.
  TASK_DECLARE("O|overfun-types-compute", "check for type violations, "
               "allowing function overloading",
               overfun_types_compute, "overfun-bindings-compute");

} // namespace overload::tasks
