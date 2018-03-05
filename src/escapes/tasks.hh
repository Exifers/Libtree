/**
 ** \file escapes/tasks.hh
 ** \brief Escapes module related tasks.
 */

#pragma once

#include <task/libtask.hh>

/// The Tasks of the escapes module.
namespace escapes::tasks
{

    TASK_GROUP("3. Escapes");

    /// Compute variables escaping.
    TASK_DECLARE("e|escapes-compute",
                 "compute the escaping variables "
                 "and the functions requiring a static link",
                 escapes_compute, "bound");

    /// Display escaped variables.
    TASK_DECLARE("E|escapes-display",
                 "enable escape display in the AST",
                 escapes_display, "parse");


} // namespace parse::tasks
