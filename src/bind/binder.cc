/**
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
    error_ << misc::error::error_type::bind
      << loc.location_get() << ": " << msg << misc::iendl
      << &misc::error::exit;
  }

  void
  Binder::check_main(const ast::FunctionDec& e)
  {
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
      undeclared<ast::SimpleVar>("variable", e);
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
    auto name = e.namety_get().name_get();
    auto def = typ_stack_.get(name);
    if (def == nullptr)
    {
      undeclared<ast::NameTy>("type", e.namety_get());
    }
    e.namety_get().def_set(def);
    e.size_exp_get().accept(*this);
    e.type_exp_get().accept(*this);
  }

  void
  Binder::operator()(ast::RecordExp& e)
  {
    auto name = e.namety_get().name_get();
    auto def = typ_stack_.get(name);
    if (def == nullptr)
      undeclared<ast::NameTy>("type", e.namety_get());
    e.namety_get().def_set(def);

    super_type::operator()(e);
  }

  void
  Binder::operator()(ast::ObjectExp& e)
  {
    auto name = e.namety_get().name_get();
    auto def = typ_stack_.get(name);
    if (def == nullptr)
      undeclared<ast::NameTy>("type", e.namety_get());
    e.namety_get().def_set(def);
  }

  void
  Binder::operator()(ast::CallExp& e)
  {
    auto def = fun_stack_.get(e.name_get());
    if (def == nullptr)
      undeclared<ast::CallExp>("function", e);
    e.def_set(def);

    super_type::operator()(e);
  }

  void
  Binder::operator()(ast::MethodCallExp& e)
  {
    auto def = fun_stack_.get(e.name_get());
    if (def == nullptr)
      undeclared<ast::CallExp>("function", e);
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
    scope_begin();
    auto l = e.exps_get();
    for (auto it = l.begin(); it != l.end(); it++)
    {
      super_type::operator()(**it);
    }
  }

  void
  Binder::operator()(ast::AssignExp& e)
  {
    (*this)(e.lvalue_get());
    (*this)(e.exp_get());
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
    loops_.push_back(&e);
    super_type::operator()(e.test_get());
    super_type::operator()(e.body_get());
    loops_.pop_back();
    scope_end();
  }

  void
  Binder::operator()(ast::ForExp& e)
  {
    scope_begin();
    loops_.push_back(&e);
    super_type::operator()(*e.vardec_get().init_get());
    super_type::operator()(e.hi_get());
    super_type::operator()(e.body_get());
    loops_.pop_back();
    scope_end();
  }

  void
  Binder::operator()(ast::BreakExp& e)
  {
    if (loops_.size() == 0)
      error(e, ": `break' outside a loop");
    e.loop_set(loops_.back());
  }

  void
  Binder::operator()(ast::VarDec& e)
  {
    if (var_stack_.get(e.name_get()) != nullptr)
      redefinition(e, *var_stack_.get(e.name_get()));
    var_stack_.put(e.name_get(), &e);
    if (e.type_name_get() != nullptr)
    {
      ast::NameTy& namety = *e.type_name_get();
      auto typ_def = typ_stack_.get(namety.name_get());
      if (typ_def == nullptr)
        undeclared<ast::NameTy>("type", namety);
      e.def_set(typ_def);
    }
    if (e.init_get() != nullptr)
      super_type::operator()(*(e.init_get()));
  }

  void
  Binder::operator()(ast::NameTy& e)
  {
    auto def = typ_stack_.get(e.name_get());
    if (def == nullptr)
      undeclared<ast::NameTy>("type", e);
    e.def_set(def);
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
    decs_visit<ast::FunctionDec>(e);
  }

  void
  Binder::operator()(ast::MethodDecs& e)
  {
    decs_visit<ast::MethodDec>(e);
  }

  /*--------------------.
  | Visiting TypeDecs.  |
  `--------------------*/
  void
  Binder::operator()(ast::TypeDecs& e)
  {
    decs_visit<ast::TypeDec>(e);
  }

} // namespace bind
