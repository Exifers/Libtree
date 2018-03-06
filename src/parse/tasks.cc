/**
 ** \file parse/tasks.cc
 ** \brief Parse module related tasks' implementation.
 **/

#include <cstdlib>
#include <iostream>

#include <ast/tasks.hh>
#include <common.hh>
#include <misc/file-library.hh>
#include <object/tasks.hh>
#include <parse/libparse.hh>
#define DEFINE_TASKS 1
#include <parse/tasks.hh>
#undef DEFINE_TASKS


namespace parse::tasks
{

  const char* tc_pkgdatadir = getenv("TC_PKGDATADIR");
  misc::file_library l =
    misc::file_library(tc_pkgdatadir ? tc_pkgdatadir : PKGDATADIR);

  void
  no_prelude()
  {
    prelude = "";
  }

  void
  parse()
  {
    precondition(filename != nullptr);
    bool scan_trace  = scan_trace_p  || getenv("SCAN");
    bool parse_trace = parse_trace_p || getenv("PARSE");
    std::pair<ast::DecsList*, misc::error> result =
      ::parse::parse(prelude, filename, l,
                     scan_trace, parse_trace
                     , object::tasks::enable_object_extensions_p
                     );
      // If the parsing completely failed, stop.
      task_error() << result.second;
      if (!result.first)
        task_error().exit();

      ast::DecsList* l = std::get<0>(result);
      ast::tasks::the_program.reset(l);
  }

  void
  library_display()
  {
    std::cout << l << '\n';
  }

  void
  library_append(const std::string& dir)
  {
    l.append_dir(dir);
  }

  void
  library_prepend(const std::string& dir)
  {
    l.prepend_dir(dir);
  }

} // namespace parse::tasks
