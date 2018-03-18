/**
 ** \file overload/binder.cc
 ** \brief Implementation of overload::Binder.
 */

#include <ast/all.hh>
#include <overload/binder.hh>

namespace overload
{

  overfun_bindings_type&
  Binder::overfun_bindings_get()
  {
    return overfun_bindings_;
  }


  /*---------.
  | Scopes.  |
  `---------*/

  void
  Binder::scope_begin()
  {
    super_type::scope_begin();
    overfuns_.scope_begin();
  }

  void
  Binder::scope_end()
  {
    overfuns_.scope_end();
    super_type::scope_end();
  }


  /*-------------------.
  | Visiting methods.  |
  `-------------------*/

  // Same as Binder's, but do not set the definition site of E.
  void
  Binder::operator()(ast::CallExp& e)
  {
#warning // FIXME: Some code was deleted here.
  }

  // Insert the prototype of the function in the environment.
  void
  Binder::visit_dec_header(ast::FunctionDec& e)
  {
    check_main(e);
    overfuns_.put(e.name_get(), e);
  }

  void
  Binder::operator()(ast::FunctionDecs& e)
  {
    // Two passes: once on headers, then on bodies.
#warning // FIXME: Some code was deleted here.
  }

} // namespace overload
