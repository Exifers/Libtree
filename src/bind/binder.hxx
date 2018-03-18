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
    // Shorthand.
    using decs_type = ast::AnyDecs<D>;
#warning // FIXME: Some code was deleted here (Two passes: once on headers, then on bodies).
  }

  /* These specializations are in bind/binder.hxx, so that derived
     visitors can use them (otherwise, they wouldn't see them).  */

#warning // FIXME: Some code was deleted here.

} // namespace bind
