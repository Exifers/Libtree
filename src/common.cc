/**
 ** \file common.cc
 ** \brief Common definitions.
 */

#include <common.hh>

// Sole argument: the file to process.
const char* filename;

// The current state of and error.
misc::error& task_error()
{
  static misc::error task_error_;
  return task_error_;
}

// Counting the time spent in the various tasks.
misc::timer task_timer;
