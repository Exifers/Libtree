/**
 ** \file object/tasks.cc
 ** \brief Object module related tasks' implementation.
 */

#include <memory>

#include <ast/tasks.hh>
#include <astclone/libastclone.hh>
#include <common.hh>
#include <object/libobject.hh>
#define DEFINE_TASKS 1
#include <object/tasks.hh>
#undef DEFINE_TASKS

namespace object::tasks
{
    void
    object_parse()
    {}

#warning // FIXME: Some code was deleted here.

    void
    object_types_compute()
    {
      task_error() << ::object::types_check(*ast::tasks::the_program)
                   << &misc::error::exit_on_error;
    }

    static std::unique_ptr<class_names_type> class_names;

    void
    object_rename()
    {
      class_names.reset(::object::rename(*ast::tasks::the_program));
    }

    void
    object_desugar()
    {
      astclone::apply(::object::desugar, ast::tasks::the_program,
                      *class_names.get());
    }

    void
    raw_object_desugar()
    {
      astclone::apply(::object::raw_desugar, ast::tasks::the_program,
                      *class_names.get());
    }

#warning // FIXME: Some code was deleted here.

} // namespace object::tasks

