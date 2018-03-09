/**
 ** \file type/attribute.hh
 ** \brief The class Attribute (of a class type).
 */
#pragma once

#include <ast/var-dec.hh>

namespace type
{


  /** \brief The base object for Class attributes.
   **
   ** Very much like Named, but it is *not* a Type. */
  class Attribute
  {
    /** \name Destructor.
     ** \{ */
  public:
    virtual ~Attribute() = default;
    /** \} */

    /** \name Constructor.
     ** \{ */
  public:
    /** \brief Construct a Attribute.
     ** \param def attribute's definition site.*/
    Attribute(const ast::VarDec* def);
    /** \} */

    /** \name Accessors.
     ** \{ */
  public:
    /// Return the attribute's name.
    misc::symbol name_get() const;
    /// Return the attribute's type.
    const Type& type_get() const;
    /// Return attribute's definition site.
    const ast::VarDec* def_get() const;
    /// Set the attribute's definition site.
    void def_set(const ast::VarDec* def);
    /** \} */

  private:
    const ast::VarDec* def_;
  };

} // namespace type

#include <type/attribute.hxx>
