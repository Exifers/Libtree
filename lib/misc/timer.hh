/**
 ** \file misc/timer.hh
 ** \brief timer: Timing nested tasks.
 */

#pragma once

#include <iosfwd>
#include <iostream>
#include <map>
#include <stack>
#include <string>

namespace misc
{

  /// Timing nested tasks.
  class timer
  {
  public:
    timer();
    timer(const timer& rhs);
    ~timer();

    /// Start a sub timer for a named task.
    /// \param name a constant string which is the task's name
    void push(const std::string& name);

    /// Start a sub timer with an integer corresponding to a task.
    /// \see push()
    /// \see name()
    void push(int i);

    /// Stop the current task and ensure its name matches the string
    /// passed as argument.
    /// \param task_name The name of the task to stop.
    void pop(const std::string& task_name);

    /// \see pop()
    /// \see pop(const std::string name)
    void pop(int i);

    /// Stop the current task's timer(the last task pushed on the stack).
    void pop();

    /// Write results.
    /// \param out An output stream, set to std::cerr by default.
    void dump(std::ostream& out = std::cerr);

    /// Enable automatic information dumping upon destruction of the
    /// timer on stream \a out.
    void dump_on_destruction(std::ostream& out);

    /// Assign name \a task_name to task number \a i.
    void name(int i, const std::string& task_name);

    /// Start the timer.
    /// \see stop()
    void start();

    /// Stop the timer.
    /// \see start()
    void stop();

    /// \brief Import timer.
    ///
    /// Import tasks defined in \a rhs.  The total execution time of
    /// \a rhs is ignored.
    ///
    /// \pre No task should be running in \a rhs.
    timer& operator<<(const timer& rhs);

  private :
    class time_var;
    class time
    {
      friend class timer;
      friend class timer::time_var;
    public:
      time();

      time & operator+=(const time& rhs);

    private :
      long user;
      long sys;
      long wall;
    };

    class time_var
    {
    public:
      time_var();

      void start();
      void stop();

      bool is_zero();

      time begin;
      time elapsed;
      time first;
      time last;
      bool initial;
    };

    /// Write formatted timing results on \a out.
    void timeinfo(long time, long total_time, std::ostream& out);

    using task_map_type = std::map<const std::string, time_var*>;

    /// Time information associated to each task name.
    task_map_type tasksmap;

    /// Stack of timed tasks.
    std::stack<time_var*> tasks;

    /// Dictionnary mapping an integer to a task name.
    /// \see push(int)
    std::map<int, std::string> intmap;

    /// Total time measured by the timer.
    /// \see start()
    /// \see stop()
    time_var total;

    /// A potential stream onto which results are dumped when the
    /// timer is destroyed.  If this pointer is null, no action is
    /// taken during the destruction of the timer.
    std::ostream* dump_stream;

    /// Number of clocks ticks per second, set according to the system
    /// timing function used.
    static const long clocks_per_sec;
  };

} // namespace misc

#include <misc/timer.hxx>
