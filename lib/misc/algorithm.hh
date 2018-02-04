/**
 ** \file misc/algorithm.hh
 ** \brief Some syntactic sugar to look for things in STL containers.
 */

#pragma once

#include <iosfwd>

namespace misc
{

  /// Invoke delete on all the members of \a c, and clear it.
  template <typename Container>
  void
  deep_clear(Container& c);

  /// Find \a v in the whole \a c.
  template <typename Container>
  inline typename Container::const_iterator
  find(const Container& c, const typename Container::value_type& v);

  /// Find \a v in the whole \a c.
  template <typename Container>
  inline typename Container::iterator
  find(Container& c, const typename Container::value_type& v);

  /// Apply \a f to all the members of \a c, and return it.
  template <typename Container, typename Functor>
  inline Functor&
  for_each(Container& c, Functor& v);

  /// Is \a v member of \a c?
  template <typename Container>
  inline bool
  has(const Container& c, const typename Container::value_type& v);

  /// Insert or update \a key -> \a value in \a map, return iterator to it.
  template <typename Map>
  typename Map::iterator
  put(Map& map,
      const typename Map::key_type& key,
      const typename Map::mapped_type& value);

} // namespace misc

#include <misc/algorithm.hxx>
