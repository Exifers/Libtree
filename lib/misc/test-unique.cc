/**
 ** Testing the Flyweight pattern.
 */

#include <iostream>

#include <misc/contract.hh>
#include <misc/unique.hh>

int
main()
{
  using unique_int = misc::unique<int>;
  unique_int the_answer = 42;
  unique_int the_same_answer = 42;
  unique_int the_solution = 51;

  // Checking misc::unique<int>.
  assertion(the_answer == unique_int(42));
  assertion(the_answer == the_same_answer);
  assertion(the_answer != the_solution);

  std::cout << the_answer << '\n';
}
