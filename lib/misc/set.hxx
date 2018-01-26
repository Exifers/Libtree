/**
 ** \file misc/set.hxx
 ** \brief misc::set: wrapper around std::set.
 **/

#pragma once

#include <algorithm>
#include <ostream>

#include <misc/contract.hh>
#include <misc/set.hh>

namespace misc
{

  template <class K, class C, class A>
  template <typename Iter>
  inline
  set<K, C, A>::set(Iter first, Iter last)
  {
    this->insert(first, last);
  }

  /* Useful to convert a std::vector in set::set.  */
  template <class K, class C, class A>
  inline
  set<K, C, A>::set(const std::vector<K> v)
  {
    for (const K& x : v)
      this->insert(x);
  }

  template <class K, class C, class A>
  inline
  bool
  set<K, C, A>::has(const K& k) const
  {
    return set_type::find(k) != this->end();
  }

  /* \brief Return the addition of \a data into \a this.
      \a data must not yet be part of \a this. */
  template <class K, class C, class A>
  inline
  set<K, C, A>
  set<K, C, A>::operator+(const K& data) const
  {
    precondition(!(data % *this));
    set<K, C, A> res(*this);
    res.insert(data);
    return res;
  }

  /* \brief Insert \a data in \a this.
      \a data must not yet be part of \a this. */
  template <class K, class C, class A>
  inline
  set<K, C, A>&
  set<K, C, A>::operator+=(const K& data)
  {
    precondition(!(data % *this));
    this->insert(data);
    return *this;
  }

  /* \brief Return the removal of \a data into \a this.
      \a data must be part of \a this. */
  template <class K, class C, class A>
  inline
  set<K, C, A>
  set<K, C, A>::operator-(const K& data) const
  {
    precondition(data % *this);
    set<K, C, A> res(*this);
    res.erase(data);
    return res;
  }

  /* \brief Remove \a data from \a this.
      \a data must be part of \a this. */
  template <class K, class C, class A>
  inline
  set<K, C, A>&
  set<K, C, A>::operator-=(const K& data)
  {
    precondition(data % *this);
    this->erase(data);
    return *this;
  }


  // Union with another set \a s.
  // FIXME: Deprecate this use, it ought to be direct sum.
  template <class K, class C, class A>
  inline
  set<K, C, A>
  set<K, C, A>::operator+(const set<K, C, A>& s) const
  {
    return set_union(*this, s);
  }

  // In place union with another set \a s.
  template <class K, class C, class A>
  inline
  set<K, C, A>&
  set<K, C, A>::operator+=(const set<K, C, A>& s)
  {
    return *this = *this + s;
  }

  // Subtraction with another set \a s.
  template <class K, class C, class A>
  inline
  set<K, C, A>
  set<K, C, A>::operator-(const set<K, C, A>& s) const
  {
    return set_difference(*this, s);
  }

  // In place subtraction with another set \a s.
  template <class K, class C, class A>
  inline
  set<K, C, A>&
  set<K, C, A>::operator-=(const set<K, C, A>& s)
  {
    *this = *this - s;
    return *this;
  }

  // Union with another set \a s.
  template <class K, class C, class A>
  inline
  set<K, C, A>
  set<K, C, A>::operator|(const set<K, C, A>& s) const
  {
    return *this + s;
  }

  // In place union with another set \a s.
  template <class K, class C, class A>
  inline
  set<K, C, A>&
  set<K, C, A>::operator|=(const set<K, C, A>& s)
  {
    return *this += s;
  }

  // Intersection with another set \a s.
  template <class K, class C, class A>
  inline
  set<K, C, A>
  set<K, C, A>::operator&(const set<K, C, A>& s) const
  {
    return set_intersection(*this, s);
  }

  // In place intersection with another set \a s.
  template <class K, class C, class A>
  inline
  set<K, C, A>&
  set<K, C, A>::operator&=(const set<K, C, A>& s)
  {
    return *this = *this & s;
  }


  template <class K, class C, class A>
  inline
  set<K, C, A>
  set_difference(const set<K, C, A>& s1, const set<K, C, A>& s2)
  {
    set<K, C, A> res;
    // Specifying the key_comp to use is required: without it, the
    // first set is properly ordered using its own key_comp, but
    // neither the second set nor the resulting set are ordering
    // using it.  Even if s1, s2, and res do use the same Compare!
    std::set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(),
                        inserter(res, res.begin()), s1.key_comp());
    return res;
  }

  template <class K, class C, class A>
  inline
  set<K, C, A>
  set_intersection(const set<K, C, A>& s1, const set<K, C, A>& s2)
  {
    set<K, C, A> res;
    std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
                          inserter(res, res.begin()), s1.key_comp());
    return res;
  }

  template <class K, class C, class A>
  inline
  set<K, C, A>
  set_union(const set<K, C, A>& s1, const set<K, C, A>& s2)
  {
    set<K, C, A> res;
    std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),
                   inserter(res, res.begin()), s1.key_comp());
    return res;
  }


  template <class K, class C, class A>
  inline
  std::ostream&
  operator<<(std::ostream& ostr, const set<K, C, A>& s)
  {
    for (typename set<K, C, A>::const_iterator i = s.begin(); i != s.end();)
      {
        ostr << *i;
        if (++i != s.end())
          ostr << ", ";
      }
    return ostr;
  }

  template <class K, class C, class A>
  inline
  bool
  operator%(const K& k, const set<K, C, A>& s)
  {
    return s.has(k);
  }

} // namespace misc
