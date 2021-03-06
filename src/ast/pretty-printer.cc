/**
 ** \file ast/pretty-printer.cc
 ** \brief Implementation of ast::PrettyPrinter.
 */

#include <misc/escape.hh>
#include <misc/indent.hh>
#include <misc/separator.hh>
#include <misc/pair.hh>
#include <ast/all.hh>
#include <ast/pretty-printer.hh>
#include <ast/libast.hh>

#include <type/class.hh>

namespace ast
{
  extern bool g_bindings_display;

  // Anonymous namespace: these functions are private to this file.
  namespace
  {
    /// Output \a e on \a ostr.
    inline
      std::ostream&
      operator<<(std::ostream& ostr, const Escapable& e)
      {
        if (escapes_display(ostr)
#warning // FIXME: Some code was deleted here.
           )
          ostr << "/* escaping */ ";

        return ostr;
      }

    /// \brief Output \a e on \a ostr.
    ///
    /// Used to factor the output of the name declared,
    /// and its possible additional attributes.
    inline
    std::ostream&
    operator<<(std::ostream& ostr, const Dec& e)
    {
      ostr << e.name_get();
      if (ast::g_bindings_display)
        ostr << " /* " << &e << " */";
      return ostr;
    }
  }



  PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : ostr_(ostr)
  {}


  void
  PrettyPrinter::operator()(const SimpleVar& e)
  {
    ostr_ << e.name_get();
    if (ast::g_bindings_display)
      ostr_ << " /* " << e.def_get() << " */";
  }

  void
  PrettyPrinter::operator()(const FieldVar& e)
  {
    ostr_ << e.var_get() << "." << e.name_get();
  }

/* Foo[10]. */
  void
  PrettyPrinter::operator()(const SubscriptVar& e)
  {
    ostr_ << e.var_get() << '[' << misc::incindent << e.index_get()
      << misc::decindent << ']';
  }

  void
  PrettyPrinter::operator()(const CastVar& e)
  {
    ostr_ << "_cast(" << e.var_get() << ", " << e.ty_get() << ')';
  }

  void
  PrettyPrinter::operator()(const CastExp& e)
  {
    ostr_ << "_cast(" << e.exp_get() << ", " << e.ty_get() << ')';
  }

  void
  PrettyPrinter::operator()(const LetExp& e)
  {
    ostr_ << "let" << misc::iendl;

    for (auto it = e.decs_get().decs_get().begin();
         it != e.decs_get().decs_get().end(); it++)
    {
      ostr_ << **it;
      ostr_ << misc::iendl;
    }

    ostr_ << "in" << misc::iendl;
    auto l = e.exps_get();
    for (auto it = l.begin(); it != l.end(); it++)
    {
      ostr_ << **it;
      auto it_cpy = it;
      if (++it_cpy != l.end())
        ostr_ << ";";
      ostr_ << misc::iendl;
    }
    ostr_ << "end";
  }

  void
  PrettyPrinter::operator()(const NilExp& e)
  {
    ostr_ << "nil";
  }

  void
  PrettyPrinter::operator()(const IntExp& e)
  {
    ostr_ << e.value_get();
  }

  void
  PrettyPrinter::operator()(const StringExp& e)
  {
    ostr_ << "\"" << misc::escape<std::string>(e.value_get()) << "\"";
  }

  void
  PrettyPrinter::operator()(const ArrayExp& e)
  {
    ostr_ << e.namety_get() << "[ " << e.size_exp_get()
      << " ] of " << e.type_exp_get();
  }

  void
  PrettyPrinter::operator()(const RecordExp& e)
  {
    ostr_ << e.namety_get() << "{ ";
    auto l = e.fields_get();
    for (auto it = l.begin(); it != l.end(); it++)
    {
      ostr_ << **it;
      auto it_cpy = it;
      if (++it_cpy != l.end())
        ostr_ << ", ";
      ostr_ << misc::iendl;
    }
    ostr_ << " }";
  }

  void
  PrettyPrinter::operator()(const ObjectExp& e)
  {
    ostr_ << "new " << e.namety_get();
  }

