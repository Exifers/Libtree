/**
 ** \file task/task-register.cc
 ** \brief Implementation of task::TaskRegister.
 **
 */

#include <algorithm>
#include <exception>
#include <map>

#include <common.hh>
#include <misc/algorithm.hh>
#include <task/argument-task.hh>
#include <task/disjunctive-task.hh>
#include <task/simple-task.hh>
#include <task/task-register.hh>

namespace task
{

  // Singleton stuff
  TaskRegister&
  TaskRegister::instance()
  {
    static TaskRegister instance_;
    return instance_;
  }

  // Register this task.
  void
  TaskRegister::register_task(const SimpleTask& task)
  {
    auto it = register_task_(task);
    // The task was already registered.
    if (it == modules_.end())
      return;

    // Callback when the option is parsed.
    auto cb = [this, &task](bool f){ if (f) enable_task(task.name_get()); };

    namespace po = boost::program_options;
    auto v = po::bool_switch()->notifier(cb);

    it->second.add_options()
      (task.fullname_get(), v, task.desc_get());
  }

  void
  TaskRegister::register_task(const ArgumentTask& task)
  {
    auto it = register_task_(task);
    // The taks was already registered.
    if (it == modules_.end())
      return;

    // Callback when the option is parsed.
    auto cb = [this, &task](const std::string& arg)
      {
        task.arg_set(arg);
        enable_task(task.name_get());
      };

    namespace po = boost::program_options;
    auto v = po::value<std::string>()->value_name(task.argname_get())
                                     ->required()
                                     ->notifier(cb);

    it->second.add_options()
      (task.fullname_get(), v, task.desc_get());
  }

  // Internal task registration.
  // Add the task to the list of tasks and return an iterrator to the module
  // the option belongs to. The module is created if needed.
  // In case something went wrong, the end of `modules_' is returned.
  TaskRegister::indexed_module_type::iterator
  TaskRegister::register_task_(const Task& task)
  {
    if (task_list_.find(task.name_get()) != task_list_.end())
      {
        task_error() << misc::error::error_type::failure
                     << program_name
                     << ": TaskRegister::register_task(" << task.name_get()
                     << "): task name already registered.\n";
        return modules_.end();
      }
    task_list_[task.name_get()] = &task;

    // Short-hands.
    namespace po = boost::program_options;
    const std::string& module_name = task.module_name_get();
    auto it = modules_.find(module_name);
    if (it == modules_.end())
      it = modules_.emplace(module_name, po::options_description(module_name))
                   .first;
    // Return the iterator on the module the task belongs to.
    return it;
  }

  // Request the execution of the task task_name.
  void
  TaskRegister::enable_task(const std::string& task_name)
  {
    if (task_list_.find(task_name) == task_list_.end())
      task_error() << misc::error::error_type::failure
                   << program_name
                   << ": TaskRegister::enable_task(" << task_name
                   << "): this task has not been registered.\n";
    else
      {
        const Task* task = task_list_.find(task_name)->second;
        resolve_dependencies(*task);
        // FIXME: for efficiency, resolve_dependency should be called once.
        // FIXME: detect cycle.
        task_order_.emplace_back(task);
      }
  }

  // Return the number of tasks to execute.
  int
  TaskRegister::nb_of_task_to_execute_get()
  {
    return task_order_.size();
  }

  // Resolve dependencies between tasks.
  void
  TaskRegister::resolve_dependencies(const Task& task)
  {
    tasks_list_type enabled_tasks;

    // Retrieved already active tasks.
    for (const std::string& s : task.dependencies_get())
      if (task_list_.find(s) == task_list_.end())
        {
          task_error() << misc::error::error_type::failure
                       << program_name
                       << ": TaskRegister::resolve_dependencies(\""
                       << task.name_get()
                       << "\"): unknown task: \"" << s << '"'
                       << std::endl;
        }
      else
        {
          const Task* task_dep = task_list_.find(s)->second;
          if (misc::has(task_order_, task_dep))
            enabled_tasks.emplace_back(task_dep);
        }

    // Ask the task which dependent tasks should be activated.
    const Task::deps_type dep_tasks = task.resolve_dependencies(enabled_tasks);

    // Activate them.
    for (const std::string& s : dep_tasks)
      {
        if (task_list_.find(s) != task_list_.end())
          if (!misc::has(task_order_, task_list_.find(s)->second))
            enable_task(s);
      }
  }

  // Check whether one of the options in os has the string_key s.
  template <typename T>
  static bool
  is_parsed(const std::string& s,
            const std::vector<boost::program_options::basic_option<T>>& os)
  {
    using option = boost::program_options::basic_option<T>;

    return std::find_if(begin(os), end(os),
                        [&s](const option& o) { return s == o.string_key; })
           != end(os);
  }

