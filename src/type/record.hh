/**
 ** \file type/record.hh
 ** \brief The class Record.
 */
#pragma once

#include <vector>

#include <misc/indent.hh>
#include <misc/symbol.hh>
#include <type/field.hh>
#include <type/fwd.hh>
#include <type/type.hh>

namespace type
{

  /** \brief Record types.
   **
   ** List of Field s. */
  class Record : public Type
  {
    /// \name Visitors entry point.
    /// \{ */
  public:
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Field elementary manipulation.
     ** \{ */
    /// Return the type associated to \a key.
    const Type* field_type(const misc::symbol key) const;
    /** \brief Return the index of the field associated to \a key.
     **
     ** The index of a field is its position in the list. */
    int field_index(const misc::symbol key) const;
    /** \} */

    /** \name Internal Field list manipulators.
     ** \{ */
    /// List of Field's.
    using fields_type = std::vector<Field>;
    /// Return the Field list stored in this (read only).
    const fields_type& fields_get() const;

    /// Add an already existing Field to the list.
    void field_add(const Field& field);
    /// Create a Field then add it to the list.
    void field_add(const misc::symbol name, const Type& type);

    /// Iterators over Field's.
    using const_iterator = fields_type::const_iterator;
    const_iterator begin() const;
    const_iterator end() const;
    /** \} */

  // FIXME: Some code was deleted here (Inherited method).

  protected:
    /// Fields list.
    fields_type fields_;
  };

} // namespace type

#include <type/record.hxx>
