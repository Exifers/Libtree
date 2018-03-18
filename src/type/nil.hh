/**
 ** \file type/nil.hh
 ** \brief The Nil type.
 */
#pragma once

#include <type/fwd.hh>
#include <type/type.hh>

namespace type
{

  /*------.
  | Nil.  |
  `------*/

  class Record;

  /// The builtin type of `nil'.
  /// The Nil type is the type of a `nil` expression.
  class Nil : public Type
  {
  public:
    /// \name Visitors entry point.
    /** \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /** \} */

    bool compatible_with(const Type& other) const override;

    /// Get the associated record type.
    const Type* record_type_get() const;

    /// Set the record type used with the nil.
    void set_record_type(const Type& type) const;

  private:
    /// The actual record_type that it represents.
    /// Nil types are either compatible with `type::Record` or `type::Class`.
    /// record_type represents the actual type that the `nil` was meant to be
    /// used with.
    mutable const Type* record_type_ = nullptr;
  };

} // namespace type
