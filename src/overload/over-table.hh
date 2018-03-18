/**
 ** \file overload/over-table.hh
 ** \brief Checking/translating an OverTiger program in a Tiger program.
 */

#pragma once

#include <map>
#include <vector>

namespace overload
{

  template <typename T>
  class OverTable
  {
  public:
    using map_type = std::multimap<const misc::symbol, T*>;
    using iterator = typename map_type::iterator;
    using const_iterator = typename map_type::const_iterator;
    using oversymtab_type = std::vector<map_type>;
    using range_type = std::pair<const_iterator, const_iterator>;

    /// Create a new over table.
    OverTable();

    /// \name Symbol handling
    /// \{
    /// Put \a key in the map and add the value to the associated container.
    void put(misc::symbol key, T& value);

    /// Return the range associated to the key.
    ///
    /// If the key is not found, the beginning and the end of the range are
    /// equal.
    range_type get(misc::symbol key);
    /// \}

    /// \name Scopes.
    /// \{
    /// \brief Open a new scope.
    ///
    /// All further type related declarations will be limited to this scope.
    void scope_begin();

    /// \brief Close the last scope.
    ///
    /// Forget everything (i.e. every type related informations) since the
    /// latest scope_begin().
    void scope_end();
    /// \}

    /// Print the table
    std::ostream& dump(std::ostream& ostr) const;

  protected:
    oversymtab_type oversymtab_;
  };

  template <typename T>
  std::ostream&
  operator<<(std::ostream& ostr, const OverTable<T>& tbl);

} // namespace type

#include <overload/over-table.hxx>
