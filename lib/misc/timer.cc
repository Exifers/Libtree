/**
 ** \file misc/timer.cc
 ** \brief Implementation for misc/timer.hh.
 */

#include <iomanip>
#include <unistd.h>
#include <sys/times.h>

#include <misc/contract.hh>
#include <misc/timer.hh>

namespace misc
{

  /*-----------------.
  | timer::time_var.  |
  `-----------------*/

  timer::time_var::time_var()
    : initial(true)
  {}

  void
  timer::time_var::start()
  {
    struct tms tms;

    begin.wall = times(&tms);
    begin.user = tms.tms_utime;
    begin.sys  = tms.tms_stime;

    if (initial)
      {
        initial = false;
        first = begin;
      }
  }

  void
  timer::time_var::stop()
  {
    struct tms tms;

    last.wall = times(&tms);
    last.user = tms.tms_utime;
    last.sys  = tms.tms_stime;
    elapsed.wall += last.wall - begin.wall;
    elapsed.user += last.user - begin.user;
    elapsed.sys  += last.sys  - begin.sys;
  }

  bool
  timer::time_var::is_zero()
  {
    return elapsed.wall == 0
           && elapsed.user == 0
           && elapsed.sys == 0;
  }


  /*--------.
  | timer.  |
  `--------*/

  timer::timer()
    : dump_stream(nullptr)
  {}

  // Duplicate a timer.  No tasks should be running.
  timer::timer(const timer& rhs)
    : intmap(rhs.intmap)
    , total(rhs.total)
    , dump_stream(rhs.dump_stream)
  {
    precondition(rhs.tasks.empty());

    for (const task_map_type::value_type& p : rhs.tasksmap)
      if (tasksmap.find(p.first) == tasksmap.end())
        tasksmap[p.first] = new time_var(*p.second);
  }


  timer::~timer()
  {
    // Print information if automatic dumping has been enabled.
    if (dump_stream)
      {
        // Consider that if the tasks were not properly closed, then
        // stop was not invoked either.
        if (!tasks.empty())
          {
            do
              pop();
            while (!tasks.empty());
            stop();
          }
        dump(*dump_stream);
      }

    // Deallocate all our time_var's.
    for (task_map_type::value_type& p : tasksmap)
      delete p.second;
  }


  void
  timer::name(int i, const std::string& task_name)
  {
    intmap[i] = task_name;
  }

  void
  timer::timeinfo(long time, long total_time, std::ostream& out)
  {
    out << std::setiosflags(std::ios::left)
        << std::setw(6) << std::setprecision(6)
        << float(time) / clocks_per_sec
        << std::resetiosflags(std::ios::left)
        << " ("
        << std::setw(5) << std::setprecision(3)
        << (total_time ?
            float(time) * 100 / total_time :
            float(time))
        << "%) ";
  }


  void
  timer::dump(std::ostream& out)
  {
    out << "Execution times (seconds)\n";
    for (const task_map_type::value_type& p : tasksmap)
      {
        if (!p.second->is_zero())
          {
            out << " " << p.first << std::setw(26 - p.first.length())
                << ": ";
            timeinfo(p.second->elapsed.user, total.elapsed.user, out);
            out << "  ";
            timeinfo(p.second->elapsed.sys, total.elapsed.sys, out);
            out << "  ";
            timeinfo(p.second->elapsed.wall, total.elapsed.wall, out);
            out << '\n';
          }
      }
    out << '\n';

    out << "Cumulated times (seconds)\n";
    for (const task_map_type::value_type& p : tasksmap)
      {
        if (p.second->last.wall != p.second->first.wall)
          {
            out << " " << p.first << std::setw(26 - p.first.length())
                << ": ";
            timeinfo(p.second->last.user - p.second->first.user,
                     total.elapsed.user, out);
            out << "  ";
            timeinfo(p.second->last.sys - p.second->first.sys,
                     total.elapsed.sys, out);
            out << "  ";
            timeinfo(p.second->last.wall - p.second->first.wall,
                     total.elapsed.wall, out);
            out << '\n';
          }
      }
    out << '\n';

    out << " TOTAL (seconds)"  << std::setw(11) << ": "

        << std::setiosflags(std::ios::left) << std::setw(7)
        << float(total.elapsed.user) / clocks_per_sec
        << std::setw(11)
        << "user,"

        << std::setw(7)
        << float(total.elapsed.sys) / clocks_per_sec
        << std::setw(11)
        << "system,"

        << std::setw(7)
        << float(total.elapsed.wall) / clocks_per_sec
        << "wall"

        << std::resetiosflags(std::ios::left) << std::endl;
  }

  void
  timer::push(const std::string& task_name)
  {
    time_var* current;

    // If the stack is not empty, set the elapsed time for the current
    // task.
    if (!tasks.empty())
      tasks.top()->stop();

    if (tasksmap.find(task_name) == tasksmap.end())
      tasksmap[task_name] = new time_var;

    current = tasksmap[task_name];
    tasks.push(current);
    current->start();
  }

  void
  timer::pop()
  {
    precondition(!tasks.empty());

    // Set the elapsed time for the current task before popping it.
    tasks.top()->stop();
    tasks.pop();

    // Set the start time of the previous task to the current time.
    if (!tasks.empty())
      tasks.top()->start();
  }

  timer&
  timer::operator<<(const timer& rhs)
  {
    // No task should be running when merging timers.
    precondition(rhs.tasks.empty());

    for (const task_map_type::value_type& p : rhs.tasksmap)
      if (tasksmap.find(p.first) == tasksmap.end())
        tasksmap[p.first] = new time_var(*p.second);

    intmap.insert(rhs.intmap.begin(), rhs.intmap.end());
    return *this;
  }

  const long timer::clocks_per_sec = sysconf(_SC_CLK_TCK);

} // namespace misc
