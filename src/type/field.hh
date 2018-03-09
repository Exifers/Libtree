/**
 ** \file type/field.hh
 ** \brief The class Field (of a record type).
 */
#pragma once

#include <misc/symbol.hh>
#include <type/fwd.hh>
#include <type/type.hh>

namespace type
{

  /** \brief The base type for Record fields.
   **
   ** Very much like Named, but it is *not* a Type. */
  class Field
  {
    /** \name Destructors
     ** \{ */
  public:
    virtual ~Field() = default;
    /** \} */

    /** \name Ctor & dtor.
     ** \{ */
    /** \brief Construct a Field.
     ** \param name field's identifier.
     ** \param type field's type. */
    Field(misc::symbol name, const Type& type);
    /** \} */

    /** \name Accessors.
     ** \{ */
    /// Return the field's name.
    misc::symbol name_get() const;
    /// Return the field's type.
    const Type& type_get() const;
    /** \} */

  protected:
    /// Field's identifier.
    misc::symbol name_;

    /// Field's type.
    const Type& type_;
  };

} // namespace type

#include <type/field.hxx>
