/**
 ** \file  misc/escape.cc
 ** \brief Implementation for misc/escape.hh.
 **/

#include <cctype>
#include <iomanip>
#include <ios>
#include <map>

#include <misc/escape.hh>

namespace misc
{

  std::ostream&
  escaped::print(std::ostream& ostr) const
  {
    return escape_(ostr, pobj_str_);
  }

  std::ostream&
  escaped::escape_(std::ostream& o, const std::string& es) const
  {
    // For some reason yet to be found, when we use the locale for
    // std::isprint, Valgrind goes berzerk.  So we no longer do the
    // following:
    //
    // static std::locale locale("");
    //
    // if (std::isprint(*p, locale))
    std::ios_base::fmtflags flags = o.flags(std::ios_base::oct);
    char fill = o.fill('0');

    /* The GNU Assembler does not recognize `\a' as a valid
       escape sequence, hence this explicit conversion to the
       007 octal character.  For more information, see
       http://sourceware.org/binutils/docs/as/Strings.html.  */
    std::map<char, std::string> escapes =
    {
      {'\a', "\\007"}, {'\b', "\\b"}, {'\f', "\\f"},
      {'\n', "\\n"}, {'\r', "\\r"}, {'\t', "\\t"},
      {'\v', "\\v"}, {'\\', "\\\\"}, {'\"', "\\\""}
    };

    for (const auto& p : es)
      {
        auto escape_it = escapes.find(p);
        if (escape_it != escapes.end())
          o << escape_it->second;
        else
          {
            if (std::isprint(p))
              o << p;
            else
              o << "\\" << std::setw(3)
                << static_cast<int>(static_cast<unsigned char>(p));
          }
      }

    o.fill(fill);
    o.flags(flags);
    return o;
  }

} // namespace misc
