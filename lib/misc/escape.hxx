/**
 ** \file  misc/escape.hxx
 ** \brief Inline methods for misc/escape.hh.
 **/

#pragma once

#include <misc/contract.hh>
#include <misc/escape.hh>

#include <boost/lexical_cast.hpp>

namespace misc
{

  template <class T>
  escaped
  escape(const T& obj)
  {
    return escaped(obj);
  }

  inline
  std::ostream&
  operator<<(std::ostream& o, const escaped& rhs)
  {
    return rhs.print(o);
  }

  template <class T>
  escaped::escaped(const T& obj)
  {
    pobj_str_ = boost::lexical_cast<std::string>(obj);
  }

} // namespace misc
