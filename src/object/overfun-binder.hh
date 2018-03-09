/**
 ** \file object/overfun-binder.hh
 ** \brief Declaration of object::OverfunBinder.
 **/

#pragma once

#include <object/binder.hh>
#include <overload/binder.hh>

namespace object
{

  /// \brief Compute bindings with support for objects and overload.
  class OverfunBinder : public Binder, public overload::Binder
  {
  // FIXME: Some code was deleted here.
  };

} // namespace object
