/**
 ** \file misc/variant.hxx
 ** \brief Implementation of misc::variant.
 **/

#pragma once

#include <variant>

#include <misc/variant.hh>
#include <type_traits>

#include <iostream>

namespace misc
{

  template <typename T, typename... Ts>
  template <typename U>
  variant<T, Ts...>::variant(const U& rhs)
    : super_type(rhs)
  {}

  template <typename T, typename... Ts>
  template <typename U>
  variant<T, Ts...>&
  variant<T, Ts...>::operator=(const U& rhs)
  {
    // Don't assign to oneself.
    if (static_cast<const void*>(&rhs) != static_cast<const void*>(this))
      super_type::operator=(rhs);
    return *this;
  }


  template <typename T, typename... Ts>
  template <typename U>
  variant<T, Ts...>::operator U&()
  {
    return std::get<U>(*this);
  }

  template <typename T, typename... Ts>
  template <typename U>
  variant<T, Ts...>::operator const U&() const
  {
    try
    {
      std::get<U>(*this);
    }
    catch(std::bad_variant_access& e)
    {
      std::cout << e.what() << '\n';
    }
    return std::get<U>(*this);
  }

  template <typename T, typename... Ts>
  std::ostream& operator<<(std::ostream& os, const variant<T, Ts...>& obj)
  {
    PrintVisitor pv(os);
    return std::visit(pv, static_cast<const std::variant<T, Ts...>>(obj));
  }

  template <typename T>
  std::ostream& PrintVisitor::operator()(const T& value) const
  {
    return os_ << value;
  }
} // namespace misc
