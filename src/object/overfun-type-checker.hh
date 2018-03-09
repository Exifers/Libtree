/**
 ** \file object/overfun-type-checker.hh
 ** \brief Checking an ObjectTiger program in a Tiger program.
 */

#pragma once

#include <object/type-checker.hh>
#include <overload/binder.hh>
#include <overload/type-checker.hh>
#include <type/class.hh>
#include <type/types.hh>

namespace object
{

  /// Perform type checking, allowing objects, and compute
  /// the bindings of the object's methods and fields.
  class OverfunTypeChecker
    : public overload::TypeChecker
    , public object::TypeChecker
  {
  // FIXME: Some code was deleted here.
  };

} // namespace type
