/**
 ** \file misc/select-const.hh
 ** \brief Select between a non const or a const type.
 */

#pragma once

namespace misc
{

  /*------------------.
  | const selectors.  |
  `------------------*/

  /// Return \a T constified.
  template <typename T>
  struct constify_traits
  {
    using type = const T;
  };

  /// Return \a T as is.
  template <typename T>
  struct id_traits
  {
    using type = T;
  };



  /*------------------.
  | select_iterator.  |
  `------------------*/

  /// The iterator over a non const structure is plain iterator.
  template <typename T>
  struct select_iterator
  {
    using type = typename T::iterator;
  };

  /// The iterator over a const structure is a const_iterator.
  template <typename T>
  struct select_iterator<const T>
  {
    using type = typename T::const_iterator;
  };

} //namespace misc
