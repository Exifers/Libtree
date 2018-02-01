/**
 ** \file ast/any-decs.hh
 ** \brief Declaration of ast::AnyDecs.
 */

#pragma once

#include <vector>

#include <ast/decs.hh>

namespace ast
{

  template <typename D>
  /// Abstract a "list of D-declarations" node.
  class AnyDecs : public Decs
  {
  public:
    /// Define shorthand type for list of D-declarations.
    using Ds = std::vector<D*>;

    /** \name Ctor & dtor.
     ** \{ */
  public:
    /** \brief Construct an AnyDecs node with a list of D-declarations.
     ** \param location scanner position informations
     ** \param decs list of D-declarations */
    AnyDecs(const Location& location, Ds* decs);
    AnyDecs(const Location& location);

    /** \brief Destroys an AnyDecs node.
     **
     ** Free list and its content. */
    ~AnyDecs();

    /** \} */


    /** \name Visitors entry point.
     ** \{ */
  public:
    /// Accept a const visitor \a v.
    void accept(Visitor& v) override;

    /// Accept a non-const visitor \a v.
    void accept(ConstVisitor& v) const override;

    /** \} */


    /** \name Accessors.
     ** \{ */
  public:
    /** \brief Push \a d in front.
     ** \param d declaration to push */
    AnyDecs<D>& push_front(D& d);

    /** \brief Push \a d in back.
     ** \param d declaration to push */
    AnyDecs<D>& emplace_back(D& d);

    /// Access to list of D-declarations (read and write).
    Ds& decs_get();

    /// Access to list of D-declarations (read only).
    const Ds& decs_get() const;

    /** \} */

    // SWIG 2 does not understand C++11 constructs, such as data
    // member initializers.
# ifndef SWIG
  private:
    Ds* decs_ = new Ds();
# endif
  };

} // namespace ast

#include <ast/any-decs.hxx>
