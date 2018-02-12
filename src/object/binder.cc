/**
 ** \file object/binder.cc
 ** \brief Implementation of object::Binder.
 */

#include <ast/all.hh>
#include <object/binder.hh>

namespace object
{

  /*---------.
  | Visits.  |
  `---------*/

  /* Handle the case of `self'.  If the SimpleVar is not defined, we only
     throw an error if it is not `self`, or if we are not inside a method.
     Variable `self' will have a meaningful definition after the object
     constructs have been desugared.  */

  void
  Binder::operator()(ast::SimpleVar& e)
  {
  // FIXME: Some code was deleted here.
  }

  // Handle the case of `Object'.
  void
  Binder::operator()(ast::NameTy& e)
  {
  // FIXME: Some code was deleted here.
  }


  /*---------------.
  | Visiting Exp.  |
  `---------------*/

  void
  Binder::operator()(ast::ForExp& e)
  {
    bool saved_within_class_ty = within_class_ty_;
    within_class_ty_ = false;
    super_type::operator()(e);
    within_class_ty_= saved_within_class_ty;
  }


  /*-------------------.
  | Visiting ClassTy.  |
  `-------------------*/

  void
  Binder::operator()(ast::ClassTy& e)
  {
    scope_begin();
    e.super_get().accept(*this);
    bool saved_within_class_ty = within_class_ty_;
    within_class_ty_ = true;
    bool saved_within_method_dec = within_method_dec_;
    within_method_dec_ = false;
    e.decs_get().accept(*this);
    within_method_dec_ = saved_within_method_dec;
    within_class_ty_= saved_within_class_ty;
    scope_end();
  }

  /*---------------.
  | Visiting Dec.  |
  `---------------*/

  void
  Binder::operator()(ast::VarDec& e)
  {
    if (within_class_ty_)
      {
        within_class_ty_ = false;
        // Don't bind class attributes.
        super_type::super_type::operator()(e);
        within_class_ty_ = true;
      }
    else
      // But still bind other variable declarations.
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::FunctionDecs& e)
  {
    decs_visit<ast::FunctionDec>(e);
  }

  template <class D>
  void
  Binder::decs_visit(ast::AnyDecs<D>& e)
  {
    // Shorthand.
    using decs_type = ast::AnyDecs<D>;
  // FIXME: Some code was deleted here (Two passes: once on headers, then on bodies).
  }

  // This trampoline is needed, since `virtual' and `template' cannot
  // be mixed.
  template <>
  void
  Binder::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e)
  {
    super_type::visit_dec_header<ast::FunctionDec>(e);
  }

  // Compute the bindings of this function's body.
  template <>
  void
  Binder::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e)
  {
    bool saved_within_class_ty = within_class_ty_;
    within_class_ty_ = false;
    bool saved_within_method_dec = within_method_dec_;
    within_method_dec_ = false;
    super_type::visit_dec_body<ast::FunctionDec>(e);
    within_method_dec_ = saved_within_method_dec;
    within_class_ty_= saved_within_class_ty;
  }

  /* We can't bind methods definitions without types, so we don't
     store them.  Nonetheless, object::Binder must still recurse
     through the children of ast::MethodDecs to bind other names.

     Note that as we defer the binding of methods to the
     type-checkimg, there is no need to visit method in two-pass (like
     bind::Binder does for functions for instance).  */
  void
  Binder::operator()(ast::MethodDec& e)
  {
    scope_begin();
    bool saved_within_class_ty = within_class_ty_;
    within_class_ty_ = false;
    bool saved_within_method_dec = within_method_dec_;
    within_method_dec_ = true;
    ast::DefaultVisitor::operator()(static_cast<ast::FunctionDec&>(e));
    within_method_dec_ = saved_within_method_dec;
    within_class_ty_= saved_within_class_ty;
    scope_end();
  }

} // namespace object
