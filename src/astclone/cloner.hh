/**
 ** \file astclone/cloner.hh
 ** \brief Declaration of astclone::Cloner.
 */

#pragma once

#include <ast/default-visitor.hh>

namespace astclone
{

  /// \brief Duplicate an Ast.
  class Cloner : public ast::DefaultConstVisitor
  {
  public:
    using super_type = ast::DefaultConstVisitor;

    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build a Cloner.
    Cloner();

    /// Destroy a Cloner.
    virtual ~Cloner() = default;

    // Return the cloned Ast.
    ast::Ast* result_get();

    template <typename T>
    T* recurse(const T& t);

    template <typename T>
    T* recurse(const T* const t);

    /** \brief Clone a collection object.

        Using overloading for this method is tempting, but it would
        lead to the same prototype than the first \a recurse method.

        A partial specialization for \a std::list<T> would work, but is
        not allowed by C++ standard. As a consequence, we are stuck to
        using different names.
     */
    template <typename CollectionType>
    CollectionType* recurse_collection(const CollectionType& c);


    // Visit methods.
  public:
    void operator()(const ast::ArrayExp&) override;
    void operator()(const ast::ArrayTy&) override;
    void operator()(const ast::AssignExp&) override;
    void operator()(const ast::BreakExp&) override;
    void operator()(const ast::CallExp&) override;
    void operator()(const ast::CastExp&) override;
    void operator()(const ast::CastVar&) override;
    void operator()(const ast::ClassTy&) override;
    void operator()(const ast::DecsList&) override;
    void operator()(const ast::Field&) override;
    void operator()(const ast::FieldInit&) override;
    void operator()(const ast::FieldVar&) override;
    void operator()(const ast::ForExp&) override;
    void operator()(const ast::FunctionDec&) override;
    void operator()(const ast::IfExp&) override;
    void operator()(const ast::IntExp&) override;
    void operator()(const ast::LetExp&) override;
    void operator()(const ast::MethodCallExp&) override;
    void operator()(const ast::MethodDec&) override;
    void operator()(const ast::NameTy&) override;
    void operator()(const ast::NilExp&) override;
    void operator()(const ast::ObjectExp&) override;
    void operator()(const ast::OpExp&) override;
    void operator()(const ast::RecordExp&) override;
    void operator()(const ast::RecordTy&) override;
    void operator()(const ast::SeqExp&) override;
    void operator()(const ast::SimpleVar&) override;
    void operator()(const ast::StringExp&) override;
    void operator()(const ast::SubscriptVar&) override;
    void operator()(const ast::TypeDec&) override;
    void operator()(const ast::VarDec&) override;
    void operator()(const ast::WhileExp&) override;

    template <typename DecsType>
    /** \brief Visit a chunk (i.e., a list of Function, Var, and Type decs).
     **
     ** It is exactly the same in the three cases, so the code is
     ** factored via a template method. */
    void decs_visit(const DecsType& e);

    // As we can't mix template and virtual methods, we have to
    // duplicate these methods.  That's too bad.  :(
    void operator()(const ast::FunctionDecs&) override;
    void operator()(const ast::MethodDecs&) override;
    void operator()(const ast::TypeDecs&) override;
    void operator()(const ast::VarDecs&) override;

  protected:
    /// The cloned Ast.
    ast::Ast* result_;
  };

} // namespace ast

#include <astclone/cloner.hxx>
