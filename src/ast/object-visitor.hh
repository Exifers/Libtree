/**
 ** \file ast/object-visitor.hh
 ** \brief Provide default visits for object-related nodes.
 */

#pragma once

#include <ast/visitor.hh>

namespace ast
{
  /** GenObjectVisitor<CONSTNESS-SELECTOR> provides default visit
      methods for object-related nodes.  This class is meant to factor
      the code visiting object-related nodes.

      ast::GenObjectVisitor inherits virtually from ast::GenVisitor
      to allow diamond inheritance, notably for a ``compatibility''
      purpose with ast::GenDefaultVisitor.

      For instance, bind::Binder, a visitor that handles bindings for
      an AST without objects, inherits from ast::DefaultVisitor to
      factor default (``empty'') traversal implementations for
      non-object-related nodes, and from ast::ObjectVisitor for
      object-related nodes.

      \verbatim

                             /ast::Visitor/
                                   ^
                (virtual)          |          (virtual)
                    ,--------------+--------------.
                    |                             |
                    |                             |
          /ast::DefaultVisitor/         /ast::ObjectVisitor/
                    ^                             ^
                    |                             |
                    `--------------+--------------'
                                   |
                                   |
                              bind::Binder

      \endverbatim
  */
  template <template <typename> class Const>
  class GenObjectVisitor : virtual public GenVisitor<Const>
  {
  public:
    /// Super class type.
    using super_type = GenVisitor<Const>;

    // Import overloaded virtual functions.
    using super_type::operator();

    /// Convenient abbreviation.
    template <typename Type>
    using const_t = typename Const<Type>::type;

    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an object visitor.
    GenObjectVisitor();
    /// Destroy an object visitor.
    virtual ~GenObjectVisitor();
    /** \} */

    /// \name Object-related visits.
    /// \{
    void operator()(const_t<ClassTy>& e) override;

    void operator()(const_t<MethodDecs>& e) override;
    void operator()(const_t<MethodDec>& e) override;

    void operator()(const_t<MethodCallExp>& e) override;
    void operator()(const_t<ObjectExp>& e) override;
    /// \}
  };

  /// Shorthand for a const visitor.
  using ObjectConstVisitor = GenObjectVisitor<misc::constify_traits>;
  /// Shorthand for a non const visitor.
#ifdef SWIG
  %template() GenVisitor<misc::id_traits>;
  %template() GenObjectVisitor<misc::id_traits>;
#endif
  using ObjectVisitor = GenObjectVisitor<misc::id_traits>;

} // namespace ast

#include <ast/object-visitor.hxx>
