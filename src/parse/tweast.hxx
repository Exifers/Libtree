/**
 ** \file parse/tweast.hxx
 ** \brief implements inline methods of parse/tweast.hh
 */

#pragma once

#include <algorithm>

#include <boost/algorithm/string/replace.hpp>

#include <misc/algorithm.hh>
#include <misc/error.hh>
#include <parse/tweast.hh>

namespace parse
{

  template <typename T>
  T&
  Tweast::append_(unsigned&, T& data) const
  {
    return data;
  }

  template <typename T>
  Tweast&
  Tweast::operator<<(const T& t)
  {
    input_ << append_(count_, t);
    return *this;
  }

  template <typename T>
  T*
  Tweast::take(unsigned s)
  {
    T* t = nullptr;
    try
      {
        t = MetavarMap<T>::take_(s);
      }
    catch (std::range_error& e)
      {
        // Print the contents of the Tweast before dying.
        misc::error error;
        error << e.what() << std::endl;
        error << *this;
        error.ice_here();
      }
    return t;
  }

  template <typename T>
  void
  Tweast::move_metavars_(Tweast& tweast, std::string& input)
  {
    using metavars_type = MetavarMap<T>;
    for (const typename metavars_type::map_type::value_type& var :
           tweast.metavars_type::map_)
      {
        // Append the variable from VAR to the enclosing Tweast.
        unsigned old_num = var.first;
        // Warning, this is not thread-safe.
        unsigned new_num = count_;
        T* data = var.second;
        metavars_type::map_[new_num] = data;
        ++count_;

        // Rename metavariables according to the numbering scheme
        // within the input string.
        std::string old_str = metavars_type::show(old_num);
        std::string new_str = metavars_type::show(new_num);
        // FIXME: This is inefficient, since the string is viewed
        // each time a metavariable is processed.  Better store
        // each (old_num, new_num) pair in a map, and process
        // the string in a single pass.
        boost::algorithm::replace_first(input,
                                        old_str, new_str);
      }
    tweast.metavars_type::map_.clear();
  }

} // namespace parse
