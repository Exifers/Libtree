/**
 ** \file parse/metavar-map.hxx
 ** \brief Implementation of parse::MetavarMap.
 */

#pragma once

#include <sstream>

#include <boost/lexical_cast.hpp>
#include <parse/metavar-map.hh>

namespace parse
{

  template <typename Data>
  MetavarMap<Data>::MetavarMap(const std::string& name)
    : name_(name), map_()
  {}

  template <typename Data>
  MetavarMap<Data>::~MetavarMap()
  {
    assertion(map_.empty());
  }

  template <typename Data>
  std::string
  MetavarMap<Data>::show(unsigned key)
  {
    return '_' + name_ + '(' + boost::lexical_cast<std::string>(key) + ')';
  }

  template <typename Data>
  std::string
  MetavarMap<Data>::append_(unsigned& count, Data* data)
  {
    map_[count] = data;
    return show(count++);
  }

  template <typename Data>
  Data*
  MetavarMap<Data>::take_(unsigned key)
  {
    return map_.take(key);
  }

}
