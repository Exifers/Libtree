/**
 ** \file bind/libbind.cc
 ** \brief Define exported bind functions.
 */


#include "libbind.hh"

namespace bind
{
  namespace tasks
  {
    void bind_ast(void)
    {
      bind::Binder binder = bind::Binder();
      ast::tasks::the_program->accept(binder);
    }
  } // namespace bind::tasks
} // namespace bind
