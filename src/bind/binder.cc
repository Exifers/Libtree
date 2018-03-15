/**
 ** \file bind/binder.cc
 ** \brief Implementation for bind/binder.hh.
 */

#include <ast/all.hh>
#include <bind/binder.hh>

#include <misc/contract.hh>

namespace bind
{

  /*-----------------.
  | Error handling.  |
  `-----------------*/

  /// The error handler.
  const misc::error&
  Binder::error_get() const
  {
    return error_;
  }

  void Binder::error(const ast::Ast& loc, const std::string& msg)
  {
  }

  template <typename T>
  void Binder::undeclared(const std::string& k, const T& e)
  {
  }

  template <typename T>
  void Binder::redefinition(const T& e1, const T& e2)
  {
  }

  void
  Binder::check_main(const ast::FunctionDec& e)
  {
  // FIXME: Some code was deleted here.
  }

  /*----------------.
  | Symbol tables.  |
  `----------------*/


  void
  Binder::scope_begin()
  {
    fun_stack_.scope_begin();
    typ_stack_.scope_begin();
    var_stack_.scope_begin();
  }

  void
  Binder::scope_end()
  {
    fun_stack_.scope_end();
    typ_stack_.scope_end();
    var_stack_.scope_end();
  }

  /*---------.
  | Visits.  |
  `---------*/

  void
  Binder::operator()(ast::SimpleVar& e)
  {
    auto def = var_stack_.get(e.name_get());
    if (def == nullptr)
      throw;
    e.def_set(def);
  }

  void
  Binder::operator()(ast::CastExp& e)
  {
    super_type::operator()(e);
  }

  void
  Binder::operator()(ast::LetExp& e)
  {
    scope_begin();
    super_type::operator()(e);
    scope_end();
  }

  void
  Binder::operator()(ast::ArrayExp& e)
  {
    super_type::operator()(e);
  }

  void
  Binder::operator()(ast::RecordExp& e)
  {
    auto l = e.fields_get();
    for (auto it = l.begin(); it != l.end(); it++)
    {
      super_type::operator()(**it);
    }
  }

  void
  Binder::operator()(ast::ObjectExp& e)
  {
  }

  void
  Binder::operator()(ast::CallExp& e)
  {
    auto def = fun_stack_.get(e.name_get());
    if (def == nullptr)
      throw;
    e.def_set(def);

    auto l = e.exps_get();
    for (auto it = l.begin(); it != l.end(); it++)
    {
      super_type::operator()(**it);
    }
  }

  void
  Binder::operator()(ast::MethodCallExp& e)
  {
    auto def = fun_stack_.get(e.name_get());
    if (def == nullptr)
      throw;
    e.def_set(def);

    super_type::operator()(e.lvalue_get());
    auto l = e.exps_get();
    for (auto it = l.begin(); it != l.end(); it++)
    {
      super_type::operator()(**it);
    }
  }

  void
  Binder::operator()(ast::SeqExp& e)
  {
    auto l = e.exps_get();
    for (auto it = l.begin(); it != l.end(); it++)
    {
      super_type::operator()(**it);
    }
  }

  void
  Binder::operator()(ast::AssignExp& e)
  {
    super_type::operator()(e.lvalue_get());
  }

  void
  Binder::operator()(ast::IfExp& e)
  {
    scope_begin();
    super_type::operator()(e.condition_get());
    super_type::operator()(e.content_get());
    try
    {
      ast::Exp& else_content = e.else_content_get();
      super_type::operator()(else_content);
    }
    catch(...)
    {}
    scope_end();
  }

  void
  Binder::operator()(ast::WhileExp& e)
  {
    scope_begin();
    super_type::operator()(e.test_get());
    super_type::operator()(e.body_get());
    scope_end();
  }

  void
  Binder::operator()(ast::ForExp& e)
  {
    scope_begin();
    super_type::operator()(*e.vardec_get().init_get());
    super_type::operator()(e.hi_get());
    super_type::operator()(e.body_get());
    scope_end();
  }

  void
  Binder::operator()(ast::VarDec& e)
  {
    var_stack_.put(e.name_get(), &e);
    if (e.init_get() != nullptr)
      super_type::operator()(*(e.init_get()));
  }

  void
  Binder::operator()(ast::TypeDec& e)
  {
    typ_stack_.put(e.name_get(), &e);
    super_type::operator()(e.ty_get());
  }

  void
  Binder::operator()(ast::FunctionDec& e)
  {
    fun_stack_.put(e.name_get(), &e);
    scope_begin();

    (*this)(e.formals_get());

    auto body = e.body_get();
    if (body != nullptr)
      super_type::operator()(*body);

    scope_end();
  }

  void
  Binder::operator()(ast::MethodDec& e)
  {
    fun_stack_.put(e.name_get(), &e);
    super_type::operator()(*(e.body_get()));
  }

  /*-------------------.
  | Visiting VarDecs.  |
  `-------------------*/

  void
  Binder::operator()(ast::VarDecs& e)
  {
    auto v = e.decs_get();
    for (auto it = v.begin(); it != v.end(); it++)
    {
      (*this)(*it);
    }
  }


  /*------------------------.
  | Visiting FunctionDecs.  |
  `------------------------*/

  void
  Binder::operator()(ast::FunctionDecs& e)
  {
    for (auto it = e.decs_get().begin(); it != e.decs_get().end(); it++)
    {
      (*this)(**it);
    }
  }

  void
  Binder::operator()(ast::MethodDecs& e)
  {
    auto v = e.decs_get();
    for (auto it = v.begin(); it != v.end(); it++)
    {
      (*this)(**it);
    }
  }

  /*--------------------.
  | Visiting TypeDecs.  |
  `--------------------*/
  void
  Binder::operator()(ast::TypeDecs& e)
  {
    for (auto it = e.decs_get().begin(); it != e.decs_get().end(); it++)
    {
      super_type::operator()(**it);
    }
  }

} // namespace bind
