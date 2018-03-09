/**
 ** \file overload/tasks.cc
 ** \brief Overload module related tasks' implementation.
 */

#include <memory>

#include <ast/tasks.hh>
#include <common.hh>
#include <overload/liboverload.hh>
#define DEFINE_TASKS 1
#include <overload/tasks.hh>
#undef DEFINE_TASKS

namespace overload::tasks
{

    std::unique_ptr<overfun_bindings_type> the_overfun_bindings = nullptr;

    void
    overfun_bindings_compute()
    {
      auto result = ::overload::bind(*ast::tasks::the_program);
      ::overload::tasks::the_overfun_bindings =
          std::make_unique<overfun_bindings_type>(std::move(result.first));

      task_error() << result.second << &misc::error::exit_on_error;
    }

    void
    overfun_types_compute()
    {
      task_error()
        << ::overload::types_check(*ast::tasks::the_program,
                                   *::overload::tasks::the_overfun_bindings);

      // Force the unique_ptr to be freed.
      the_overfun_bindings.reset();
      task_error().exit_on_error();
    }

} // namespace overload::tasks
