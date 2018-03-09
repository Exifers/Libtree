/**
 ** \file type/pretty-printer.cc
 ** \brief Implementation for type/pretty-printer.hh.
 */

#include <type/libtype.hh>
#include <type/pretty-printer.hh>
#include <type/type.hh>
#include <type/types.hh>

namespace type
{

  namespace
  {

    template <typename Type>
    std::ostream& print_type(std::ostream& ostr, const Type& type)
    {
      PrettyPrinter printer{ostr};
      printer(type);
      return ostr;
    }

    /// How many times did we go through operator()(const Named&)?
    inline long int& indent(std::ostream& o)
    {
      // The slot to store the current indentation level.
      static const long int indent_index = std::ios::xalloc();
      return o.iword(indent_index);
    }

  }

  std::ostream&
  operator<<(std::ostream& ostr, const Attribute& e)
  {
    return print_type(ostr, e);
  }

  std::ostream&
  operator<<(std::ostream& ostr, const Field& e)
  {
    return print_type(ostr, e);
  }

  std::ostream&
  operator<<(std::ostream& ostr, const Type& e)
  {
    return print_type(ostr, e);
  }


  PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : ostr_{ostr}
  {}

  void
  PrettyPrinter::operator()(const Nil& e)
  {
    ostr_ << "nil = ";
    if (auto record_type = e.record_type_get())
      ostr_ << *record_type;
    else
      ostr_ << "(null)";
  }

  void
  PrettyPrinter::operator()(const Void&)
  {
    ostr_ << "void";
  }

  void
  PrettyPrinter::operator()(const Int&)
  {
  // FIXME: Some code was deleted here.
  }

  void
  PrettyPrinter::operator()(const String&)
  {
  // FIXME: Some code was deleted here.
  }

  void
  PrettyPrinter::operator()(const Named& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  PrettyPrinter::operator()(const Array& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  PrettyPrinter::operator()(const Record& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  PrettyPrinter::operator()(const Class& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  PrettyPrinter::operator()(const Function& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  PrettyPrinter::operator()(const Attribute& e)
  {
    ostr_ << e.name_get() << " : " << e.type_get();
  }

  void
  PrettyPrinter::operator()(const Field& e)
  {
    ostr_ << e.name_get() << " : " << e.type_get();
  }

} // namespace type
