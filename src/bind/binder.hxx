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

  template <typename T>
  void Binder::undeclared(const std::string& k, const T& e)
  {
    if (k == "variable")
      error(e, "undeclared variable: " + e.name_get().get());
    else if (k == "function")
      error(e, "undeclared function: " + e.name_get().get());
    else if (k == "type")
      error(e, "undeclared type: " + e.name_get().get());
  }

  template <typename T>
  void Binder::redefinition(const T& e1, const T& e2)
  {
    error_ << misc::error::error_type::bind
      << e1.location_get() << ": redefition: " << e1.name_get() << misc::iendl;
    error_ << misc::error::error_type::bind
      << e2.location_get() << ": first definition"
      << misc::iendl << &misc::error::exit;
  }

  /*-------------------.
  | Definition sites.  |
  `-------------------*/


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
    if (fun_stack_.get(e.name_get()) != nullptr)
      redefinition<ast::FunctionDec>(e, *fun_stack_.get(e.name_get()));
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
    if (fun_stack_.get(e.name_get()) != nullptr)
      redefinition<ast::FunctionDec>(e, *fun_stack_.get(e.name_get()));
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
    if (typ_stack_.get(e.name_get()) != nullptr)
      redefinition<ast::TypeDec>(e, *typ_stack_.get(e.name_get()));
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
