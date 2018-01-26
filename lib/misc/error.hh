/**
 ** \file misc/error.hh
 ** \brief Declare error.
 */

#pragma once

#include <iosfwd>
#include <sstream>

/// Shortcuts.
/// \{
#define ice_here() ice(__FILE__, __LINE__)
#define ice_on_error_here() ice_on_error(__FILE__, __LINE__)
/// \}

namespace misc
{

  /** \brief Handle errors in the whole project.
   **
   ** Each task has an error status depending on its exit code
   ** described in the enum below.
   **
   ** Several versions of operator<< are used to fill the handler.
   **
   ** A global variable is defined to centralize all the error uses.
   */

  class error
  {
  public:
    error();
    error(const error& e);

    /// Copy an error.
    error& operator=(const error& e);

    /// \name Filling the error handler.
    /// \{

    /// With what exit status should we end?
    enum class error_type: unsigned
      {
        /// Job successfully done.
        success = 0,
        /// Some unspecified error happened.
        failure = 1,
        /// Lexical error.
        scan = 2,
        /// Syntactic error.
        parse = 3,
        /// Binding error: undefined name.
        bind = 4,
        /// Type checking error.
        type = 5
      };

    /// General method: put the parameter in stream_.
    template <typename T> error& operator<<(const T& t);

    /// Set the status if \a e is lower than the current status.
    error& operator<<(error_type e);

    /// Accept std::endl etc.
    error& operator<<(std::ostream& (*f)(std::ostream&));

    /// Import errors.
    error& operator<<(const error& rhs);

    /// Member manipulator signature.
    using member_manip_type = void (error::*)();
    /// Const member manipulator signature.
    using const_member_manip_type = void (error::*)() const;

    /// Hook for member manipulators.
    error& operator<<(member_manip_type f);
    /// Hooks for const member manipulators.
    error& operator<<(const_member_manip_type f);

    /// \}


    /// \name Member manipulators.
    /// \{

    /// Throw an exception to exit.
    [[noreturn]] void exit() const;

    /// If the error status is set, throw an exception to exit.
    void exit_on_error() const;

    /// Throw an Internal Compiler Error.
    void ice(const char* file, int line) const;

    /// If the error status is set, consider that an Internal Compiler
    /// Error has happened and abort.
    void ice_on_error(const char* file, int line) const;

    /// Reset to no error.
    void clear();

    /// \}


    /// \name Accessors.
    /// \{

    /// True if an error is recorded.
    operator bool() const;

    /// Get the current status.
    error_type status_get() const;

    /// Get the current status value.
    unsigned status_get_value() const;

    /// Get the stream associated with the class.
    const std::ostringstream& stream_get() const;

    /// \}

  private:
    /// The current exit status.
    error_type status_;

    /// The current error message.
    std::ostringstream stream_;
  };

  /// Display the error message on the given ostream.
  std::ostream& operator<<(std::ostream& o, const error& e);

} // namespace misc

#include <misc/error.hxx>
