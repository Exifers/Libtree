/**
 ** \file object/binder.hh
 ** \brief Declaration of object::Binder.
 **/

#pragma once

#include <bind/binder.hh>

namespace object
{

  /** \brief Computing bindings with support for objects.
   **
   ** Inheritance is declared virtual to enable diamond inheritance with
   ** the OverfunBinder (src/object/overfun-binder.hh), inheriting from
   ** overload::Binder and object::Binder, both inheriting from bind::Binder.
   **/
  class Binder : virtual public bind::Binder
  {
  public:
    /// Super class type.
    using super_type = ::bind::Binder;
    /// Import all the overloaded operator() methods.
    using super_type::operator();

    /* The visiting methods. */
  public:
    // ---------------- //
    // Visiting /Exp/.  //
    // ---------------- //

    void operator()(ast::ForExp& e) override;

    /// Visit a Variable instantiation.
    void operator()(ast::SimpleVar& e) override;


    // ---------------- //
    // Visiting /Ty/.  //
    // ---------------- //

    /// Visit a type name.
    void operator()(ast::NameTy& e) override;

    /// Visit a class definition.
    void operator()(ast::ClassTy& e) override;


    // ---------------- //
    // Visiting /Dec/.  //
    // ---------------- //

    /// Check a set of definitions: unique names, browse headers, then bodies.
    template <class D>
    void decs_visit(ast::AnyDecs<D>& e);

    /// Check a Function declaration header.
    template <class D>
    void visit_dec_header(D& e);

    /// Check a Function declaration body.
    template <class D>
    void visit_dec_body(D& e);

    // Visit a variable declaration.
    void operator()(ast::VarDec&) override;

    /// Visit a chunk of Function declarations.
    void operator()(ast::FunctionDecs&) override;

    /// No longer used.
    void operator()(ast::MethodDec&) override;

  private:
    /// Are we (immediately) within a class definition?
    ///
    /// This predicate is used to prevent the bindings of VarDecs that
    /// are direct children of a ClassTy and which represent
    /// attributes of that class definition; the binding of these
    /// attributes is deferred to the type-checking phase (as for
    /// records' fields).  This predicate should be false within a
    /// non-ClassTy node declaring variables, even if that node
    /// belongs (indirectly) to the subtree of a ClassTy.
    bool within_class_ty_ = false;

    /// Are we (immediately) within a method definition?
    ///
    /// This predicate is used to determine whether `self' is a valid
    /// variable.  This is only the case for nodes that belong to the
    /// subtree of a MethodDec node, except for FunctionDec and
    /// ClassTy subtrees, which ``reset'' the context.
    bool within_method_dec_ = false;
  };

} // namespace object
