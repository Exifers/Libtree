/**
 ** \file src/common.hh
 ** \brief Definitions common to the whole task system.
 **
 ** These variables are global.  As such they should not be used
 ** in the libraries, but only in the "imperative" subsystem: the
 ** tasks.
 */

#pragma once

#include <misc/error.hh>
#include <misc/timer.hh>

/// \name Program identity.
/// \{
/// Name of this program.
extern const char* program_name;

/// Version string of this program.
extern const char* program_version;

/// Bug report address of this program.
extern const char* program_bug_address;

/// Describe program and accepted arguments.
extern const char* program_doc;
extern const char* program_args_doc;

/// \}


/// Timing the tasks.
extern misc::timer task_timer;

/// Sole argument: the file to process.
extern const char* filename;

/// The current state of error.
extern misc::error& task_error();
