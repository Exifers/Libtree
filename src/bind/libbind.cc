/**
 ** \file bind/libbind.cc
 ** \brief Define exported bind functions.
 */


#include "libbind.hh"
#include "renamer.hh"

namespace bind
{
  namespace tasks
  {
    void bind_ast(void)
    {
      bind::Binder binder = bind::Binder();
      ast::tasks::the_program->accept(binder);
    }

    void rename_ast(void)
    {
      bind::Renamer renamer = bind::Renamer();
      ast::tasks::the_program->accept(renamer);
    }
  } // namespace bind::tasks
} // namespace bind
