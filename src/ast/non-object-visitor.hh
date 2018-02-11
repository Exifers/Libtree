/**
 ** \file ast/non-object-visitor.hh
 ** \brief Provide aborting visits for object-related nodes.
 */

#pragma once

#include <ast/visitor.hh>

namespace ast
{
  /** GenNonObjectVisitor<CONSTNESS-SELECTOR> provides aborting visit
      methods for object-related nodes.  This class is meant to factor
      the code visiting object-related nodes in visitors bound to
      process AST \em without objects.

      ast::GenNonObjectVisitor inherits virtually from ast::GenVisitor
      to allow diamond inheritance, notably for a ``compatibility''
      purpose with ast::GenDefaultVisitor.

      For instance, type::TypeChecker, a visitor that checks the types
      of an AST without objects, inherits from ast::DefaultVisitor to
      factor default (``empty'') traversal implementations, and from
      ast::NonObjectVisitor to get an aborting behavior for
      object-related nodes.

      \verbatim

                             /ast::Visitor/
                                   ^
                (virtual)          |          (virtual)
                    ,--------------+--------------.
                    |                             |
                    |                             |
          /ast::DefaultVisitor/         /ast::NonObjectVisitor/
                    ^                             ^
                    |                             |
                    `--------------+--------------'
                                   |
                                   |
                           type::TypeChecker

      \endverbatim
  */
  template <template <typename> class Const>
  class GenNonObjectVisitor : virtual public GenVisitor<Const>
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
    /// Construct a non-object visitor.
    GenNonObjectVisitor();
    /// Destroy a non-object visitor.
    virtual ~GenNonObjectVisitor();
    /** \} */

    /// \name Object-related visits.
    ///
    /// The methods should not be used, since this visitor is for the
    /// non-object flavor of the language.
    /// \{
    void operator()(const_t<ClassTy>& e) override;

    void operator()(const_t<MethodDecs>& e) override;
    void operator()(const_t<MethodDec>& e) override;

    void operator()(const_t<MethodCallExp>& e) override;
    void operator()(const_t<ObjectExp>& e) override;
    /// \}
  };

  /// Shorthand for a const visitor.
  using NonObjectConstVisitor = GenNonObjectVisitor<misc::constify_traits>;
  /// Shorthand for a non const visitor.
#ifdef SWIG
  %template() GenVisitor<misc::id_traits>;
  %template() GenNonObjectVisitor<misc::id_traits>;
#endif
  using NonObjectVisitor = GenNonObjectVisitor<misc::id_traits>;

} // namespace ast

#include <ast/non-object-visitor.hxx>
