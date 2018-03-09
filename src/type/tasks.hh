/**
 ** \file type/tasks.hh
 ** \brief Type module tasks.
 */

#pragma once

#include <task/libtask.hh>

namespace type::tasks
{

  TASK_GROUP("4. Type checking");

  /// Default the type-checking to Tiger (without objects nor overloading).
  DISJUNCTIVE_TASK_DECLARE("T|typed",
                           "default the type-checking to Tiger "
                           "(without objects nor overloading)",
                           "types-compute"
                           " object-types-compute");

  /// Check for type violation.
  TASK_DECLARE("types-compute", "check for type violations",
               types_check, "bindings-compute");

} // namespace type::tasks
