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

  // FIXME: Some code was deleted here (Error reporting).

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
  Binder::operator()(ast::FunctionDec& e)
  {
    auto exp = e.body_get();
    if (exp)
      exp->accept(*this);
  }

  void
  Binder::operator()(ast::MethodDec& e)
  {
  }

  void
  Binder::operator()(ast::TypeDec& e)
  {
  }

  void
  Binder::operator()(ast::VarDec& e)
  {
  }

  void
  Binder::operator()(ast::ArrayExp& e)
  {
  }

  void
  Binder::operator()(ast::AssignExp& e)
  {
  }

  void
  Binder::operator()(ast::CallExp& e)
  {
  }

  void
  Binder::operator()(ast::MethodCallExp& e)
  {
  }

  void
  Binder::operator()(ast::LetExp& e)
  {
    for (auto it = e.decs_get().decs_get().begin();
        it != e.decs_get().decs_get().end(); it++)
    {
      (**it).accept(*this);
    }

    for (auto it = e.exps_get().begin(); it != e.exps_get().end(); it++)
    {
      (**it).accept(*this);
    }

  }

  void
  Binder::operator()(ast::ObjectExp& e)
  {
  }

  void
  Binder::operator()(ast::RecordExp& e)
  {
  }

  void
  Binder::operator()(ast::SeqExp& e)
  {
    for (auto it = e.exps_get().begin(); it != e.exps_get().end(); it++)
    {
      (**it).accept(*this);
    }
  }


  /*-------------------.
  | Visiting VarDecs.  |
  `-------------------*/

  void
  Binder::operator()(ast::VarDecs& e)
  {
    std::cout << "Binding vardecs" << std::endl;
  }


  /*------------------------.
  | Visiting FunctionDecs.  |
  `------------------------*/

  void
  Binder::operator()(ast::FunctionDecs& e)
  {
    for (auto it = e.decs_get().begin(); it != e.decs_get().end(); it++)
    {
      (**it).accept(*this);
    }
  }

  void
  Binder::operator()(ast::MethodDecs& e)
  {
    for (auto it = e.decs_get().begin(); it != e.decs_get().end(); it++)
    {
      (**it).accept(*this);
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
      (**it).accept(*this);
    }
  }

} // namespace bind
