/**
 ** \file parse/libparse.cc
 ** \brief Functions and variables exported by the parse module.
 */

#include <ast/decs.hh>
#include <ast/decs-list.hh>
#include <misc/file-library.hh>
#include <misc/symbol.hh>
#include <parse/libparse.hh>
#include <parse/location.hh>
#include <parse/tiger-parser.hh>
#include <parse/tweast.hh>

// Define exported parse functions.
namespace parse
{

  // Parse a Tiger file, return the corresponding abstract syntax.
  std::pair<ast::DecsList*, misc::error>
  parse(const std::string& prelude,
        const std::string& fname,
        misc::file_library& library,
        bool scan_trace_p, bool parse_trace_p
        , bool enable_object_extensions_p
        )
  {
    // Current directory must be that of the file currently processed.
    library.push_current_directory(misc::path(fname).parent_path());

    TigerParser tp(library);
    tp.scan_trace(scan_trace_p)
      .parse_trace(parse_trace_p);
    tp.enable_object_extensions(enable_object_extensions_p);

    ast::DecsList* res = nullptr;

    ast_type tree = tp.parse_file(fname);


    ast::Exp** exp = std::get_if<ast::Exp*>(&tree);
    ast::DecsList** decs = std::get_if<ast::DecsList*>(&tree);

    // Try to parse the program as an expression, and check that the
    // parsing did not fail in that case.
    if (exp && *exp)
      {
        Tweast in;

        if (!prelude.empty())
          {
            ast::DecsList* prelude_decs =
              (prelude == "builtin"
               ? std::get<ast::DecsList*>(tp.parse(tp.prelude()))
               : tp.parse_import(prelude, location()));
            if (prelude_decs)
              in << prelude_decs;
          }
        in << "function _main() = (" << *exp << "; ())";
        res = tp.parse(in);
      }
    // Try to parse the program as a list of declarations, and check
    // that the parsing did not fail in that case.
    else if (decs && *decs)
      {
        // Try to parse the program as a list of declarations.
        res = *decs;
      }
    // Otherwise, the parsing failed, and an error will be returned as
    // second member of the return value.

    // Ensure that directory stack is not modified by parse.
    library.pop_current_directory();

    return std::pair(res, tp.error_get());
  }

  ast_type
  parse(Tweast& input)
  {
    TigerParser tp;
    tp.enable_extensions();
    tp.enable_object_extensions();
    ast_type res = tp.parse(input);
    if (tp.error_get())
      {
        misc::error e;
        e << tp.error_get() << input;
        e.ice_here();
      }
    return res;
  }

  ast::Exp*
  parse(const std::string& str
        , bool enable_object_extensions_p
        )
  {
    TigerParser tp;
    tp.enable_object_extensions(enable_object_extensions_p);
    ast::Exp* res = tp.parse(str);
    tp.error_get().ice_on_error_here();
    return res;
  }

  ast::DecsList*
  parse_unit(const std::string& str
        , bool enable_object_extensions_p
        )
  {
    TigerParser tp;
    tp.enable_object_extensions(enable_object_extensions_p);
    std::string rewrite = "function _main() = (" + str + "; ())";
    ast::DecsList* res = tp.parse(rewrite);
    tp.error_get().ice_on_error_here();
    return res;
  }

  // Parse a set of declarations.
  ast::Decs*
  parse_decs(Tweast& in)
  {
    ast::DecsList* dl = parse(in);
    assertion(dl->decs_get().size() == 1);
    ast::Decs* res = dl->decs_get().front();
    dl->decs_get().pop_front();
    delete dl;
    return res;
  }

} // namespace parse
