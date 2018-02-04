/**
 ** \file misc/file-library.hxx
 ** \brief implements inline function of misc/file-library.hh
 */

#pragma once

#include <misc/file-library.hh>

namespace misc
{

  inline std::ostream&
  operator<<(std::ostream& ostr, const file_library& l)
  {
    return l.dump(ostr);
  }

} // namespace misc
