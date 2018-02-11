/**
 ** \file ast/pretty-printer.hh
 ** \brief Declaration of ast::PrettyPrinter.
 */

#pragma once

#include <ast/default-visitor.hh>
#include <ast/object-visitor.hh>

namespace ast
{

  /// Visit an Ast and print the content of each node.
  class PrettyPrinter
    : virtual public DefaultConstVisitor
    , virtual public ObjectConstVisitor
  {
  public:
    using super_type = DefaultConstVisitor;
    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build to print on \a ostr.
    PrettyPrinter(std::ostream& ostr);

    /// Visit methods.
    /// \{
    void operator()(const SimpleVar& e) override;
    void operator()(const FieldVar& e) override;
    void operator()(const SubscriptVar& e) override;
    void operator()(const CastVar& e) override;
    void operator()(const CastExp& e) override;
    /// \}

  private:
    // Factor pretty-printing of RecordExp and RecordTy.
    template <typename RecordClass>
    void print_record(const RecordClass& e);


  protected:
    /// The stream to print on.
    std::ostream& ostr_;
  };


} // namespace ast
