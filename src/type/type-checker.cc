/**
 ** \file type/type-checker.cc
 ** \brief Implementation for type/type-checker.hh.
 */

#include <memory>

#include <ast/all.hh>
#include <type/type-checker.hh>
#include <type/types.hh>

namespace type
{

  namespace
  {

    // Try to cast the type into a nil type.
    // If it's not actually a `type::Nil`, return `nullptr`.
    // This allows us to write more clear code like:
    // if (auto nil = to_nil(e.type_get())
    // ...
    const Nil* to_nil(const Type& type)
    {
      return dynamic_cast<const Nil*>(&type.actual());
    }

  }

  TypeChecker::TypeChecker()
    : super_type()
    , error_()
  {}

  const Type*
  TypeChecker::type(ast::Typable& e)
  {
  // FIXME: Some code was deleted here.
  }

  const Record*
  TypeChecker::type(const ast::fields_type& e)
  {
    auto res = new Record;
  // FIXME: Some code was deleted here.
    return res;
  }

  const Record*
  TypeChecker::type(const ast::VarDecs& e)
  {
    auto res = new Record;
    for (const auto& i : e.decs_get())
      res->field_add(i->name_get(), *type(*i));

    return res;
  }

  const misc::error&
  TypeChecker::error_get() const
  {
    return error_;
  }


  /*-----------------.
  | Error handling.  |
  `-----------------*/

  void
  TypeChecker::error(const ast::Ast& ast, const std::string& msg)
  {
    error_ << misc::error::error_type::type
           << ast.location_get() << ": " << msg << std::endl;
  }

  void
  TypeChecker::type_mismatch(const ast::Ast& ast,
                             const std::string& exp1, const Type& type1,
                             const std::string& exp2, const Type& type2)
  {
    error_ << misc::error::error_type::type
           << ast.location_get() << ": type mismatch" << misc::incendl
           << exp1 << " type: " << type1 << misc::iendl
           << exp2 << " type: " << type2 << misc::decendl;
  }

  void
  TypeChecker::check_types(const ast::Ast& ast,
                           const std::string& exp1, const Type& type1,
                           const std::string& exp2, const Type& type2)
  {
  // FIXME: Some code was deleted here.
  }


  void
  TypeChecker::check_types(const ast::Ast& ast,
                           const std::string& exp1, ast::Typable& type1,
                           const std::string& exp2, ast::Typable& type2)
  {
    // Ensure evaluation order.
    type(type1);
    type(type2);
  // FIXME: Some code was deleted here (Check types).
  }


  /*--------------------------.
  | The core of the visitor.  |
  `--------------------------*/

  /*-----------------.
  | Visiting /Var/.  |
  `-----------------*/

  void
  TypeChecker::operator()(ast::SimpleVar& e)
  {
  // FIXME: Some code was deleted here.
  }

  // FIXME: Some code was deleted here.


  /*-----------------.
  | Visiting /Exp/.  |
  `-----------------*/

  // Literals.
  void
  TypeChecker::operator()(ast::NilExp& e)
  {
    auto nil_ptr = std::make_unique<Nil>();
    type_default(e, nil_ptr.get());
    created_type_default(e, nil_ptr.release());
  }

  void
  TypeChecker::operator()(ast::IntExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  TypeChecker::operator()(ast::StringExp& e)
  {
  // FIXME: Some code was deleted here.
  }


  // Complex values.

  void
  TypeChecker::operator()(ast::RecordExp& e)
  {
    // If no error occured, check for nil types in the record initialization.
    // If any error occured, there's no need to set any nil types.
    // If there are any record initializations, set the `record_type_`
    // of the `Nil` to the expected type.
  // FIXME: Some code was deleted here.
  }

  void
  TypeChecker::operator()(ast::OpExp& e)
  {
  // FIXME: Some code was deleted here.

    // If any of the operands are of type Nil, set the `record_type_` to the
    // type of the opposite operand.
    if (!error_)
      {
  // FIXME: Some code was deleted here.
      }
  }

  // FIXME: Some code was deleted here.


  /*-----------------.
  | Visiting /Dec/.  |
  `-----------------*/

  /*------------------------.
  | Visiting FunctionDecs.  |
  `------------------------*/

  void
  TypeChecker::operator()(ast::FunctionDecs& e)
  {
    decs_visit<ast::FunctionDec>(e);
  }


  void
  TypeChecker::operator()(ast::FunctionDec&)
  {
    // We must not be here.
    unreachable();
  }


  // Store the type of this function.
  template <>
  void
  TypeChecker::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e)
  {
  // FIXME: Some code was deleted here.
  }


  // Type check this function's body.
  template <>
  void
  TypeChecker::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e)
  {
    if (e.body_get())
      {
        visit_routine_body<Function>(e);

        // Check for Nil types in the function body.
        if (!error_)
          {
  // FIXME: Some code was deleted here.
          }
      }
  }


  /*---------------.
  | Visit VarDec.  |
  `---------------*/

  void
  TypeChecker::operator()(ast::VarDec& e)
  {
  // FIXME: Some code was deleted here.
  }


  /*--------------------.
  | Visiting TypeDecs.  |
  `--------------------*/

  void
  TypeChecker::operator()(ast::TypeDecs& e)
  {
    decs_visit<ast::TypeDec>(e);
  }


  void
  TypeChecker::operator()(ast::TypeDec&)
  {
    // We must not be here.
    unreachable();
  }


  // Store this type.
  template <>
  void
  TypeChecker::visit_dec_header<ast::TypeDec>(ast::TypeDec& e)
  {
    // We only process the head of the type declaration, to set its
    // name in E.  A declaration has no type in itself; here we store
    // the type declared by E.
  // FIXME: Some code was deleted here.
  }

  // Bind the type body to its name.
  template <>
  void
  TypeChecker::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
  {
  // FIXME: Some code was deleted here.
  }

  /*------------------.
  | Visiting /Decs/.  |
  `------------------*/

  template <class D>
  void
  TypeChecker::decs_visit(ast::AnyDecs<D>& e)
  {
  // FIXME: Some code was deleted here.
  }


  /*-------------.
  | Visit /Ty/.  |
  `-------------*/

  void
  TypeChecker::operator()(ast::NameTy& e)
  {
  // FIXME: Some code was deleted here (Recognize user defined types, and built-in types).
  }

  void
  TypeChecker::operator()(ast::RecordTy& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  TypeChecker::operator()(ast::ArrayTy& e)
  {
  // FIXME: Some code was deleted here.
  }

} // namespace type
