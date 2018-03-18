/**
 ** \file object/type-checker.cc
 ** \brief Implementation for object/type-checker.hh.
 */

#include <iostream>
#include <sstream>

#include <ast/all.hh>
#include <object/type-checker.hh>
#include <type/types.hh>

namespace object
{

  TypeChecker::TypeChecker()
    : super_type()
    , current_(nullptr)
    , within_methoddec_body_p_(false)
  {
    // Reset the subclasses of Object.  This is required if several
    // trees are processed during the compilation.
    type::Class::object_instance().subclasses_clear();

    // `self' variables are the only valid variables having a null
    // declaration site.  Use this property to tag them as read-only.
#warning // FIXME: Some code was deleted here.
  }


  /*--------------------------.
  | The core of the visitor.  |
  `--------------------------*/

  /*-----------------.
  | Visiting /Var/.  |
  `-----------------*/

  void
  TypeChecker::operator()(ast::SimpleVar& e)
  {
#warning // FIXME: Some code was deleted here.
  }

  void
  TypeChecker::operator()(ast::FieldVar& e)
  {
    const type::Type* def_type = nullptr;
#warning // FIXME: Some code was deleted here (Grab type).
    auto class_type = dynamic_cast<const type::Class*>(&def_type->actual());

    if (class_type)
      {
#warning // FIXME: Some code was deleted here.
      }
    else
      super_type::operator()(e);
  }


  /*----------------.
  | Visiting /Ty/.  |
  `----------------*/

  // Handle the case of `Object'.
  void
  TypeChecker::operator()(ast::NameTy& e)
  {
#warning // FIXME: Some code was deleted here.
  }


  /*-----------------.
  | Visiting /Exp/.  |
  `-----------------*/

  void
  TypeChecker::operator()(ast::IfExp& e)
  {
    // We want to handle the following case
    // let
    //   class A {}
    //   class B extends A { method print() = () }
    //   var a :=
    //     if 1 then
    //       new B
    //     else
    //       new A
    // in
    //    a.print() /* error */
    // end
#warning // FIXME: Some code was deleted here.
  }

  void
  TypeChecker::operator()(ast::OpExp& e)
  {
    // We want to only compare equal static object types.
    // Otherwise, the desugarer emits wrong code on:
    //
    // let
    //   class A {}
    //   class B extends A {}
    //   var a := new A
    //   var b := new B
    // in
    //   a = b
    // end
#warning // FIXME: Some code was deleted here.
  }

  void
  TypeChecker::operator()(ast::ObjectExp& e)
  {
#warning // FIXME: Some code was deleted here.
  }

  void
  TypeChecker::operator()(ast::MethodCallExp& e)
  {
#warning // FIXME: Some code was deleted here.
  }


  /*-----------------.
  | Visiting /Dec/.  |
  `-----------------*/

  /*--------------------.
  | Visiting TypeDecs.  |
  `--------------------*/

  void
  TypeChecker::operator()(ast::TypeDecs& e)
  {
    // Visit the header and the body of the typedecs, as in
    // type::TypeChecker.
    super_type::operator()(e);

    // However, class members are not considered part of the body of
    // their class here; they are processed separately to allow valid
    // uses of the class from its members.
    for (ast::TypeDec* typedec : e.decs_get())
      {
        ast::Ty& ty = typedec->ty_get();
        if (auto classty = dynamic_cast<ast::ClassTy*>(&ty))
          visit_dec_members(*classty);
      }
  }


  /*----------------------.
  | Visiting MethodDecs.  |
  `----------------------*/

  void
  TypeChecker::operator()(ast::MethodDecs& e)
  {
    // Two passes: once on headers, then on bodies.
    for (ast::MethodDec* m : e.decs_get())
      visit_dec_header(*m);
    for (ast::MethodDec* m : e.decs_get())
      visit_dec_body(*m);
  }

  // Store the type of this method.
  void
  TypeChecker::visit_dec_header(ast::MethodDec& e)
  {
    assertion(current_);

#warning // FIXME: Some code was deleted here.

    // Check for multiple definitions in the current class.
    for (const type::Method* m : current_->meths_get())
      if (m->name_get() == e.name_get())
        return error(e, "method multiply defined", e.name_get());

    // Check for signature conformance w.r.t. super class, if applicable.
    const type::Method* super_meth_type =
      dynamic_cast<const type::Method*>(current_->meth_type(e.name_get()));
#warning // FIXME: Some code was deleted here.
  }


  // Type check this method's body.
  void
  TypeChecker::visit_dec_body(ast::MethodDec& e)
  {
    precondition(!within_methoddec_body_p_);
    within_methoddec_body_p_ = true;
    visit_routine_body<type::Method>(e);
    within_methoddec_body_p_ = false;
  }


  /*---------------.
  | Visit VarDec.  |
  `---------------*/

  void
  TypeChecker::operator()(ast::VarDec& e)
  {
    super_type::operator()(e);
    /* If we are inside a class declaration, but not within a
       method's body, then E is an attribute: record it into the
       CURRENT_ class.  */
    if (e.init_get() && current_ && !within_methoddec_body_p_)
      {
        assertion(e.init_get());

        if (current_->attr_type(e.name_get()))
          error(e, "attribute multiply defined", e.name_get());
        else
          current_->attr_add(&e);
      }
  }


  /*-------------.
  | Visit /Ty/.  |
  `-------------*/

  // Don't handle members, as visit_dec_members is in charge of this task.
  void
  TypeChecker::operator()(ast::ClassTy& e)
  {
#warning // FIXME: Some code was deleted here (Create class).

#warning // FIXME: Some code was deleted here (Set the type of the super class).

#warning // FIXME: Some code was deleted here (Recursively update the list of subclasses of the super classes).
  }

  // Handle the members of a class.
  void
  TypeChecker::visit_dec_members(ast::ClassTy& e)
  {
    const type::Type* type = nullptr;
#warning // FIXME: Some code was deleted here.

    assertion(type);
    auto class_type = dynamic_cast<const type::Class*>(type);
    assertion(class_type);

    type::Class* saved_class_type = current_;
    // Make the type writable, so that we can add references to the
    // types of the members.
    current_ = const_cast<type::Class*>(class_type);
    /* Even if it were the case, pretend we are not within a method,
       since we are inside a class definition, which ``overrides'' any
       (outer) enclosing method.  */
    bool saved_within_methoddec_body_p = within_methoddec_body_p_;
    within_methoddec_body_p_ = false;
    e.decs_get().accept(*this);
    // Set back the status we had before we visited the members.
    within_methoddec_body_p_ = saved_within_methoddec_body_p;
    current_ = saved_class_type;
  }

} // namespace object
