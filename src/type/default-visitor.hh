/**
 ** \file type/default-visitor.hh
 ** \brief Traverse a Type, doing nothing.
 */

#pragma once

#include <type/visitor.hh>

namespace type
{

  template <template <typename> class Const>
  class GenDefaultVisitor : public GenVisitor<Const>
  {
  public:
    /// Convenient abbreviation.
    template <typename Type>
    using const_t = typename Const<Type>::type;

    /// Super class type.
    using super_type = GenVisitor<Const>;

    // Import overloaded \c operator() methods.
    using super_type::operator();

    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a default visitor.
    GenDefaultVisitor();
    /// Destroy a default visitor.
    virtual ~GenDefaultVisitor();
    /** \} */

    /** \name Visit basic types.
     ** \{ */
    void operator()(const_t<Nil>& e) override;
    void operator()(const_t<Void>& e) override;
    void operator()(const_t<Int>& e) override;
    void operator()(const_t<String>& e) override;
    /** \} */


    /** \name Visit composed types.
     ** \{ */
    void operator()(const_t<Named>& e) override;
    void operator()(const_t<Array>& e) override;
    void operator()(const_t<Record>& e) override;
    void operator()(const_t<Class>& e) override;
    void operator()(const_t<Function>& e) override;
    void operator()(const_t<Method>& e) override;
    /** \} */
  };

  /// Shorthand for a const visitor.
  using DefaultConstVisitor = GenDefaultVisitor<misc::constify_traits>;
  /// Shorthand for a non const visitor.
  using DefaultVisitor = GenDefaultVisitor<misc::id_traits>;

} // namespace type

#include <type/default-visitor.hxx>
