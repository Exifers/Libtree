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
  // FIXME: Some code was deleted here.
  }

  void
  Binder::scope_end()
  {
  // FIXME: Some code was deleted here.
  }

  /*---------.
  | Visits.  |
  `---------*/

  // FIXME: Some code was deleted here.

  void
  Binder::operator()(ast::LetExp& e)
  {
  // FIXME: Some code was deleted here.
  }


  /*-------------------.
  | Visiting VarDecs.  |
  `-------------------*/

  // FIXME: Some code was deleted here.


  /*------------------------.
  | Visiting FunctionDecs.  |
  `------------------------*/

  // FIXME: Some code was deleted here.

  /*--------------------.
  | Visiting TypeDecs.  |
  `--------------------*/
  // FIXME: Some code was deleted here.

} // namespace bind