  void
  PrettyPrinter::operator()(const CallExp& e)
  {
    ostr_ << e.name_get();
    if (ast::g_bindings_display)
      ostr_ << " /* " << e.def_get() << " */";
    ostr_ << "( ";
    auto l = e.exps_get();
    for (auto it = l.begin(); it != l.end(); it++)
    {
      ostr_ << **it;
      auto it_cpy = it;
      if (++it_cpy != l.end())
        ostr_ << ", ";
    }
    ostr_ << " )";
  }

  void
  PrettyPrinter::operator()(const MethodCallExp& e)
  {
    ostr_ << e.lvalue_get() << "( ";
    auto l = e.exps_get();
    for (auto it = l.begin(); it != l.end(); it++)
    {
      ostr_ << **it;
      auto it_cpy = it;
      if (++it_cpy != l.end())
        ostr_ << ", ";
    }
    ostr_ << " )";
  }

  void
  PrettyPrinter::operator()(const OpExp& e)
  {
    auto o = e.oper_get();
    ostr_ << e.left_get();
    ostr_ << " ";
    switch( (int) o)
    {
      case (int) OpExp::Oper::add:
        ostr_ << "+";
        break;
      case (int) OpExp::Oper::sub:
        ostr_ << "-";
        break;
      case (int) OpExp::Oper::mul:
        ostr_ << "*";
        break;
      case (int) OpExp::Oper::div:
        ostr_ << "/";
        break;
      case (int) OpExp::Oper::eq:
        ostr_ << "";
        break;
      case (int) OpExp::Oper::ne:
        ostr_ << "<>";
        break;
      case (int) OpExp::Oper::lt:
        ostr_ << "<";
        break;
      case (int) OpExp::Oper::le:
        ostr_ << "<=";
        break;
      case (int) OpExp::Oper::gt:
        ostr_ << ">";
        break;
      case (int) OpExp::Oper::ge:
        ostr_ << ">=";
        break;
      default:
        break;
    }
    ostr_ << " " << e.right_get();
  }

  void
  PrettyPrinter::operator()(const SeqExp& e)
  {
    ostr_ << "( ";
    auto l = e.exps_get();
    for (auto it = l.begin(); it != l.end(); it++)
    {
      ostr_ << **it;
      auto it_cpy = it;
      if (++it_cpy != l.end())
        ostr_ << ";" << misc::iendl;
    }
    ostr_ << " )";
  }

  void
  PrettyPrinter::operator()(const AssignExp& e)
  {
    ostr_ << e.lvalue_get() << " := " << e.exp_get();
  }

  void
  PrettyPrinter::operator()(const IfExp& e)
  {
    ostr_ <<  "if " << e.condition_get() << " then " << misc::iendl
      << e.content_get();
    try
    {
      const Exp& else_content = e.else_content_get();
      ostr_ << " else " << else_content;
    }
    catch(...)
    {}
  }

  void
  PrettyPrinter::operator()(const WhileExp& e)
  {
    ostr_ << "while ";
    if (ast::g_bindings_display)
      ostr_ << "/* " << &e << " */";
    ostr_ << e.test_get() << " do " << misc::iendl
      << e.body_get();
  }

  void
  PrettyPrinter::operator()(const ForExp& e)
  {
    ostr_ << "for ";
    if (ast::g_bindings_display)
      ostr_ << "/* " << &e << " */";
    ostr_ << e.vardec_get().name_get() << " := "
      << *e.vardec_get().init_get()
      << " to " << e.hi_get() << " do "
      << e.body_get();
  }

  void
  PrettyPrinter::operator()(const BreakExp& e)
  {
    ostr_ << "break";
    if (ast::g_bindings_display)
      ostr_ << " /* " << &e.loop_get() << " */";
  }

  void
  PrettyPrinter::operator()(const TypeDec& e)
  {
    ostr_ << "type " << e.name_get();
    if (ast::g_bindings_display)
      ostr_ << " /* " << &e << " */";
    ostr_ << " = " << e.ty_get();
  }

