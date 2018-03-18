/**
 ** \file type/fwd.hh
 ** \brief Forward declarations for the type module.
 */

#pragma once

#include <misc/fwd.hh>

namespace type
{

  class Array;
  class Attribute;
  class Class;
  class Field;
  class Function;
  class Int;
  class Method;
  class Named;
  class Nil;
  class Record;
  class String;
  class Type;
  class Void;

  // From visitor.hh
  template <template <typename> class Const>
  class GenVisitor;
  using ConstVisitor = GenVisitor<misc::constify_traits>;
  using Visitor = GenVisitor<misc::id_traits>;

} // namespace type
