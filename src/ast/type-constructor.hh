/**
 ** \file ast/type-constructor.hh
 ** \brief Declaration of ast::TypeConstructor.
 */

#pragma once

#include <type/fwd.hh>
#include <ast/fwd.hh>

namespace ast
{


  /** \class ast::TypeConstructor
   ** \brief Create a new type.
   */
  class TypeConstructor
  {
    public:
      TypeConstructor(const type::Type *created_type);
      TypeConstructor() = default;
      ~TypeConstructor();

      void created_type_set(const type::Type *created_type);
      const type::Type *created_type_get() const;

    private:
      const type::Type *created_type_;
  };

} // namespace ast

#include <ast/type-constructor.hxx>
