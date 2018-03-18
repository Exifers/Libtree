/**
 ** \file type/visitor.hh
 ** \brief Definition of type::Visitor.
 */
#pragma once

#include <misc/select-const.hh>
#include <type/fwd.hh>

namespace type
{

  /** \brief Root class of all Type visitors.
   **
   ** GenVisitor<CONSTIFY> is the root class of all Type visitors. */
  template <template <typename> class Const>
  class GenVisitor
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Convenient abbreviation.
    template <typename T>
    using const_t = typename Const<T>::type;

    /// Destroy a GenVisitor.
    virtual ~GenVisitor();
    /** \} */

    /// The entry point: visit \a e.
    virtual void operator()(const_t<Type>& e);
    virtual void operator()(const_t<Nil>&) = 0;
    virtual void operator()(const_t<Void>&) = 0;
    virtual void operator()(const_t<Int>&) = 0;
    virtual void operator()(const_t<String>&) = 0;
    virtual void operator()(const_t<Named>&) = 0;
    virtual void operator()(const_t<Array>&) = 0;
    virtual void operator()(const_t<Record>&) = 0;
    virtual void operator()(const_t<Class>&) = 0;
    virtual void operator()(const_t<Function>&) = 0;
    virtual void operator()(const_t<Method>&) = 0;

    /// Helper to visit nodes manipulated via a pointer.
    template <class E> void operator()(E* e);
  };

  /// Shorthand for a const visitor.
  using ConstVisitor = GenVisitor<misc::constify_traits>;
  /// Shorthand for a non const visitor.
  using Visitor = GenVisitor<misc::id_traits>;

} // namespace type

# include <type/visitor.hxx>
