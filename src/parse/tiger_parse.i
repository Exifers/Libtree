// -*- C++ -*-

%module tiger_parse

%include "std_string.i"
%include "std_pair.i"


%{
#  include <sstream>
#  include <misc/error.hh>
#  include <parse/position.hh>
#  include <parse/location.hh>
#  include <parse/tiger-parser.hh>
#  include <parse/libparse.hh>
%}

%include "parse/fwd.hh"

// Explicit instantiation of MetavarMap's.
%include "parse/metavar-map.hh"
%template() parse::MetavarMap<ast::Exp>;
%template() parse::MetavarMap<ast::Var>;
%template() parse::MetavarMap<ast::NameTy>;
%template() parse::MetavarMap<ast::DecsList>;

/*------------------.
| parse::position.  |
`------------------*/

// Replace parse::position's ctor and ignore parse::position::initialize,
// as Python is unable to parse the literal `1u' used as default value
// of two of their arguments.
%extend parse::position
{
  // External ctor.  For more information, see
  // http://www.nabble.com/Java---adding-code-to-a-constructor-td20210601.html
  position (const std::string* f = nullptr,
            unsigned int l = 1, unsigned int c = 1)
  {
    return new parse::position(f, l, c);
  }
}
%ignore parse::position::position;
%ignore parse::position::initialize;
%include "parse/position.hh"
%extend parse::position
{
  std::string
  __str__ () const
  {
    std::ostringstream o;
    o << *$self;
    return o.str ();
  }
}

/*------------------.
| parse::location.  |
`------------------*/

// Ignore parse::location::initialize, as Python is unable to
// parse the literal `1u' used as default value of two of its
// arguments.
%ignore parse::location::initialize;
%include "parse/location.hh"
%extend parse::location
{
  std::string
  __str__ () const
  {
    std::ostringstream o;
    o << *$self;
    return o.str ();
  }
}

/*-----------.
| libparse.  |
`-----------*/

%import "parse/tweast.hh"
%include "parse/tiger-parser.hh"
%inline
{
  namespace parse
  {
    // Parse a Tiger file, return the corresponding abstract syntax.
    ast::DecsList*
    parse (const std::string& prelude, const std::string& fname,
           misc::file_library& library)
    {
      std::pair<ast::DecsList*, misc::error> res =
        parse (prelude, fname, library, false, false);
      res.second.exit_on_error ();
      return res.first;
    }
  }

}

%include "parse/libparse.hh"
