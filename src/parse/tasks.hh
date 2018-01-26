/**
 ** \file parse/tasks.hh
 ** \brief Parse module tasks.
 */

#pragma once

#include <misc/fwd.hh>
#include <task/libtask.hh>

/// Tasks of the parse module.
namespace parse::tasks
{

  /// Global library for search path.
  extern misc::FileLibrary file_library;

  TASK_GROUP("1. Parsing");

  /// Enable scanner trace.
  BOOLEAN_TASK_DECLARE("scan-trace", "trace the scanning",
                       scan_trace_p, "");
  /// Enable parser trace.
  BOOLEAN_TASK_DECLARE("parse-trace", "trace the parse",
                       parse_trace_p, "");
  /// Prelude declarations.
  STRING_TASK_DECLARE("prelude", "builtin",
                      "name of the prelude.  Defaults to \"builtin\" "
                      "denoting the builtin prelude",
                      prelude, "");
  /// Prelude declarations.
  TASK_DECLARE("X|no-prelude", "don't include prelude",
               no_prelude, "");
  /// Parse the input file, store the ast into ast::tasks::the_program.
  TASK_DECLARE("parse", "parse a file",
               parse, "");

  /// Display library search path.
  TASK_DECLARE("library-display", "display library search path",
               library_display, "");
  /// Append directory DIR to the search path.
  MULTIPLE_STRING_TASK_DECLARE("P|library-append",
                               "append directory DIR to the search path",
                               library_append, "");
  /// Prepend directory DIR to the search path.
  MULTIPLE_STRING_TASK_DECLARE("p|library-prepend",
                               "prepend directory DIR to the search path",
                               library_prepend, "");

} // namespace parse::tasks
