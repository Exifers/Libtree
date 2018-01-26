/**
 ** \file misc/file-library.cc
 ** \brief Implements misc::file_library.
 */

#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <unistd.h>

#include <misc/contract.hh>
#include <misc/file-library.hh>

namespace misc
{

  void
  file_library::push_cwd()
  {
    // Store the working directory
    char cwd[MAXPATHLEN + 1];

    if (nullptr == getcwd(cwd, MAXPATHLEN + 1))
      throw std::runtime_error("working directory name too long");

    push_current_directory(path(std::string(cwd)));
  }


  file_library::file_library()
  {
    push_cwd();
  }

  file_library::file_library(path p)
  {
    push_cwd();
    // Then only process given path.
    search_path_.emplace_back(p);
  }

  void
  file_library::append_dir_list(std::string path_list)
  {
    std::string::size_type pos;

    while ((pos = path_list.find(':')) != std::string::npos)
      {
        append_dir(path_list.substr(0, pos));
        path_list.erase(0, pos + 1);
      }
    append_dir(path_list);
  }


  path
  file_library::ensure_absolute_path(path p) const
  {
    if (p.is_absolute())
      return p;
    else
      return current_directory_get() / p;
  }

  void
  file_library::append_dir(path p)
  {
    search_path_.emplace_back(ensure_absolute_path(p));
  }

  void
  file_library::prepend_dir(path p)
  {
    search_path_.insert(search_path_.begin(), ensure_absolute_path(p));
  }

  void
  file_library::push_current_directory(path p)
  {
    // Ensure that path is absolute.
    if (!p.is_absolute())
      p = current_directory_get() / p;

    current_directory_.insert(current_directory_.begin(), p);
  }

  void
  file_library::pop_current_directory()
  {
    precondition(!current_directory_.empty());

    current_directory_.erase(current_directory_.begin());
  }

  path
  file_library::current_directory_get() const
  {
    precondition(!current_directory_.empty());

    return current_directory_.front();
  }


  path
  file_library::find_file(const std::string& file)
  {
    // Split file in two components, basename and basedir.
    path p = path(file);
    path directory = p.filename();

    if (directory.is_absolute())
      {
        // If file is absolute, just check that it exists.
        if (!boost::filesystem::exists(path(file)))
          return path();
      }
    else
      {
        // Does the file can be found in current directory?
        if (find_in_directory(current_directory_get(), file))
          return (current_directory_get() / file).parent_path();

        directory = find_in_search_path(directory, p.filename().string());
      }

    return directory;
  }

  bool
  file_library::find_in_directory(const path& dir,
                                  const std::string& file) const
  {
    return boost::filesystem::exists(path(dir / file));
  }

  path
  file_library::find_in_search_path(const path& relative_path,
                                    const std::string& filename) const
  {
    path checked_dir;

    // Otherwise start scanning the search path.
    for (const path& p : search_path_)
      {
        if (p.is_absolute())
          checked_dir = p;
        else
          checked_dir = current_directory_get() / p;

        checked_dir /= relative_path;

        if (find_in_directory(checked_dir, filename))
          return checked_dir;
      }

    // File not found in search path.
    return path();
  }

  std::ostream&
  file_library::dump(std::ostream& ostr) const
  {
    ostr << ".";
    for (const path& p : search_path_)
      ostr << ":" << p;
    return ostr;
  }

} // namespace misc
