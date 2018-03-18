/**
 ** \file type/type-checker.hh
 ** \brief Perform type checking and other semantical checks.
 */

#pragma once

#include <cassert>
#include <string>

#include <ast/default-visitor.hh>
#include <ast/non-object-visitor.hh>
#include <misc/error.hh>
#include <misc/set.hh>
#include <type/fwd.hh>

namespace type
{

  class TypeChecker
    : public ast::DefaultVisitor
    , public ast::NonObjectVisitor
  {
  public:
    using super_type = ast::DefaultVisitor;
    using super_type::operator();

    /// Construction.
    TypeChecker();
    /// The error handler.
    const misc::error& error_get() const;

  protected:
    /// Run this visitor on \a e, and return its type.
    ///
    /// Note that it is also guaranteed that \a type_ is set to this type.
    /// More generally, using \a type allows to avoid calling \a accept
    /// directly.
    const Type* type(ast::Typable& e);
    const Record* type(const ast::fields_type& e);
    const Record* type(const ast::VarDecs& e);


    // ------------------ //
    // Helping routines.  //
    // ------------------ //
  protected:
    /// \name Error handling.
    /// \{

    /// Report an error.
    void error(const ast::Ast& ast, const std::string& msg);

    /// Report an error.
    ///
    /// \param ast   the node whose location is used in the error message
    /// \param msg   the error message
    /// \param exp   the culprit.  It must support << output
    template <typename T>
    void error(const ast::Ast& ast, const std::string& msg, const T& exp);

    /// Report an error, and recover from it.
    ///
    /// \param loc   the node whose location is used in the error message
    ///              and whose type is set to nil as an attempt to
    ///              recover.
    /// \param msg   the error message
    /// \param exp   the culprit.  It must support << output
    template <typename T, typename U>
    void error_and_recover(T& loc, const std::string& msg, const U& exp);

    /// Report a type_mismatch between two entities.
    /// \param ast      the guilty node, used to report the location.
    /// \param exp1    the string denoting the first exp.
    /// \param type1   its type
    /// \param exp2    similarly
    /// \param type2   similarly
    void type_mismatch(const ast::Ast& ast,
                       const std::string& exp1, const Type& type1,
                       const std::string& exp2, const Type& type2);
    /// \}


    /// \name Checking types.
    /// \{

    /// \brief Check the type of an Exp.
    ///
    /// \param e  the expression/declaration to check
    /// \param s  the string to refer to \a e in error messages
    ///           (e.g., "index", "left operand" etc.).
    /// \param t  the expected type
    ///
    /// On failure, report the error, and set the type of \a e to \a t.
    /// This should be used for `ast::Exp` and `ast::Dec` nodes.
    template <typename NodeType>
    void check_type(NodeType& e, const std::string& s, const Type& t);

    /** \brief Check the type compatibility.
     **
     ** An error message is output if types are incompatible.
     **
     ** \param loc      a node which location is used to report errors
     ** \param exp1     the syntactic category of the first entity,
     **                 (used in error messages)
     ** \param type1    the first type
     ** \param exp2     same as above
     ** \param type2    same as above
     **/
    void check_types(const ast::Ast& loc,
                     const std::string& exp1, const Type& type1,
                     const std::string& exp2, const Type& type2);
    void check_types(const ast::Ast& loc,
                     const std::string& exp1, ast::Typable& type1,
                     const std::string& exp2, ast::Typable& type2);
    /// \}

  protected:
    /// \name Setting types.
    /// \{

    /// Set the type of a node, if it isn't already set
    /// (an existing type won't be overwritten).
    ///
    /// \param e     the bound node
    /// \param type  the type
    template <typename NodeType>
    void type_default(NodeType& e, const type::Type* type);

    /// Same as type_default, but for a created type.
    template <typename NodeType>
    void created_type_default(NodeType& e, const type::Type* type);

    /// Set the type of a node (overwriting allowed).
    ///
    /// \param e     the bound node
    /// \param type  the type
    template <typename NodeType>
    void type_set(NodeType& e, const type::Type* type);
    /// \}

    // ------------------------- //
    // The core of the visitor.  //
    // ------------------------- //

    // ---------------- //
    // Visiting /Var/.  //
    // ---------------- //

    void operator()(ast::SimpleVar& e) override;
#warning // FIXME: Some code was deleted here (Other Var nodes).


    // ---------------- //
    // Visiting /Exp/.  //
    // ---------------- //

    // Literals.
    void operator()(ast::NilExp&) override;
    void operator()(ast::IntExp&) override;
    void operator()(ast::StringExp&) override;

    // Complex values.
    void operator()(ast::RecordExp& e) override;
    void operator()(ast::OpExp& e) override;
#warning // FIXME: Some code was deleted here (Other Exp nodes).

    // ---------------- //
    // Visiting /Dec/.  //
    // ---------------- //

    /// \name Type and Function declarations.
    /// \{

    /// Be sure to read the documentation of
    /// bind::Binder::decs_visit.
    ///
    /// When type-checking a function (or a type) we need two
    /// traversals: one to register the function's type (to enable
    /// mutual recursions) and a second one to check the bodies.

    /// This is why there are actually three methods: decs_visit,
    /// visit_dec_header, and visit_dec_body.  It turns out that
    /// decs_visit can be written for both functions and types, but of
    /// course, traversals of headers and bodies differ.

    /// Check a set of definitions: unique names, browse headers, then
    /// bodies.
    template <class D>
    void decs_visit(ast::AnyDecs<D>& e);

    /// Check a Function or Type declaration header.
    template <class D>
    void visit_dec_header(D& e);

    /// Check a Function or Type declaration body.
    template <class D>
    void visit_dec_body(D& e);

    /// Generic type-checking of a routine's body.
    template <typename Routine_Type, typename Routine_Node>
    void visit_routine_body(Routine_Node& e);

    /// Visit a chunk of function declarations.
    void operator()(ast::FunctionDecs& e) override;
    /// No longer used.
    void operator()(ast::FunctionDec&) override;

    /// Visit a chunk of type declarations.
    void operator()(ast::TypeDecs& e) override;
    /// No longer used.
    void operator()(ast::TypeDec&) override;
    /// \}

    /// Visit a single Variable Declaration.
    void operator()(ast::VarDec& e) override;

    // --------------- //
    // Visiting /Ty/.  //
    // --------------- //

    void operator()(ast::NameTy& e) override;
    void operator()(ast::RecordTy& e) override;
    void operator()(ast::ArrayTy& e) override;

  protected:
    /// Error handler.
    misc::error error_;
    /// Set of for index variable definitions, which are read only.
    misc::set<const ast::VarDec*> var_read_only_;
  };

  /// Visit the lhs of an ast::FunctionDec.
  template <>
  void TypeChecker::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e);
  /// Visit the rhs of an ast::FunctionDec.
  template <>
  void TypeChecker::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e);

  /// Visit the lhs of an ast::TypeDec.
  template <>
  void TypeChecker::visit_dec_header<ast::TypeDec>(ast::TypeDec& e);
  /// Visit the rhs of an ast::TypeDec.
  template <>
  void TypeChecker::visit_dec_body<ast::TypeDec>(ast::TypeDec& e);

} // namespace type

#include <type/type-checker.hxx>
