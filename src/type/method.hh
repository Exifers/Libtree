/**
 ** \file type/method.hh
 ** \brief The class Method.
 */
#pragma once

#include <ast/method-dec.hh>
#include <type/function.hh>

namespace type
{

  // Forward declaration.
  class Class;

  /** \brief Method types.
   **
   ** Encapsulate the signature of a method, i.e. the type structures
   ** of both method's arguments and its result.  */
  class Method : public Function
  {
    /// A shortcut for the super type of this class.
    using super_type = Function;

  public:
    /** \brief Construct a FunEntry.
     **
     ** \param name     The method's identifier.
     ** \param owner    The type::Class owning this method.
     ** \param formals  The type structures of formal arguments.
     ** \param result   The type structure of what method returns.
     ** \param def      The method's definition site.  */
    Method(const misc::symbol& name, const Class* owner,
           const Record* formals, const Type& result, ast::MethodDec* def);

    /** \brief Destructor.
     **/
    virtual ~Method() = default;

    /// \name Visitors entry point.
    /** \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /** \} */

    /** \name Accessors.
     ** \{ */
    /// Return the method's name.
    misc::symbol name_get() const;
    /// Return thes method's owner (enclosing class).
    const Class* owner_get() const;
    /// Return the attribute's type.
    const Type& type_get() const;
    /// Return the method's definiton site.
    const ast::MethodDec* def_get() const;
    /// Return the method's definiton site.
    ast::MethodDec* def_get();

    /// Set the method's name.
    void name_set(const misc::symbol& name);
    /// set the method's definiton site.
    void def_set(ast::MethodDec* def);
    /** \} */

#warning // FIXME: Some code was deleted here (Special implementation of "compatible_with" for type::Method).

  private:
    /// Method's identifier.
    misc::symbol name_;
    /// The Class where this Method is defined.
    const Class* owner_;
    /// Method's definition site.
    ast::MethodDec* def_;
  };

} // namespace type

#include <type/method.hxx>
