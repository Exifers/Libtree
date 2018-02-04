/**
 ** \file parse/tweast.hxx
 ** \brief implements inline methods of parse/tweast.hh
 */

#pragma once

#include <misc/error.hh>
#include <parse/tweast.hh>

namespace parse
{

  template <typename T>
  T&
  Tweast::append_(unsigned&, T& data) const
  {
    return data;
  }

  template <typename T>
  Tweast&
  Tweast::operator<<(const T& t)
  {
    input_ << append_(count_, t);
    return *this;
  }

  template <typename T>
  T*
  Tweast::take(unsigned s)
  {
    T* t = nullptr;
    try
      {
        t = MetavarMap<T>::take_(s);
      }
    catch (std::range_error& e)
      {
        // Print the contents of the Tweast before dying.
        misc::error error;
        error << e.what() << std::endl;
        error << *this;
        error.ice_here();
      }
    return t;
  }


} // namespace parse
