/**
 ** \file bind/binder.hxx
 ** \brief Inline methods of bind::Binder.
 **/

#pragma once

#include <bind/binder.hh>

namespace bind
{

  /*-----------------.
  | Error handling.  |
  `-----------------*/

#warning // FIXME: Some code was deleted here (Error reporting).

  /*-------------------.
  | Definition sites.  |
  `-------------------*/

#warning // FIXME: Some code was deleted here.

  /*------------------.
  | Visiting /Decs/.  |
  `------------------*/

  template <class D>
  void
  Binder::decs_visit(ast::AnyDecs<D>& e)
  {
    auto v = e.decs_get();
    for (auto it = v.begin(); it != v.end(); it++)
      visit_dec_header<D>(**it);
    for (auto it = v.begin(); it != v.end(); it++)
      visit_dec_body<D>(**it);
  }

  /* These specializations are in bind/binder.hxx, so that derived
     visitors can use them (otherwise, they wouldn't see them).  */

  template <>
  inline
  void
  Binder::visit_dec_header(ast::FunctionDec& e)
  {
    fun_stack_.put(e.name_get(), &e);
  }

  template <>
  inline
  void
  Binder::visit_dec_body(ast::FunctionDec& e)
  {
    scope_begin();
    (*this)(e.formals_get());
    if (e.body_get() != nullptr)
      (*this)(*e.body_get());
    scope_end();
  }

  template <>
  inline
  void
  Binder::visit_dec_header(ast::MethodDec& e)
  {
    fun_stack_.put(e.name_get(), &e);
  }

  template <>
  inline
  void
  Binder::visit_dec_body(ast::MethodDec& e)
  {
    scope_begin();
    (*this)(e.formals_get());
    if (e.body_get() != nullptr)
      (*this)(*e.body_get());
    scope_end();
  }

  template <>
  inline
  void
  Binder::visit_dec_header(ast::TypeDec& e)
  {
    typ_stack_.put(e.name_get(), &e);
  }

  template <>
  inline
  void
  Binder::visit_dec_body(ast::TypeDec& e)
  {
    scope_begin();
    (*this)(e.ty_get());
    scope_end();
  }

} // namespace bind
