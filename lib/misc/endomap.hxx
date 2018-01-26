/**                                                     -*- C++ -*-
 ** \file misc/endomap.hxx
 ** \brief Implementation of misc::endomap.
 */

#pragma once

#include <misc/endomap.hh>

namespace misc
{

  template <class T>
  endomap<T>::endomap ()
    : map<T, T> (), strictness_ (strictness_type::nonstrict)
  {}

  template <class T>
  endomap<T>*
  endomap<T>::clone() const
  {
    return new endomap<T>(*this);
  }

  template <class T>
  T
  endomap<T>::operator()(const T& t) const
  {
    typename super_type::map_type::const_iterator ires = this->find(t);
    if (ires != this->map_.end())
      return ires->second;
    else if (this->strictness_ == strictness_type::nonstrict)
      return t;
    std::ostringstream err;
    err << "map: no mapping for " << t;
    throw std::range_error(err.str());
  }

  template <class T>
  T&
  endomap<T>::operator[](const T& t)
  {
    // Inspired by ``Efficient STL'' on efficient insert_or_update
    // for maps.  See also misc::put.
    typename super_type::map_type::iterator i = this->map_.lower_bound(t);
    if (i == this->map_.end() || this->map_.key_comp()(t, i->first))
      i = this->map_.emplace(t, t).first;
    return i->second;
  }

} // namespace misc
