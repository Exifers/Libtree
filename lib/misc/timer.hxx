/**
 ** \file misc/timer.hxx
 ** \brief Inline methods for misc/timer.hh.
 */

#pragma once

#include <misc/contract.hh>
#include <misc/timer.hh>

namespace misc
{

  inline
  void
  timer::push(int i)
  {
    precondition(this->intmap.find(i) != this->intmap.end());
    this->push(this->intmap[i]);
  }

  inline
  void
  timer::pop([[maybe_unused]] const std::string& task_name)
  {
    precondition(this->tasksmap[task_name] == this->tasks.top());
    this->pop();
  }

  inline
  void
  timer::pop(int i)
  {
    this->pop(this->intmap[i]);
  }


  inline
  void
  timer::dump_on_destruction(std::ostream& out)
  {
    this->dump_stream = &out;
  }

  inline
  void
  timer::start()
  {
    this->total.start();
  }

  inline
  void
  timer::stop()
  {
    this->total.stop();
  }

  inline
  timer::time::time()
    : user(0), sys(0), wall(0)
  {}

  inline
  timer::time&
  timer::time::operator+=(const time& rhs)
  {
    this->wall += rhs.wall;
    this->user += rhs.user;
    this->sys  += rhs.sys;
    return *this;
  }

} // namespace misc
