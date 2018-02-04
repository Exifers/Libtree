/**
 ** \file  misc/escape.hh
 ** \brief Escape: escaping special characters for output.
 **/

#pragma once

#include <iosfwd>
#include <string>

namespace misc
{

  class escaped
  {
  public:
    std::ostream& print(std::ostream& ostr) const;

  protected:
    template <class T>
    escaped(const T&);

    template <class T>
    friend escaped escape(const T&);

  protected:
    std::string pobj_str_;

  private:
    std::ostream&
    escape_(std::ostream& o, const std::string& es) const;
  };

  template <class T>
  escaped escape(const T&);

  std::ostream& operator<<(std::ostream& o, const escaped&);

} // namespace misc

#include <misc/escape.hxx>
