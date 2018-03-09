/**
 ** \file type/tasks.cc
 ** \brief Type module task implementations.
 */

#include <ast/tasks.hh>
#include <common.hh>
#include <type/libtype.hh>
#define DEFINE_TASKS 1
#include <type/tasks.hh>
#undef DEFINE_TASKS

// Type module related tasks' implementation.
namespace type::tasks
{

    void
    types_check()
    {
      task_error() << ::type::types_check(*ast::tasks::the_program)
                   << &misc::error::exit_on_error;
    }

} // namespace type::tasks
