/**
 ** \file ast/tasks.cc
 ** \brief Ast Tasks implementation.
 */

#include <misc/contract.hh>
#include <ast/libast.hh>
#define DEFINE_TASKS 1
#include <ast/tasks.hh>
#undef DEFINE_TASKS

namespace ast
{

  namespace tasks
  {

    // The abstract syntax tree.
    std::unique_ptr<ast::DecsList> the_program(nullptr);

    void
    ast_display()
    {
      precondition(the_program);
      std::cout << "/* == Abstract Syntax Tree. == */\n"
                << *the_program << std::endl;
    }

  } // namespace tasks

} // namespace ast
