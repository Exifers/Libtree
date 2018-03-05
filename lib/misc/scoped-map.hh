/**
 ** \file misc/scoped-map.hh
 ** \brief Declaration of misc::scoped_map.
 **
 ** This implements a stack of dictionnaries.  Each time a scope is
 ** opened, a new dictionnary is added on the top of the stack; the
 ** dictionary is removed when the scope is closed.  Lookup of keys
 ** is done in the last added dictionnary first (LIFO).
 **
 ** In particular this class is used to implement symbol tables.
 **/

#pragma once

#include <map>
#include <vector>

namespace misc
{

  template <typename Key, typename Data>
  class scoped_map
  {
    public:
      /** Constructs an empty scoped_map, ie an empty vector. */
      scoped_map() = default;
      ~scoped_map() = default;

      /** Adds a variable defined by pair \a key \a value in the last map. */
      void put(const Key& key, const Data& value);

      /** Returns the value matching the key \a key from the last map on the
       * stack. */
      Data get(const Key& key) const;

      /** Dumps the scoped_map into \a ostr in a human readable manner. */
      std::ostream& dump(std::ostream& ostr);

      /** Creates a new map on the stack and copies all variables defined below.
      */
      void scope_begin();

      /** Deletes the last map on the stack. */
      void scope_end();
    private:
      std::vector<std::map<Key, Data>> stack_;
  };

  template <typename Key, typename Data>
  std::ostream&
  operator<<(std::ostream& ostr, const scoped_map<Key, Data>& tbl);

  // FIXME: Some code was deleted here.

} // namespace misc

#include <misc/scoped-map.hxx>
