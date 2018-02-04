/**                                                     -*- C++ -*-
 ** \file misc/vector.hxx
 ** \brief Implementation of misc::vector.
 */

#pragma once

#include <ostream>

#include <misc/contract.hh>

namespace misc
{

  template <class T>
  vector<T>::vector()
  {}

  template <class T>
  vector<T>::vector(const T& t)
  {
    this->push_back(t);
  }

  template <class T>
  vector<T>::vector(const T& t1, const T& t2)
  {
    this->push_back(t1);
    this->push_back(t2);
  }

  template <class T>
  vector<T>::vector(const T& t, const vector<T>& v)
  {
    this->push_back(t);
    this->insert(this->end(), v.begin(), v.end());
  }

  template <class T>
  vector<T>::vector(std::initializer_list<T> l)
  {
    this->insert(this->begin(), l.begin(), l.end());
  }

  template <class T>
  template <class InputIterator>
  vector<T>::vector(InputIterator b, InputIterator e)
    : super_type(b, e)
  {}

  template <class T>
  template <class C>
  vector<T>::vector(const C& c)
    : super_type(c.begin(), c.end())
  {}

  template <class T>
  bool
  vector<T>::has(const T& data) const
  {
    return std::find(this->begin(), this->end(), data) != this->end();
  }

  template <class T>
  inline
  typename std::vector<T>::iterator
  vector<T>::prepend(const vector<T>& v)
  {
    auto it = this->insert(this->begin(), v.begin(), v.end());
    return it;
  }

  template <class T>
  inline
  typename std::vector<T>::iterator
  vector<T>::prepend(const vector<T>&& v)
  {
    auto it = this->insert(this->begin(), v.begin(), v.end());
    return it;
  }

  template <class T>
  inline
  typename std::vector<T>::iterator
  vector<T>::append(const vector<T>& v)
  {
    auto it = this->insert(this->end(), v.begin(), v.end());
    return it;
  }

  template <class T>
  inline
  typename std::vector<T>::iterator
  vector<T>::append(const vector<T>&& v)
  {
    auto it = this->insert(this->end(), v.begin(), v.end());
    return it;
  }

  template <class T>
  inline
  vector<T>
  vector<T>::operator+(const vector<T>& v) const
  {
    vector<T> res = *this;
    return res += v;
  }

  template <class T>
  inline
  vector<T>&
  vector<T>::operator+=(const vector<T>& v)
  {
    this->insert(this->end(), v.begin(), v.end());
    return *this;
  }

  template <class T>
  template <typename Iterator>
  inline
  typename std::vector<T>::iterator
  vector<T>::position_append(const vector<T>& v, Iterator it)
  {
    auto new_it = this->insert(it, v.begin(), v.end());
    return new_it;
  }

  template <class T>
  template <typename Iterator>
  inline
  typename std::vector<T>::iterator
  vector<T>::position_append(const vector<T>&& v, Iterator it)
  {
    auto new_it = this->insert(it, v.begin(), v.end());
    return new_it;
  }

  template <class T>
  inline
  vector<T>&
  vector<T>::remove(const T& data)
  {
    precondition(has(data));
    this->erase(std::find(this->begin(), this->end(), data));
    return *this;
  }

  template <class T>
  std::ostream&
  vector<T>::dump(std::ostream& ostr) const
  {
    for (typename super_type::const_iterator i = this->begin();
         i != this->end(); ++i)
      ostr << (i == this->begin() ? "" : ", ") << *i;
    return ostr;
  }

  template <class T>
  std::ostream&
  operator<<(std::ostream& ostr, const vector<T>& v)
  {
    return v.dump(ostr);
  }

  template <typename T>
  auto append_and_move(std::vector<T>& v1, std::vector<T>&& v2)
  {
    auto it = v1.insert(v1.end(),
               make_move_iterator(v2.begin()),
               make_move_iterator(v2.end()));
    v2.clear();
    return it;
  }

  template <typename T>
  auto append_and_move(std::vector<T>& v1, std::vector<T>& v2)
  {
    auto it = v1.insert(v1.end(),
               make_move_iterator(v2.begin()),
               make_move_iterator(v2.end()));
    v2.clear();
    return it;
  }

  template <typename T>
  auto prepend_and_move(std::vector<T>& v1, std::vector<T>&& v2)
  {
    auto it = v1.insert(v1.begin(),
               make_move_iterator(v2.begin()),
               make_move_iterator(v2.end()));
    v2.clear();
    return it;
  }

  template <typename T>
  auto prepend_and_move(std::vector<T>& v1, std::vector<T>& v2)
  {
    auto it = v1.insert(v1.begin(),
               make_move_iterator(v2.begin()),
               make_move_iterator(v2.end()));
    v2.clear();
    return it;
  }

  template <typename T, typename Iterator>
  auto position_append_and_move(std::vector<T>& v1,
                                Iterator v1_iterator,
                                std::vector<T>&& v2)
  {
    auto it = v1.insert(v1_iterator,
               make_move_iterator(v2.begin()),
               make_move_iterator(v2.end()));
    v2.clear();
    return it;
  }

  template <typename T, typename Iterator>
  auto position_append_and_move(std::vector<T>& v1,
                                Iterator v1_iterator,
                                std::vector<T>& v2)
  {
    auto it = v1.insert(v1_iterator,
               make_move_iterator(v2.begin()),
               make_move_iterator(v2.end()));
    v2.clear();
    return it;
  }

} // namespace misc
