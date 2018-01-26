/**
 ** Test code for misc/indent.hh features.
 */

#include <iostream>
#include <sstream>

#include <misc/contract.hh>
#include <misc/indent.hh>

using misc::iendl;
using misc::incendl;
using misc::decendl;

int main()
{
  std::ostringstream s;

  s << "{" << incendl
    << "1," << iendl
    << "2," << iendl
    << "{" << incendl
    << "2.1," << iendl
    << "2.2" << decendl
    << "}," << iendl
    << "3" << decendl
    << "}\n";

  std::string expected = "{\n\
  1,\n\
  2,\n\
  {\n\
    2.1,\n\
    2.2\n\
  },\n\
  3\n\
}\n\
";
  assertion(s.str() == expected);
}
