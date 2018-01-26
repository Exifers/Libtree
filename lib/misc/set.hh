/**
 ** \file misc/set.hh
 ** \brief misc::set: wrapper around std::set.
 **
 ** Set class is a std::set wrapper used to facilitate set
 ** operations such as '+' (union) and '-' and also redefine
 ** functions such as set_union, set_intersection etc. in
 ** order to be more specific and more simple to handle set for our
 ** purpose.
 **/

#pragma once

#include <algorithm>
#include <iosfwd>
#include <set>
#include <vector>

namespace misc
{

  template <typename K,
            typename C = std::less<K>,
            typename A = std::allocator<K>>
  /**
   ** \brief The class misc::set is wrapper around std::set.
   **
   ** Because Doxygen doesn't handle template
   ** parameters names mix we keep the shorter version,
   ** so K for Key, C for Compare and A for Allocator. */
  class set : public std::set<K, C, A>
  {
  public:

    /// \name typedefs
    /// \{
    using set_type = typename std::set<K, C, A>;

    using iterator = typename set_type::iterator;
    using const_iterator = typename set_type::const_iterator;
    using reverse_iterator = typename set_type::reverse_iterator;
    using const_reverse_iterator = typename set_type::const_reverse_iterator;
    using size_type = typename set_type::size_type;
    using const_reference = typename set_type::const_reference;
    /// \}

    /// \name constructor(s)/destructor.
    /// \{

    explicit set() = default;
    template <typename Iter>
    explicit set(Iter first, Iter last);

    /* Useful to convert a std::vector in set::set.  */
    explicit set(const std::vector<K> v);

    /// \}


    /** \name Element vs. set.
        \{ */

    /// Is \a k part of \a this set?
    bool has(const K& k) const;

    /** \brief Return the addition of \a data into \a this.
        \a data must not yet be part of \a this. */
    set operator+(const K& data) const;

    /** \brief Insert \a data in \a this.
        \a data must not yet be part of \a this. */
    set& operator+=(const K& data);

    /** \brief Return the removal of \a data into \a this.
        \a data must be part of \a this. */
    set operator-(const K& data) const;

    /** \brief Remove \a data from \a this.
        \a data must be part of \a this. */
    set& operator-=(const K& data);

    /// \}


    /** \name Set vs. set.
        \{ */

    /// Union with another set \a s.
    // FIXME: Deprecate this use, it ought to be direct sum.
    set operator+(const set<K, C, A>& s) const;

    /// In place union with another set \a s.
    set& operator+=(const set<K, C, A>& s);

    /// Subtraction with another set \a s.
    set operator-(const set<K, C, A>& s) const;

    /// In place subtraction with another set \a s.
    set& operator-=(const set<K, C, A>& s);

    /// Union with another set \a s.
    set operator|(const set& s) const;

    /// In place union with another set \a s.
    set& operator|=(const set& s);

    /// Intersection with another set \a s.
    set operator&(const set& s) const;

    /// In place intersection with another set \a s.
    set& operator&=(const set& s);

    /// \}
  }; // class set

  template <typename K, typename C, typename A>
  inline set<K, C, A>
  set_difference(const set<K, C, A>& s1,
                 const set<K, C, A>& s2);

  template <typename K, typename C, typename A>
  inline set<K, C, A>
  set_intersection(const set<K, C, A>& s1,
                   const set<K, C, A>& s2);

  template <typename K, typename C, typename A>
  inline set<K, C, A>
  set_union(const set<K, C, A>& s1,
            const set<K, C, A>& s2);


  /* Print a human-dump for debugging.

  Warning: this method requires that type Key overloads the operator
  '<<'.  If it is not the case do it or remove set print method
  and << operator (see below).  */
  template <typename K, typename C, typename A>
  inline std::ostream&
  operator<<(std::ostream& ostr, const set<K, C, A>& s);

  template <typename K, typename C, typename A>
  inline bool operator%(const K& k, const set<K, C, A>& s);

} // namespace misc

#include <misc/set.hxx>
