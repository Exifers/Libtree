/** \file misc/contract.cc
 ** \brief Implementation for contract.hh
 */

#include <cstdlib>
#include <iostream>

#include <misc/contract.hh>

void __FailedCondition(const char* condType,
                       const char* condText,
                       const char* fileName,
                       int fileLine)
{
  std::cerr << fileName << ':'
            << fileLine
            << ": "
            << condType << " `"
            << condText << "' failed.\n";
  abort();
}

void __Terminate(const char* fileName, int fileLine, const char* reason)
{
  std::cerr << fileName << ":" << fileLine
            << ": Program abortion (" << reason << ")\n";
  abort();
}
