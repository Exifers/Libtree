/**
 ** \file misc/symbol.cc
 ** \brief Implementation of misc::symbol.
 */

#include <sstream>

#include <boost/lexical_cast.hpp>

#include <misc/symbol.hh>

namespace misc
{

  symbol::symbol(const std::string& s)
    : unique<std::string>(s)
  {}

  symbol::symbol(const char* s)
    : unique<std::string>(std::string(s))
  {}

  symbol
  symbol::fresh()
  {
    return fresh("a");
  }

  symbol
  symbol::fresh(const symbol& s)
  {
    /// Counter of unique symbols.
    static unsigned counter_ = 0;
    std::string str =
      s.get() + "_" + boost::lexical_cast<std::string>(counter_);
    ++counter_;
    return symbol(str);
  }

} // namespace symbol
