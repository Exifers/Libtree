/**
 ** \file misc/error.hxx
 ** \brief Implement template parts of misc/error.hh.
 */

#pragma once

#include <misc/error.hh>

namespace misc
{

  template <class T>
  error&
  error::operator<<(const T& t)
  {
    stream_ << t;
    return *this;
  }

  // Member manipulators.
  inline error&
  error::operator<<(member_manip_type f)
  {
    (this->*f)();
    return *this;
  }

  // Const member manipulators.
  inline error&
  error::operator<<(const_member_manip_type f)
  {
    (this->*f)();
    return *this;
  }

} // namespace misc
