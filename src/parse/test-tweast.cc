/**
 ** Test the tweast.
 **/

#include <iostream>
#include <misc/contract.hh>
#include <misc/symbol.hh>
#include <parse/libparse.hh>
#include <parse/location.hh>
#include <parse/tweast.hh>

const char* program_name = "test-tweast";

int
main()
{
  try
    {
      parse::Tweast in;
    }
  catch (misc::error& e)
    {
      std::cerr << e;
      exit(e.status_get_value());
    }

}
