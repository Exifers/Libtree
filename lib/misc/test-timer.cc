/**
 ** Test the timing nested tasks.
 */

#include <iostream>
#include <unistd.h>

#include <misc/timer.hh>

int main()
{
  misc::timer t;
  enum timevar
  {
    One = 1,
    Two,
    Three
  };

  t.name(One, "One");
  t.name(Two, "Two");
  t.name(Three, "Three");

  t.start();

  t.push(One);
  sleep(1);
  t.pop(1);

  t.push("Two");
  sleep(2);
  t.pop("Two");

  t.push("Three");
  sleep(3);
  t.pop(Three);

  t.stop();
  t.dump(std::cerr);
}
