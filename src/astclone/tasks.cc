/**
 ** \file astclone/tasks.cc
 ** \brief Astclone module related tasks' implementation.
 **/

#include <ast/tasks.hh>

#include <astclone/libastclone.hh>
#define DEFINE_TASKS 1
#include <astclone/tasks.hh>
#undef DEFINE_TASKS

#include <common.hh>

namespace astclone::tasks
{
    void
    clone()
    {
      ast::DecsList* ds = ::astclone::clone(*ast::tasks::the_program);
      if (!ds)
        task_error() << misc::error::error_type::failure
                     << "Cloning Failed\n"
                     << &misc::error::exit;
      ast::tasks::the_program.reset(ds);
    }
} // namespace astclone::tasks