  void
  PrettyPrinter::operator()(const FunctionDec& e)
  {
    auto result = e.result_get();
    auto body = e.body_get();
    if (result == nullptr && body == nullptr)
    {
      ostr_ << "primitive " << e.name_get();
      if (ast::g_bindings_display)
        ostr_ << " /* " << &e << " */ ";
      ostr_  << " (" << e.formals_get() << ")";
    }
    else if (result == nullptr)
    {
      ostr_ << "function " << e.name_get();
      if (ast::g_bindings_display)
        ostr_ << " /* " << &e << " */ ";
      ostr_ << " (" << e.formals_get() << ") "
        << " = " << *body;
    }
    else if (body == nullptr)
    {
      ostr_ << "primitive " << e.name_get();
      if (ast::g_bindings_display)
        ostr_ << " /* " << &e << " */ ";
      ostr_ << " (" << e.formals_get() << ") "
        << ": " << *result;
    }
    else
    {
      ostr_ << "function " << e.name_get();
      if (ast::g_bindings_display)
        ostr_ << " /* " << &e << " */ ";
      ostr_ << " (" << e.formals_get() << ") "
        << ": " << *result << " = " << *body;
    }
  }

  void
  PrettyPrinter::operator()(const MethodDec& e)
  {
    ostr_ << "method " << e.name_get() << " (";

    auto v = e.formals_get().decs_get();
    for (auto it = v.begin(); it != v.end(); it++)
    {
      ostr_ << (**it).name_get() << " : " << *(**it).type_name_get();
      auto it_cpy = it;
      if (++it_cpy != v.end())
        ostr_ << ", ";
    }
    ostr_ << ") ";

    if (e.result_get() != nullptr)
    {
      ostr_ << " : " << *(e.result_get()) << " ";
    }
    ostr_ << "= " << *(e.body_get());
  }

  void
  PrettyPrinter::operator()(const ArrayTy& e)
  {
    ostr_ << "array of " << e.base_type_get();
  }

  void
  PrettyPrinter::operator()(const ClassTy& e)
  {
    ostr_ << "class ";
    try
    {
      ostr_ << "extends " << e.super_get();
    }
    catch(...)
    {}
    ostr_ << " {" << e.decs_get() << "} ";
  }

  void
  PrettyPrinter::operator()(const NameTy& e)
  {
    ostr_ << e.name_get();
  }

  void
  PrettyPrinter::operator()(const RecordTy& e)
  {
    ostr_ << "{ ";
    auto l = e.tyfields_get();
    for (auto it = l.begin(); it != l.end(); it++)
    {
      ostr_ << **it;
      auto it_cpy = it;
      if (++it_cpy != l.end())
        ostr_ << ", ";
    }
    ostr_ << " }";
  }

  void
  PrettyPrinter::operator()(const FieldInit& e)
  {
    ostr_ << e.name_get() << " = " << e.init_get();
  }

  void
  PrettyPrinter::operator()(const Field& e)
  {
    ostr_ << e.name_get() << " : " << e.type_name_get();
  }

  void
  PrettyPrinter::operator()(const VarDecs& e)
  {
    auto v = e.decs_get();
    for (auto it = v.begin(); it != v.end(); it++)
    {
      if ((**it).init_get() != nullptr)
        ostr_ << "var ";

      ostr_ << (const Dec&) (**it);

      if ((**it).type_name_get() != nullptr)
      {
        ostr_ << " : " << *((**it).type_name_get());
        if (ast::g_bindings_display)
          ostr_ << " /* " << (**it).def_get() << " */ ";
      }

      if ((**it).init_get() != nullptr)
        ostr_ << " := " << *((**it).init_get());

      auto it_cpy = it;
      if (++it_cpy != v.end())
        ostr_ << ", ";
    }
  }

  void
  PrettyPrinter::operator()(const MethodDecs& e)
  {
    auto v = e.decs_get();
    for (auto it = v.begin(); it != v.end(); it++)
    {
      operator()(**it);
      ostr_ << misc::iendl;
    }
  }

  void
  PrettyPrinter::operator()(const FunctionDecs& e)
  {
    auto v = e.decs_get();
    for (auto it = v.begin(); it != v.end(); it++)
    {
      operator()(**it);
      auto it_cpy = it;
      if (++it_cpy != v.end())
        ostr_ << misc::iendl;
    }
  }

  void
  PrettyPrinter::operator()(const TypeDecs& e)
  {
    auto v = e.decs_get();
    for (auto it = v.begin(); it != v.end(); it++)
    {
      operator()(**it);
      auto it_cpy = it;
      if (++it_cpy != v.end())
        ostr_ << misc::iendl;
    }
  }

} // namespace ast
