/**
 ** \file parse/libparse.hh
 ** \brief Declare functions and variables exported by parse module.
 */

#pragma once

#include <set>
#include <string>
#include <utility>

#include <misc/error.hh>
#include <misc/file-library.hh>
#include <parse/fwd.hh>

// This forward declarations is provided to allow the compilation of
// the project without the `ast' module at TC-1.  Remove it as soon
// as this module is available (i.e., at TC-2).
namespace ast
{

  class Decs;

} // namespace ast

/// Parsing the input, delivering an ast::Ast.
namespace parse
{

  /// \brief Parse a Tiger file, return the corresponding abstract syntax tree.
  ///
  /// \param prelude                    name of the prelude file.
  /// \param fname                      path and name of the tiger file.
  /// \param library                    library for managing search path.
  /// \param scan_trace_p               display information on scan step.
  /// \param parse_trace_p              display information on parse step.
  /// \param enable_object_extensions_p enable object constructions
  ///
  /// \return a pair composed of a pointer to an abstract parse tree
  ///         (set to `nullptr' upon failure) and an error status.
  ///         This function is the only interface available between
  ///         the scanner/parser and the rest of the program.

#ifdef SWIG
  %newobject parse;
#endif

  std::pair<ast::DecsList*, misc::error>
  parse(const std::string& prelude,
        const std::string& fname,
        misc::file_library& library,
        bool scan_trace_p, bool parse_trace_p
        , bool enable_object_extensions_p = false
       );

  /// \brief Parse a Tweast.
  ///
  /// Extensions are enabled.  Raises an exception on errors.
  ast_type parse(Tweast& input);

  /// Parse a std::string. Used for unit tests.
  ast::Exp* parse(const std::string& str
                  , bool enable_object_extensions_p = false
                 );

  /// Parse a std::string. Used for unit tests.
  /// The declaration of the _main function is automatically added.
  ast::DecsList* parse_unit(const std::string& str
                            , bool enable_object_extensions_p = false
                           );


} // namespace parse
