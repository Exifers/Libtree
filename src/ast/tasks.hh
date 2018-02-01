/**
 ** \file ast/tasks.hh
 ** \brief Ast module related tasks.
 */

#pragma once

#include <task/libtask.hh>
#include <ast/decs-list.hh>

namespace ast
{

  /// Task for ast.
  namespace tasks
  {
    /// Global root node of abstract syntax tree.
    extern std::unique_ptr<ast::DecsList> the_program;

    TASK_GROUP("2. Abstract Syntax Tree");

    /// Display the abstract syntax tree.
    TASK_DECLARE("A|ast-display", "display the AST",
                 ast_display, "parse");

  } // namespace tasks

} // namespace ast
