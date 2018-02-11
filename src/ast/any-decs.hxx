/**
 ** \file ast/any-decs.hxx
 ** \brief Implementation of ast::AnyDecs.
 */

#pragma once

#include <ast/visitor.hh>
#include <ast/any-decs.hh>

namespace ast
{

  template <typename D>
  AnyDecs<D>::AnyDecs(const Location& location, Ds* decs) :
    Decs(location),
    decs_(decs)
  {}

  template <typename D>
  AnyDecs<D>::AnyDecs(const Location& location) :
    Decs(location)
  {}

  template <typename D>
  AnyDecs<D>::~AnyDecs()
  {
    for (typename Ds::iterator i = decs_->begin(); i != decs_->end(); ++i)
      delete *i;
    delete decs_;
  }

  template <typename D>
  inline void
  AnyDecs<D>::accept(Visitor& v)
  {
    v(*this);
  }

  template <typename D>
  inline void
  AnyDecs<D>::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  template <typename D>
  AnyDecs<D>&
  AnyDecs<D>::push_front(D& d)
  {
    location_set(location_get() + d.location_get());
    decs_->insert(decs_->begin(), &d);
    return *this;
  }

  template <typename D>
  AnyDecs<D>&
  AnyDecs<D>::emplace_back(D& d)
  {
    location_set(location_get() + d.location_get());
    decs_->emplace_back(&d);
    return *this;
  }

  template <typename D>
  inline typename AnyDecs<D>::Ds&
  AnyDecs<D>::decs_get()
  {
    return *decs_;
  }

  template <typename D>
  inline const typename AnyDecs<D>::Ds&
  AnyDecs<D>::decs_get() const
  {
    return *decs_;
  }

} // namespace ast
