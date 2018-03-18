/**
 ** \file type/class.cc
 ** \brief Implementation for type/class.hh.
 */

#include <iostream>
#include <ostream>

#include <misc/indent.hh>
#include <type/class.hh>
#include <type/visitor.hh>

namespace type
{

  Class::Class(const Class* super)
    : Type()
    , id_(fresh_id())
    , super_(super)
    , subclasses_()
  {}

  void
  Class::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  Class::accept(Visitor& v)
  {
    v(*this);
  }

  const Type*
  Class::attr_type(const misc::symbol& key) const
  {
#warning // FIXME: Some code was deleted here.
  }

  const Type*
  Class::meth_type(const misc::symbol& key) const
  {
#warning // FIXME: Some code was deleted here.
  }

#warning // FIXME: Some code was deleted here (Find common super class).

#warning // FIXME: Some code was deleted here (Super class soundness test).

#warning // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Class).

  const Class&
  Class::object_instance()
  {
#warning // FIXME: Some code was deleted here.
  }

  unsigned Class::fresh_id()
  {
    static unsigned counter_ = 0;
    return counter_++;
  }

} // namespace type
