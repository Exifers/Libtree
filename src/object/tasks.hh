/**
 ** \file object/tasks.hh
 ** \brief Object module related tasks.
 */

#pragma once

#include <task/libtask.hh>

namespace object::tasks
{
  TASK_GROUP("Object");

  /// Enable object extensions.
  BOOLEAN_TASK_DECLARE("o|object", "enable object extensions",
                       enable_object_extensions_p, "");

  /// Parse the input file, allowing objects.
  TASK_DECLARE("object-parse", "parse a file, allowing objects",
               object_parse, "object parse");

#warning // FIXME: Some code was deleted here.




} // namespace object::tasks
