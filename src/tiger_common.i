// -*- C++ -*-

%module tiger_common

%include std_string.i

%{
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>
#include <string>
#include <misc/timer.hh>
%}

// Ofstream.
%inline %{
  struct Ofstream
  {
    Ofstream (const std::string& filename) : closed_ (false)
    {
      stream_ = new std::ofstream (filename.c_str ());
    }

    ~Ofstream ()
    {
      if (!closed_)
        close ();
    }

    std::ostream&
    to ()
    {
      assert (stream_);
      return *stream_;
    }

    void
    close ()
    {
      assert (stream_);
      stream_->close ();
      delete stream_;
      closed_ = true;
    }

    std::ofstream* stream_;
    bool closed_;
  };

  std::ostream&
  get_cout()
  {
    return std::cout;
  }

  std::ostream&
  get_cerr()
  {
    return std::cerr;
  }

  std::ostream* Cout = &std::cout;
  std::ostream* Cerr = &std::cerr;
  std::ostream* Clog = &std::clog;

  misc::timer timer;
%}
