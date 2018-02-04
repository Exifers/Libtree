/**
 ** \file misc/vector.hh
 ** \brief Declaration of misc::vector
 */

#pragma once

#include <algorithm>
#include <iosfwd>
#include <vector>

namespace misc
{

  template <class Ident_>
  class vector : public std::vector<Ident_>
  {
  public:
    /// Super class type.
    using super_type = std::vector<Ident_>;

    /// \name Constructors and destructor.
    /// \{
    /// Build an empty vector.
    vector();

    /// Build a one-element vector.
    vector(const Ident_& t);

    /// Build a two-element vector.
    vector(const Ident_& t1, const Ident_& t2);

    /// Concat an element and a vector.
    vector(const Ident_& t, const vector& v);

    // Build a vector from an initializer list.
    vector(std::initializer_list<Ident_> l);

    /// Build a vector from 2 iterators.
    template <class InputIterator>
    vector(InputIterator b, InputIterator e);

    /// Build a vector fro, another container.
    template <class C> vector(const C& c);
    /// \}

    /// \name Content management.
    /// \{
    /// Is \a data part of \a this vector?
    bool has(const Ident_& data) const;

    /// Prepend \a v into \a this and return the new iterator.
    typename super_type::iterator
    prepend(const vector<Ident_>& v);
    typename super_type::iterator
    prepend(const vector<Ident_>&& v);

    /// Append \a v into \a this and return the new iterator.
    typename super_type::iterator
    append(const vector<Ident_>& v);
    typename super_type::iterator
    append(const vector<Ident_>&& v);

    /// Append \a v into \a this.
    vector operator+(const vector& v) const;
    /// Append \a v into \a this.
    vector& operator+=(const vector& v);

    /// Append \a v into \a this from it and return the new iterator.
    template <typename Iterator>
    typename super_type::iterator
    position_append(const vector& v, Iterator it);
    template <typename Iterator>
    typename super_type::iterator
    position_append(const vector&& v, Iterator it);

    /** \brief Remove \a data from \a this.
        \a data must be part of \a this. */
    vector& remove(const Ident_& data);
    /// \}

    virtual std::ostream& dump(std::ostream& ostr) const;
  };

  /// Output \a v onto \a ostr.
  template <class Ident_>
  std::ostream& operator<<(std::ostream& ostr, const vector<Ident_>& v);


  template <typename T>
  auto append_and_move(std::vector<T>& res, std::vector<T>&& to_append);

  template <typename T>
  auto append_and_move(std::vector<T>& res, std::vector<T>& to_append);

  template <typename T>
  auto prepend_and_move(std::vector<T>& res, std::vector<T>&& to_prepend);

  template <typename T>
  auto prepend_and_move(std::vector<T>& res, std::vector<T>& to_prepend);

  template <typename T, typename Iterator>
  auto position_append_and_move(std::vector<T>& res,
                                Iterator res_iterator,
                                std::vector<T>&& to_append);

  template <typename T, typename Iterator>
  auto position_append_and_move(std::vector<T>& res,
                                Iterator res_iterator,
                                std::vector<T>& to_append);

} // namespace misc

#include <misc/vector.hxx>