  char*
  TaskRegister::parse_arg(int argc, char* argv[])
  {
    // Short-hand.
    namespace po = boost::program_options;
    std::string input_file;

    // Create the category containing `help', `version' and `usage'.
    po::options_description generic;
    generic.add_options()
      ("help,?", "Give this help list")
      ("usage", "Give a short usage message")
      ("version", "Print program version");

    // Positional parameter.
    po::options_description hidden;
    po::positional_options_description positional;
    hidden.add_options()
      ("input-file", po::value<std::string>(&input_file)->required(),
       "Input file");
    positional.add("input-file", 1);

    // Create the top-level category, with visible options.
    po::options_description visible_desc(program_doc);

    // Add each category to the top-level one.
    for (const auto& i : modules_)
      visible_desc.add(i.second);
    visible_desc.add(generic);

    // Sum of visible options and positional argument.
    po::options_description all_opts = visible_desc;
    all_opts.add(hidden);

    // Give control to boost.
    try
      {
        // Sadly we can't use `boost::program_options::variables_map'. By doing
        // so, we would lose the chronological order of the tasks, which is
        // capital for TC to work.
        auto parsed = po::command_line_parser(argc, argv)
                                      .options(all_opts)
                                      .positional(positional)
                                      .run();

        // We don't want to fail if these options ar present. So we take care
        // of them right now.
        if (is_parsed("help", parsed.options))
            std::cout << visible_desc;
        else if (is_parsed("version", parsed.options))
            std::cout << program_version;
        else if (is_parsed("usage", parsed.options))
            std::cout << "tc [OPTIONS...] INPUT-FILE\n";
        else
          {
            // Replace the traditional calls to `vm.store()' and `vm.notify()'.
            for (const auto& i : parsed.options)
              {
                auto option = parsed.description->find(i.string_key, false);

                po::variable_value v;
                option.semantic()->parse(v.value(), i.value, true);
                option.semantic()->notify(v.value());
              }

            // If no input file is given, throw.
            if (input_file.size() == 0)
              throw po::error("no file name");
          }
      }
    catch (po::error& e)
      {
        std::cerr << program_name << ": " << e.what()
                  << "\ntc [OPTIONS...] INPUT-FILE\n"
                     "Try `tc --help' or `tc --usage' for more information.\n";
        throw std::invalid_argument("command line parsing error");
      }
    catch (std::invalid_argument& e)
      {
        throw;
      }

    char* input_file_ = nullptr;
    if (!input_file.empty())
      {
        input_file_ = new char[input_file.size() + 1];
        strcpy(input_file_, input_file.c_str());
      }
    return input_file_;
  }


  // Display registered Tasks.
  std::ostream&
  TaskRegister::print_task_list(std::ostream& ostr)
  {
    ostr << "List of registered tasks:\n";
    for (const tasks_by_name_type::value_type& i : task_list_)
      ostr << "\t* " << i.first << '\n';
    return ostr << std::endl;
  }

  // Dump task graph.
  std::ostream&
  TaskRegister::print_task_graph(std::ostream& ostr)
  {
    ostr << "/* Task graph */\n"
         << "digraph Tasks {\n"
         << "  node [shape=box, fontsize=14]\n"
      // Preserve the order of the children.
         << "  graph [ordering=out]\n";

    for (const tasks_by_name_type::value_type& i : task_list_)
      {
        const Task& task = *i.second;
        if (dynamic_cast<const DisjunctiveTask*>(&task))
          ostr << "  \"" << task.name_get() << "\" [shape=diamond]\n";
        ostr << "  \"" << task.name_get() << "\"";
        if (task.dependencies_get().size())
          {
            ostr << " -> {";
            for (const std::string& s : task.dependencies_get())
              ostr <<  " \"" << s << "\"";
            ostr << " } ";
          }
        ostr << '\n';
      }

    return ostr << "}\n";
  }

  // Display registered Tasks execution order.
  std::ostream&
  TaskRegister::print_task_order(std::ostream& ostr)
  {
    ostr << "List of Task Order:\n";
    for (const Task* t : task_order_)
      ostr << "\t* " << t->name_get() << std::endl;
    return ostr << std::endl;
  }

  // Execute tasks, checking dependencies.
  void
  TaskRegister::execute()
  {
    // FIXME: should be the only one to call resolve_dependency.
    for (const Task* t : task_order_)
      {
        std::cout << "Executing tasks" << std::endl;
        std::string pref(t->module_name_get());
        if (!pref.empty())
          pref = pref[0] + std::string(": ");
        timer_.push(pref + t->name_get());
        t->execute();
        timer_.pop(pref + t->name_get());
      }
  }

} // namespace task
