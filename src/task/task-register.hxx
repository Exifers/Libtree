/**
 ** \file task/task-register.hxx
 ** \brief Inline methods of task::TaskRegister.
 **
 */

#pragma once

#include <task/task-register.hh>

namespace task
{

  inline
  const misc::timer&
  TaskRegister::timer_get() const
  {
    return timer_;
  }

} // namespace task.
