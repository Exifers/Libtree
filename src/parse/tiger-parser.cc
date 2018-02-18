/**
 ** \file parse/tiger-parser.cc
 ** \brief Implementation of parse::TigerParser.
 */

#include <cstdlib>
#include <fstream>
#include <string>

#include <parse/parsetiger.hh>
#include <parse/scantiger.hh>
#include <parse/tiger-parser.hh>

namespace parse
{

  TigerParser::TigerParser(const misc::file_library& lib)
    : scanner_(new yyFlexLexer)
    , library_(lib)
  {}

  // Yes, this is exactly the default dtor.  But because it is defined
  // here, in the *.cc file, instead of "= default" in the *.hh file,
  // there is no need for all the members to be complete defined in
  // the header.  In particular, the scanner_ member acts as a Pimpl,
  // so we really want the generation of the dtor to be delayed to
  // here, not in the header.
  TigerParser::~TigerParser()
  {}

  /// Set the scanner traces.
  TigerParser&
  TigerParser::scan_trace(bool b)
  {
    scan_trace_p_ = b;
    return *this;
  }

  /// Set the parser traces.
  TigerParser&
  TigerParser::parse_trace(bool b)
  {
    parse_trace_p_ = b;
    return *this;
  }

  /// Enable object extensions.
  TigerParser&
  TigerParser::enable_object_extensions(bool b)
  {
    enable_object_extensions_p_ = b;
    return *this;
  }

  /// Enable syntax extensions.
  TigerParser&
  TigerParser::enable_extensions(bool b)
  {
    enable_extensions_p_ = b;
    return *this;
  }

  /// Parse a Tiger file or string.
  ast_type
  TigerParser::parse_()
  {
    std::string* fn = std::get_if<std::string>(&input_);

    /* The (address of) the string behind the symbol FILENAME is
       guaranteed to remain valid even after the symbol has been
       destroyed, so we can safely pass `&filename.name_get()' to
       `location_.initialize()'.  As for other symbols, the
       corresponding string will be deallocated at the end of the
       program.  */
    misc::symbol filename(fn == nullptr ? ""
                          : *fn == "-" ? "standard input"
                          : *fn);
    location_.initialize(&filename.get());

    std::shared_ptr<std::istream> in;
    if (fn == nullptr)
      // Parse a Tweast.
      in = (std::make_shared<std::stringstream>
            (std::get<Tweast*>(input_)->input_get()));
    else if (*fn == "-")
      // Parse from the standard input.
      in.reset(&std::cin, [](...){});
    else
      {
        // Parse from a file.
        in = std::make_shared<std::ifstream>(*fn);
        if (in->fail())
          error_ << misc::error::error_type::failure
                 << program_name
                 << ": cannot open `" << filename << "': "
                 << strerror(errno) << std::endl
                 << &misc::error::exit;
      }

    /* Initialize the scanner and parser, then parse and close. */
    scanner_->scan_open_(*in);

    parser parser(*this);
    try
    {
      parser.set_debug_level((bool) getenv("PARSE"));
    }
    catch(...)
    {
      parser.set_debug_level(0);
    }
    parser.parse();

    /* close the scanner */
    scanner_->scan_close_();

    ast_type res = ast_;
    ast_ = static_cast<ast::Exp*>(nullptr);

    return res;
  }

  /*---------------.
  | Parse a file.  |
  `---------------*/

  ast_type
  TigerParser::parse_file(const misc::path& name)
  {
    if (parse_trace_p_)
      std::cerr << "Parsing file: " << name << '\n';
    input_ = name.string();
    return parse_();
  }

  /*----------------.
  | Parse a Tweast. |
  `----------------*/

  ast_type
  TigerParser::parse_input(Tweast& s, bool extensions)
  {
    std::swap(extensions, enable_extensions_p_);
    if (parse_trace_p_)
      std::cerr << "Parsing string: " << s.input_get() << '\n';
    input_ = &s;
    ast_type res = parse_();
    std::swap(extensions, enable_extensions_p_);
    return res;
  }

  ast_type
  TigerParser::parse(Tweast& s)
  {
    return parse_input(s, true);
  }

  /*-----------------.
  | Parse a string.  |
  `-----------------*/

  ast_type
  TigerParser::parse(const std::string& s)
  {
    Tweast in(s);
    return parse_input(in, false);
  }

  /*-----------------------.
  | Parse a Tiger import.  |
  `-----------------------*/

  ast::DecsList*
  TigerParser::parse_import(const std::string& name, const location& loc)
  {
    // Try to find directory containing the file to import.
    misc::path directory_path = library_.find_file(name);

    if (directory_path.empty())
      {
        error_ << misc::error::error_type::failure
               << loc << ": "
               << name << ": file not found.\n";
        return nullptr;
      }

    // Complete path of file (directory + filename).
    misc::path absolute_path
      = directory_path / misc::path(misc::path(name).filename());

    // Detect recursive inclusion.
    if (open_files_.find(absolute_path) != open_files_.end())
      {
        error_ << misc::error::error_type::failure
               << loc << ": " << name
               << ": recursive inclusion.\n"
               << open_files_[absolute_path]
               << ": initial inclusion was here.\n";
        return nullptr;
      }

    library_.push_current_directory(directory_path);
    open_files_[absolute_path] = loc;
    // Save the inputs, and reset them.
    input_type saved_input = input_;
    location saved_location = location_;
    // Parse the imported file.
    ast::DecsList* res = nullptr;
    try
      {
        res = parse_file(absolute_path);
      }
    // c++17 - std::variant
    // replace boost::bad_get by adequate exception in std
    catch (std::bad_variant_access& e)
      {
        error_ << misc::error::error_type::parse
               << absolute_path << ": imported from " << loc
               << ": syntax error, unexpected exp, expecting decs.\n";
        error_.exit();
      }
    // Set the inputs back to their original values.
    input_ = saved_input;
    location_ = saved_location;

    open_files_.erase(absolute_path);
    library_.pop_current_directory();
    return res;
  }

  const misc::error&
  TigerParser::error_get() const
  {
    return error_;
  }

} // namespace parse
