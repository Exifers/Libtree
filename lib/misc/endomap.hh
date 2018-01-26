/**
 ** \file misc/endomap.hh
 ** \brief Declaration of misc::endomap.
 */

#pragma once

#include <list>
#include <map>

#include <misc/map.hh>

namespace misc
{

  /** \brief A renaming mapping defaulting to identity:
      Mapping a class with itself (endomorphism).
      Unless a value is already mapped onto another, map it to itself
      if nonstrict. This is a special case of std::map. */
  template <class T>
  class endomap : public map<T, T>
  {
  public:
    /// Super class type.
    using super_type = map<T, T>;

    // Import overloaded virtual functions.
    using super_type::operator[];
    using super_type::operator();

    enum class strictness_type
      {
        /// Querying about an unknown identifier returns itself.
        nonstrict,
        /// Querying about an unknown identifier is an error.
        strict
      };

    /// \name Constructors and destructor.
    /// \{
    endomap();
    virtual ~endomap() = default;
    /// \}

    /// Return a duplicate of \a this.
    endomap* clone() const override;

    /// Return a reference to the value associated to \a t.
    ///
    /// If \a t was not inserted before, then, contrary to std::map,
    /// we insert t -> t into the map, instead of `t -> T()'.  This
    /// spares the construction of a new T, which may have nasty
    /// effects if this constructor has side effects (e.g.,
    /// incrementing a counter).
    virtual T& operator[](const T& t);

    /// Lookup for \a t, returning it if unknown.
    T operator()(const T& t) const override;


  protected:
    /// If strict, queries for an unknown (unmapped) Identifier is an error.
    strictness_type strictness_;
  };

} // namespace misc

#include <misc/endomap.hxx>
