/**                                                     -*- C++ -*-
 ** \file misc/map.hxx
 ** \brief Implementation of misc::map.
 */

#pragma once

#include <iostream>
#include <sstream>

#include <boost/lexical_cast.hpp>

#include <misc/contract.hh>
#include <misc/indent.hh>
#include <misc/map.hh>

namespace misc
{

  template <class T, class N>
  map<T, N>*
  map<T, N>::clone() const
  {
    return new map<T, N>(*this);
  }

  template <class T, class N>
  typename map<T, N>::const_iterator
  map<T, N>::find(const T& t) const
  {
    return map_.find(t);
  }

  template <class T, class N>
  typename map<T, N>::iterator
  map<T, N>::find(const T& t)
  {
    return map_.find(t);
  }

  template <class T, class N>
  typename map<T, N>::iterator
  map<T, N>::xfind(const T& t)
  {
    iterator ires = find(t);
    if (ires != map_.end())
      return ires;
    else
      throw std::range_error(std::string("map: no mapping for ")
                             + boost::lexical_cast<std::string>(t));
  }

  template <class T, class N>
  typename map<T, N>::const_iterator
  map<T, N>::xfind(const T& t) const
  {
    const_iterator ires = find(t);
    if (ires != map_.end())
      return ires;
    else
      throw std::range_error(std::string("map: no mapping for ")
                             + boost::lexical_cast<std::string>(t));
  }

  template <class T, class N>
  typename map<T, N>::key_compare
  map<T, N>::key_comp() const
  {
    return map_.key_comp();
  }

  template <class T, class N>
  N
  map<T, N>::operator()(const T& t) const
  {
    return xfind(t)->second;
  }

  template <class T, class N>
  std::vector<N>
  map<T, N>::operator()(const std::vector<T>& ts) const
  {
    std::vector<N> res;
    for (const T& t : ts)
      res.emplace_back(operator()(t));
    return res;
  }

  template <class T, class N>
  std::ostream&
  map<T, N>::print(std::ostream& ostr) const
  {
    for (const value_type& p : *this)
      ostr << p.first << " -> " << p.second << misc::iendl;
    return ostr;
  }

  template <class T, class N>
  N
  map<T, N>::operator[](const T& t) const
  {
    return operator()(t);
  }

  template <class T, class N>
  N&
  map<T, N>::operator[](const T& t)
  {
    return map_[t];
  }

  template <class T, class N>
  typename map<T, N>::iterator
  map<T, N>::begin()
  {
    return map_.begin();
  }

  template <class T, class N>
  typename map<T, N>::iterator
  map<T, N>::end()
  {
    return map_.end();
  }

  template <class T, class N>
  typename map<T, N>::const_iterator
  map<T, N>::begin() const
  {
    return map_.begin();
  }

  template <class T, class N>
  typename map<T, N>::const_iterator
  map<T, N>::end() const
  {
    return map_.end();
  }


  template <class T, class N>
  typename map<T, N>::iterator
  map<T, N>::lower_bound(const T& k)
  {
    return map_.lower_bound(k);
  }

  template <class T, class N>
  typename map<T, N>::const_iterator
  map<T, N>::lower_bound(const T& k) const
  {
    return map_.lower_bound(k);
  }


  template <class T, class N>
  std::pair<typename map<T, N>::iterator, bool>
  map<T, N>::insert(const std::pair<const T, N>& x)
  {
    return map_.insert(x);
  }

  template <class T, class N>
  void
  map<T, N>::insert(const map& other)
  {
    map_.insert(other.begin(), other.end());
  }

  template <class T, class N>
  template <class... Args>
  std::pair<typename map<T, N>::iterator, bool>
  map<T, N>::emplace(Args&&... args)
  {
    return map_.emplace(std::forward<Args>(args)...);
  }

  template <class T, class N>
  bool
  map<T, N>::empty() const
  {
    return map_.empty();
  }

  template <class T, class N>
  size_t
  map<T, N>::size() const
  {
    return map_.size();
  }

  template <class T, class N>
  N
  map<T, N>::take(const T& t)
  {
    typename map_type::iterator ires = xfind(t);
    N elt = ires->second;
    map_.erase(ires);
    return elt;
  }

  template <class T, class N>
  void
  map<T, N>::clear()
  {
    map_.clear();
  }

  template <class T, class N>
  std::ostream&
  operator<<(std::ostream& ostr, const map<T, N>& m)
  {
    return m.print(ostr);
  }

} // namespace misc
