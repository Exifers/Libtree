/**
 ** \file astclone/tasks.hh
 ** \brief Astclone module tasks.
 */

#pragma once

#include <misc/fwd.hh>

#include <task/libtask.hh>

/// Tasks of the astclone module.
namespace astclone::tasks
{

    TASK_GROUP("2.5 Cloning");

    /// Clone ast::tasks::the_program, and replace it with its copy.
    TASK_DECLARE("clone", "clone the Ast", clone, "parse");
    
} // namespace astclone::tasks
