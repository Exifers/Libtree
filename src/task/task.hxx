/**
 ** \file task/task.hxx
 ** \brief Inline methods for task/task.hh.
 */
#pragma once

#include <task/task.hh>

namespace task
{

  inline
  const char*
  Task::name_get() const
  {
    return name_.c_str();
  }

  inline
  const char*
  Task::module_name_get() const
  {
    return module_name_;
  }

  inline
  const char*
  Task::fullname_get() const
  {
    return fullname_.c_str();
  }

  inline
  const char*
  Task::desc_get() const
  {
    return desc_;
  }

  inline
  const Task::deps_type&
  Task::dependencies_get() const
  {
    return dependencies_;
  }

} // namespace task
