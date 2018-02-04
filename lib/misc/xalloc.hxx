/**
 ** \file misc/xalloc.hxx
 ** \brief Implementation for misc/xalloc.hh.
 */

#pragma once

#include <utility>

#include <misc/xalloc.hh>

namespace misc
{

  /*----------------.
  | iomanipulator.  |
  `----------------*/

  inline std::ostream&
  operator<<(std::ostream& o, const iomanipulator& g)
  {
    g(o);
    return o;
  }


  /*---------------------.
  | xalloc<StoredType>.  |
  `---------------------*/

  template <class StoredType>
  template <typename... Args>
  xalloc<StoredType>::xalloc(Args&&... args)
    : index_(std::ios::xalloc())
    , model_{std::forward<Args>(args)...}
  {}

  template <class StoredType>
  long int
  xalloc<StoredType>::index() const
  {
    return index_;
  }

  template <class StoredType>
  StoredType&
  xalloc<StoredType>::operator()(std::ostream& ostr) const
  {
    void*& storage_ptr = ostr.pword(index_);

    if (!storage_ptr)
      {
        storage_ptr = new StoredType{model_};
        ostr.register_callback(xalloc::deallocate, index_);
      }

    return *static_cast<StoredType*>(storage_ptr);
  }

  template <class StoredType>
  void
  xalloc<StoredType>::deallocate(std::ios_base::event type,
                                 std::ios_base& ios,
                                 int index)
  {
    if (type == std::ios_base::erase_event)
      {
        StoredType* ptr = static_cast<StoredType*>(ios.pword(index));
        delete ptr;
      }
  }


  /*-----------.
  | set_type.  |
  `-----------*/

  template <class StoredType>
  xalloc<StoredType>::set_type::set_type(const xalloc& slot, StoredType& data)
    : slot_(slot), data_(data)
  {}

  template <class StoredType>
  void
  xalloc<StoredType>::set_type::operator()(std::ostream& ostr) const
  {
    slot_(ostr) = data_;
  }

  template <class StoredType>
  typename xalloc<StoredType>::set_type
  xalloc<StoredType>::set(StoredType& data) const
  {
    return set_type(*this, data);
  }


  /*-----------.
  | get_type.  |
  `-----------*/

  template <class StoredType>
  xalloc<StoredType>::get_type::get_type(const xalloc& slot, StoredType& data)
    : slot_(slot), data_(data)
  {}

  template <class StoredType>
  void
  xalloc<StoredType>::get_type::operator()(std::ostream& ostr) const
  {
    data_ = slot_(ostr);
  }

  template <class StoredType>
  typename xalloc<StoredType>::get_type
  xalloc<StoredType>::get(StoredType& data) const
  {
    return get_type(*this, data);
  }


  /*------------.
  | swap_type.  |
  `------------*/

  template <class StoredType>
  xalloc<StoredType>::swap_type::swap_type(const xalloc& slot, StoredType& data)
    : slot_(slot), data_(data)
  {}

  template <class StoredType>
  void
  xalloc<StoredType>::swap_type::operator()(std::ostream& ostr) const
  {
    std::swap(slot_(ostr), data_);
  }

  template <class StoredType>
  typename xalloc<StoredType>::swap_type
  xalloc<StoredType>::swap(StoredType& data) const
  {
    return swap_type(*this, data);
  }

} // namespace misc
