/**
 ** Test code for misc::variant.
 */

#include <cstdlib>
#include <string>

#include <misc/variant.hh>

int
main()
{
  using variant_type = misc::variant<int, std::string>;
  using multiple_variant_type = misc::variant<int, std::string, double>;

  // Sucessful conversion.
  {
    variant_type v("Hello");
    std::string s = v;
  }

  // Failing conversion (trying to convert to the a bad dynamic type
  // among the variant's ones).
  {
    bool failure = true;
    variant_type v(42);
    try
      {
        std::string s = v;
      }
    catch (std::bad_variant_access& e)
      {
        failure = false;
      }

    if (failure)
      exit(EXIT_FAILURE);
  }

  // Succesful conversion.
  {
    multiple_variant_type v("Hello");
    std::string s = v;
  }

  // Successful conversion.
  {
    multiple_variant_type v(56.7);
    double d = v;
  }

  // Failing conversion (trying to convert to the bad dynamic type
  // out of the variant's one).
  {
    bool failure = true;
    multiple_variant_type v(34.5);
    try
      {
        int i = v;
      }
    catch (std::bad_variant_access& e)
      {
        failure = false;
      }

    if (failure)
      exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
