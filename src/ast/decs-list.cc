/**
 ** \file ast/decs-list.cc
 ** \brief Implementation of ast::DecsList.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/decs-list.hh>
#include <ast/decs.hh>

namespace ast
{

  void
  DecsList::push_front(Decs* d)
  {
    decs_.emplace_front(d);
    location_.begin = d->location_get().begin;
  }

  void
  DecsList::emplace_back(Decs* d)
  {
    decs_.emplace_back(d);
    location_.end = d->location_get().end;
  }

  void
  DecsList::splice_front(DecsList& ds)
  {
    decs_.splice(decs_.begin(), ds.decs_get());
  }

  void
  DecsList::splice_back(DecsList& ds)
  {
    decs_.splice(decs_.end(), ds.decs_get());
  }

  DecsList::DecsList(const Location& location)
    : Ast(location)
  {}

  DecsList::DecsList(const Location& location,
                     const DecsList::decs_type& decs)
    : Ast(location)
    , decs_(decs)
  {}

  DecsList::~DecsList()
  {
    misc::deep_clear(decs_);
  }

  void
  DecsList::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  DecsList::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

