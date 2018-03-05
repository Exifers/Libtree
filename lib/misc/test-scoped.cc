/**
 ** Testing the symbol tables.
 */

#include <ostream>

#include <misc/contract.hh>
#include <misc/scoped-map.hh>

int
main()
{
  using misc::scoped_map;

  const std::string toto1("toto");
  const std::string titi1("titi");

  // Checking symbol tables.
  misc::scoped_map<const std::string, int> t;
  {
    t.scope_begin();
    t.put(toto1, 11);
    t.put(titi1, 22);
    {
      t.scope_begin();
      t.put(toto1, 1111);
      assertion(t.get(toto1) == 1111);
      assertion(t.get(titi1) == 22);
      t.scope_end();
    }
    assertion(t.get(toto1) == 11);
    assertion(t.get(titi1) == 22);
    t.scope_end();
  }
}
