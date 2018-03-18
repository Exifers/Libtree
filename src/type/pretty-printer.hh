/**
 ** \file type/pretty-printer.hh
 ** \brief Print the type hierarchy.
 */

#pragma once

#include <ostream>

#include <type/default-visitor.hh>
#include <type/fwd.hh>

namespace type
{

  class PrettyPrinter : public DefaultConstVisitor
  {
  public:
    /// Super class type.
    using super_type = DefaultConstVisitor;

    // Import overloaded \c operator() methods.
    using super_type::operator();

    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a pretty printer.
    PrettyPrinter(std::ostream& ostr);
    /** \} */

    /** \name Visit basic types.
     ** \{ */
    void operator()(const Nil& e) override;
    void operator()(const Void& e) override;
    void operator()(const Int& e) override;
    void operator()(const String& e) override;
    /** \} */


    /** \name Visit composed types.
     ** \{ */
    void operator()(const Named& e) override;
    void operator()(const Array& e) override;
    void operator()(const Record& e) override;
    void operator()(const Class& e) override;
    void operator()(const Function& e) override;
    /** \} */

    /** \name Visit Non type types.
     ** \{ */
    void operator()(const Attribute& e);
    void operator()(const Field& e);
    /** \} */

  private:
    /// The stream to print on.
    std::ostream& ostr_;
  };

  /// Overload redirection operator for Type.
  std::ostream& operator<<(std::ostream& ostr, const Type& t);

  /// Overload redirection operator for Attribute.
  std::ostream& operator<<(std::ostream& ostr, const Attribute& obj);

  /// Overload redirection operator for Field.
  std::ostream& operator<<(std::ostream& ostr, const Field& obj);

} // namespace type
