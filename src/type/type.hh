/**
 ** \file type/type.hh
 ** \brief The class Type.
 */
#pragma once

#include <misc/xalloc.hh>
#include <type/fwd.hh>

namespace type
{

  /// Abstract a type.
  class Type
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Destroys a Type.
    virtual ~Type() = default;
    /** \} */


    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    virtual void accept(ConstVisitor& v) const = 0;
    /// Accept a non-const visitor \a v.
    virtual void accept(Visitor& v) = 0;
    /// \}


    /** \name Accessors.
     ** \{ */
    /// Return the actual type held by THIS.
    virtual const Type& actual() const;
    /** \} */

    /** \brief Whether two types are "compatible".
     **
     ** I.e., whether "a = b", "a <> b", "a := b" are correctly typed
     ** with a of type \a this, and b of type \a other).
     **
     ** By default two types are compatible (in the sense of "=" and "<>",
     ** not w.r.t. an order) only when they are equal.
     **
     ** In the case of assignment, "rec := nil" is valid, but "nil := rec"
     ** is not, which suggest that we should have a non commutative
     ** assignment specific compatibility check.  But since "nil := ..."
     ** is incorrect syntactically, that is not needed.
     */
    virtual bool compatible_with(const Type& other) const;
  };

  /** \brief Compare two Type s.
   **
   ** Return true if \a a and \a b are equivalent Tiger Types.  E.g.,
   ** if \a a and \a b are different but point to the same type, then
   ** return true. */
  bool operator==(const Type& lhs, const Type& rhs);
  /// !(a == b).
  bool operator!=(const Type& lhs, const Type& rhs);

  /// Hide actual types?  (i.e., print only the surface type?)
  extern const misc::xalloc<bool> hide_actual_types;

} // namespace type

#include <type/type.hxx>
