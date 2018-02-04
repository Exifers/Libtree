/**
 ** \file misc/error.cc
 ** \brief Implement error.
 */

#include <iostream>
#include <stdexcept>

#include <misc/contract.hh>
#include <misc/error.hh>

namespace misc
{

  /*--------.
  | error.  |
  `--------*/

  error::error()
    : status_(error_type::success)
  {}

  error::error(const error& e)
  {
    *this = e;
  }

  error&
  error::operator=(const error& rhs)
  {
    status_ = rhs.status_get();
    stream_.str(rhs.stream_get().str());
    return *this;
  }


  /*----------------------------.
  | Filling the error handler.  |
  `----------------------------*/

  error&
  error::operator<<(error_type e)
  {
    unsigned status_value = static_cast<unsigned>(status_);
    unsigned e_value = static_cast<unsigned>(e);
    if ((e_value && e_value < status_value) || (!status_value))
      status_ = e;
    return *this;
  }

  // Import errors.
  error&
  error::operator<<(const error& rhs)
  {
    *this << rhs.status_get() << rhs.stream_get().str();
    return *this;
  }

  error&
  error::operator<<(std::ostream& (*f)(std::ostream&))
  {
    stream_ << f;
    return *this;
  }

  /*---------------.
  | Manipulators.  |
  `---------------*/

  void
  error::exit() const
  {
    throw *this;
  }

  void
  error::exit_on_error() const
  {
    if (static_cast<unsigned>(status_))
      exit();
  }

  void
  error::ice(const char* file, int line) const
  {
    std::cerr << stream_.str();
    __Terminate(file, line, "Internal Compiler error");
  }

  void
  error::ice_on_error(const char* file, int line) const
  {
    if (static_cast<unsigned>(status_))
      ice(file, line);
  }

  void
  error::clear()
  {
    status_ = error_type::success;
    stream_.clear();
  }


  /*------------.
  | Accessors.  |
  `------------*/

  error::operator bool() const
  {
    return status_ != error_type::success;
  }

  error::error_type
  error::status_get() const
  {
    return status_;
  }

  unsigned
  error::status_get_value() const
  {
    return static_cast<unsigned>(status_);
  }

  const std::ostringstream&
  error::stream_get() const
  {
    return stream_;
  }



  std::ostream&
  operator<<(std::ostream& o, const error& e)
  {
    return o << e.stream_get().str();
  }

} // namespace misc
