/**
 ** \file task/libtask.hh
 ** \brief Interface to the Task module.
 **
 */

/* This file must not be protected against multiple inclusion,
   because it might be read to define or declare the tasks. */

#include <task/boolean-task.hh>
#include <task/disjunctive-task.hh>
#include <task/function-task.hh>
#include <task/int-task.hh>
#include <task/multiple-string-task.hh>
#include <task/string-task.hh>

/// Handling of Task.
namespace task {} // namespace task

/** A means to concatenate tokens with delayed evaluation. */
# define CONCAT_(A, B) A ## B
# define CONCAT(A, B)  CONCAT_(A, B)

/** Make a "unique" token using the line number of invocation of this
    macro.

    Conflicts are possible, but unlikely: tasks declared at the same
    line number, but in different files, are not a problem, since
    anyway the tasks are static, and in different namespaces.

    Just don't declare two tasks on the same line! */
# define TASK_UNIQUE() CONCAT(task_, __LINE__)

/*------------------------------.
| Easy instantiation of Tasks.  |
`------------------------------*/

#undef TASK_GROUP
#undef TASK_DECLARE
#undef BOOLEAN_TASK_DECLARE
#undef INT_TASK_DECLARE
#undef STRING_TASK_DECLARE
#undef MULTIPLE_STRING_TASK_DECLARE
#undef DISJUNCTIVE_TASK_DECLARE

// Should we define the objects, or just declare them?
#if DEFINE_TASKS

/// Define the current Task group name.
# define TASK_GROUP(Name)                       \
  const char group_name[] = Name

/// Instantiate a FunctionTask.
# define TASK_DECLARE(Name, Help, Routine, Deps)                        \
  extern void (Routine)();                                             \
  static task::FunctionTask task_##Routine(Routine, group_name, Help,   \
                                           Name, Deps)

/// Instantiate a BooleanTask.
# define BOOLEAN_TASK_DECLARE(Name, Help, Flag, Deps)           \
  bool Flag;                                                    \
  static task::BooleanTask task_##Flag(Flag, group_name, Help,  \
                                       Name, Deps)

# define TASK_UNIQUE_NAME_(Line) \
  task_##Line

# define TASK_UNIQUE_NAME \
  TASK_UNIQUE_NAME_(__LINE__)

/// Instantiate an IntTask.
# define INT_TASK_DECLARE(Name, Min, Max, Help, Flag, Deps)             \
  static task::IntTask TASK_UNIQUE()(Flag, Min, Max, group_name,        \
                                     Help, Name, Deps)


/// Instantiate a StringTask.
# define STRING_TASK_DECLARE(Name, Default, Help, Flag, Deps)   \
  std::string Flag = Default;                                   \
  static task::StringTask task_##Flag(Flag, group_name, Help,   \
                                      Name, Deps)

/// Instanciate a MultipleStringTask
# define MULTIPLE_STRING_TASK_DECLARE(Name, Help, Routine, Deps)        \
  extern task::MultipleStringTask::callback_type Routine;               \
  static task::MultipleStringTask task_##Routine(Routine, group_name,   \
                                                 Help, Name,            \
                                                 Deps)

/// Instantiate a DisjunctiveTask.
# define DISJUNCTIVE_TASK_DECLARE(Name, Help, Deps)             \
  static task::DisjunctiveTask task_##Routine(group_name, Help, \
                                              Name, Deps)

#else // !DEFINE_TASKS

/// Define the current Task group name.
# define TASK_GROUP(Name) \
  extern const char* group_name
/// Instantiate a FunctionTask.
# define TASK_DECLARE(Name, Help, Routine, Deps) \
  extern void (Routine)()
/// Instantiate a BooleanTask.
# define BOOLEAN_TASK_DECLARE(Name, Help, Flag, Deps) \
  extern bool Flag;
/// Instantiate an IntTask.
# define INT_TASK_DECLARE(Name, Min, Max, Help, Flag, Deps)
/// Instantiate a StringTask.
# define STRING_TASK_DECLARE(Name, Default, Help, Flag, Deps) \
  extern std::string Flag;
/// Instantiate a MultipleStringTask.
# define MULTIPLE_STRING_TASK_DECLARE(Name, Help, Routine, Deps) \
  extern void (Routine)(std::string);
/// Instantiate a DisjunctiveTask.
# define DISJUNCTIVE_TASK_DECLARE(Name, Help, Deps)

#endif // !DEFINE_TASKS
