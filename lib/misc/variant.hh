/**
 ** \file misc/variant.hh
 ** \brief Interface of misc::variant.
 **
 ** misc::variant is a wrapper over boost::variant that adds
 ** conversion operators to the original Boost variant class.
 ** misc::variant is used just like boost::variant, and you
 ** won't be disturbed when using it.
 **/

#pragma once

#include <variant>

namespace misc
{

  /// A wrapper over std::variant supporting conversion operators.
  ///
  /// Preconditions:
  /// - Each type must be unique.
  /// - No type may be const-qualified.
  ///
  /// Proper declaration form:
  ///   misc::variant<T, T1, ..., Tn>

  template <typename T, typename... Ts>
  class variant :
    public std::variant<T, Ts...>
  {
    static_assert(std::is_default_constructible<T>::value,
                  "the first parameter type of the variant must be"
                  " default-constructible");

  public:
    /// The type of this variant.
    using self_type = variant<T, Ts...>;
    /// Super type.

    using super_type = std::variant<T, Ts...>;

    /// Constructors.
    /// \{
    variant() = default;
    template <typename U> variant(const U& rhs);
    /// \}

    template <typename U> self_type& operator=(const U&);

    /// \brief Convert this variant to a value of type \a U.
    ///
    /// This conversion relies on std::get.  In particular, if the
    /// conversion fails, a std::bad_variant_access exception is thrown.
    template <typename U> operator U&();

    /// Likewise, const version.
    template <typename U> operator const U&() const;
  };

  // Here add variadic template recursion on std::get
  template <typename T, typename... Ts>
  std::ostream& operator<<(std::ostream& os, const variant<T, Ts...>& obj);

  class PrintVisitor
  {
    public:
      PrintVisitor(std::ostream& os) : os_(os)
      {}

      template <typename T>
      std::ostream& operator()(const T& value) const;

    private:
      std::ostream& os_;
    };
} // namespace misc

#include <misc/variant.hxx>
