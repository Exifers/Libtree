#undef NDEBUG
#include <iostream>

#include <misc/contract.hh>
#include <type/types.hh>

using namespace type;

#define ASSERT(Exp)                             \
{                                               \
  std::cerr << #Exp << '\n';                    \
  assertion(Exp);                               \
}

int
main()
{
  // Define the named type `a', pointing to `b', pointing to `int'.
  const Named b("b", &Int::instance());
  const Named a("a", &b);

  // This definition is sound.
  ASSERT(a.sound());

  // Check that `a' points to `int'.
  ASSERT(a == b);
  ASSERT(a == Int::instance());

  // Equal types are compatible.
  ASSERT(a.compatible_with(b));
  ASSERT(b.compatible_with(a));
  ASSERT(a.compatible_with(Int::instance()));
  ASSERT(Int::instance().compatible_with(a));

  // Unsound is insane :)
  const Named c = Named("c");
  const Named d = Named("d", &c);
  c.type_set(&d);
  ASSERT(!c.sound());


  // Check the case of records.  Make it recursive for fun, and more
  // in depth checking anyway.
  const Named Rec("Rec");
  Record rec;
  rec.field_add("Rec", Rec);
  Rec.type_set(&rec);
  ASSERT(Rec.sound());

  ASSERT(Rec == rec);
  ASSERT(rec == Rec);

  const Nil n{};
  ASSERT(Rec.compatible_with(n));
  ASSERT(n.compatible_with(Rec));

  ASSERT(! Rec.compatible_with(Int::instance()));
  ASSERT(! Int::instance().compatible_with(Rec));
}
