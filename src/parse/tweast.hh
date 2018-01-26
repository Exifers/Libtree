/**
 ** \file parse/tweast.hh
 ** \brief Declaration of parse::Tweast.
 */

#pragma once

#include <iostream>
#include <map>
#include <sstream>


// These forward declarations are provided to allow the compilation of
// the project without the `ast' module at TC-1.  Remove them as soon
// as this module is available (i.e., at TC-2).
namespace ast
{

  class Exp;
  class Var;
  class NameTy;
  class DecsList;

} // namespace ast
#include <misc/map.hh>
#include <misc/symbol.hh>
#include <parse/metavar-map.hh>

namespace parse
{

  /// \brief TWEAST stands for ``Text With Embedded Abstract Syntax Trees''.
  ///
  /// Aggregate string to parse and tables of metavariables.
  class Tweast
    : public MetavarMap<ast::Exp>
    , public MetavarMap<ast::Var>
    , public MetavarMap<ast::NameTy>
    , public MetavarMap<ast::DecsList>
  {
  public:
    Tweast();
    Tweast(const std::string& str);
    virtual ~Tweast() = default;

    /// \brief Stream manipulator.
    ///
    /// Append Tiger expressions to the string to parse.
    template <typename T> Tweast& operator<<(const T& t);

    /// Metavariables manipulator.
    template <typename T> T* take(unsigned s);


    /// Get the current input string.
    std::string input_get() const;

    /// Print the table
    std::ostream& dump(std::ostream& ostr) const;

  protected:
    // Insert base class members in the current scope.
    using MetavarMap<ast::Exp>::append_;
    using MetavarMap<ast::Var>::append_;
    using MetavarMap<ast::NameTy>::append_;
    using MetavarMap<ast::DecsList>::append_;

    /// Fake append (default case, i.e. when \a data is not a metavariable).
    template <typename T> T& append_(unsigned&, T& data) const;


  protected:
    /// The next identifier suffix to create.
    static unsigned count_;

    /// The string to parse.
    std::stringstream input_;
  };

  /// Display the content of the tweast.
  std::ostream& operator<<(std::ostream& ostr, const Tweast& in);

} // namespace parse

#include <parse/tweast.hxx>
