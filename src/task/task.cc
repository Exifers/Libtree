/**
 ** \file task/task.cc
 ** \brief Implementation of task::Task.
 **
 */

#include <algorithm>
#include <iostream>
#include <iterator>

#include <task/task.hh>

namespace task
{

  Task::Task(const char* name,
             const char* module_name, const char* desc,
             const std::string& deps)
    : name_(normalize(name)), fullname_(name_), module_name_(module_name)
    , desc_(desc)
  {
    // Compute its dependencies.
    std::string::size_type start = 0;
    while (start < deps.size())
      {
        std::string::size_type end = deps.find(' ', start);
        if (end > deps.size())
          end = deps.size();
        dependencies_.emplace_back(normalize(deps.substr(start, end - start)));
        start = end + 1;
      }

    // See if it has a short option, such as "h|help".
    if (name_.size() >= 2 && name_[1] == '|')
      {
        fullname_ += ',';
        fullname_ += name_[0];
        name_.erase(0, 2);
        fullname_.erase(0, 2);
      }
  }


  Task::deps_type
  Task::resolve_dependencies(tasks_list_type&) const
  {
    // By default, consider that all dependencies are required.
    return dependencies_;
  }


  /// Display dependencies of this task.
  void
  Task::print_dependencies() const
  {
    std::cout << "Dependencies for task " << name_ << ":\n";
    for (const std::string& s : dependencies_)
      std::cout << "\t" << s << '\n';
    std::cout << std::flush;
  }

  std::string
  Task::normalize(const std::string& task_name)
  {
    std::string normalized_name;
    std::replace_copy(task_name.begin(), task_name.end(),
                      std::inserter(normalized_name,
                                    normalized_name.begin()),
                      '_', '-');
    return normalized_name;
  }

} // namespace task
