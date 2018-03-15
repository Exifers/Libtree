/** \file misc/scoped-map.hxx
 ** \brief Implementation of misc::scoped_map.
 */

#pragma once

#include <sstream>
#include <stdexcept>
#include <type_traits>

#include <misc/algorithm.hh>
#include <misc/contract.hh>
#include <misc/indent.hh>

namespace misc
{
  template <typename Key, typename Data>
  void scoped_map<Key, Data>::put(const Key& key, const Data& value)
  {
    if (stack_.size() == 0)
      return;
    stack_.back()[key] = value;
  }

  template <typename Key, typename Data>
  Data scoped_map<Key, Data>::get(const Key& key) const
  {
    auto cur = stack_.back();
    try
    {
      return cur[key];
    }
    catch(...)
    {
      if (std::is_pointer<Data>::value)
      {
        Data p = nullptr;
        return p;
      }
      else
      {
        throw std::range_error("No such key was found in map");
      }
    }
  }

  template <typename Key, typename Data>
  std::ostream& scoped_map<Key, Data>::dump(std::ostream& ostr)
  {
    for (auto it = stack_.begin(); it != stack_.end(); it++)
    {
      for (auto mit = it->begin(); mit != it->end(); mit++)
      {
        ostr << mit->first << " : " << mit->second << "\n";
      }
    }
    return ostr;
  }

  template <typename Key, typename Data>
  void scoped_map<Key, Data>::scope_begin()
  {
    if (stack_.size() == 0)
    {
      stack_.push_back(std::map<Key, Data>());
    }
    else
    {
      auto cur_cpy = stack_.back();
      stack_.push_back(cur_cpy);
    }
  }

  template <typename Key, typename Data>
  void scoped_map<Key, Data>::scope_end()
  {
    stack_.pop_back();
  }

  template <typename Key, typename Data>
  inline std::ostream&
  operator<<(std::ostream& ostr, const scoped_map<Key, Data>& tbl)
  {
    return tbl.dump(ostr);
  }

} // namespace misc
