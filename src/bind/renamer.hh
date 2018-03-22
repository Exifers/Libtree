/**
 ** \file bind/renamer.hh
 ** \brief Implementation of bind::Renamer.
 */

#pragma once

#include <map>

#include <ast/default-visitor.hh>
#include <ast/non-object-visitor.hh>

namespace bind
{

  /// Perform identifier renaming within an AST (in place),
  /// without support for objects.
  class Renamer : public ast::DefaultVisitor, public ast::NonObjectVisitor
  {
  public:
    using super_type = ast::DefaultVisitor;

    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build a Renamer.
    Renamer();

    /// \name Auxiliary routines.
    /// \{
    /// \brief Compute the name for this kind of declaration.
    ///
    /// Take into account the fact that _main and primitive are
    /// not to be renamed.
    template <typename Def>
    misc::symbol new_name_compute(const Def& e);

    /// \brief Get the new name of this declaration, possibly create it.
    ///
    /// The tricky thing is that when visiting a chunk of definitions,
    /// we might visit a body using a name not yet renamed (e.g., mutually
    /// recursive functions), in which case we must compute the
    /// new name of that function on the fly.
    template <typename Def>
    misc::symbol new_name(const Def& e);
    /// \}

    // Visit methods.
    /// \brief Process a declaration body or a usage site.
    ///
    /// \a def is the definition site of \e (must be equal to
    /// \a e if it is a Dec node).
    template <class E, class Def>
    void visit(E& e, const Def* def);

    /// \name Visiting definition sites.
    /// \{
    void operator()(ast::VarDec& e) override;
    void operator()(ast::FunctionDec& e) override;
    void operator()(ast::TypeDec& e) override;
    /// \}

    /// \name Visiting usage sites.
    /// \{
    void operator()(ast::SimpleVar& e) override;
    void operator()(ast::FieldVar& e) override;
    void operator()(ast::SubscriptVar& e) override;
    void operator()(ast::CastVar& e) override;
    void operator()(ast::NilExp& e) override;
    void operator()(ast::IntExp& e) override;
    void operator()(ast::StringExp& e) override;
    void operator()(ast::CallExp& e) override;
    void operator()(ast::OpExp& e) override;
    void operator()(ast::RecordExp& e) override;
    void operator()(ast::AssignExp& e) override;
    void operator()(ast::IfExp& e) override;
    void operator()(ast::WhileExp& e) override;
    void operator()(ast::ForExp& e) override;
    void operator()(ast::BreakExp&) override;
    void operator()(ast::ArrayExp& e) override;
    void operator()(ast::CastExp& e) override;
    void operator()(ast::FieldInit& e) override;
    /// \}

  private:
    /// \name New names.
    /// \{
    /// New names associated to original declared entities.
    using new_names_type = std::map<const ast::Dec*, misc::symbol>;
    /// Dictionary mapping old declarations to their new names.
    new_names_type new_names_;
    /// \}
   
    /// Rename a declaration with a name not used by any other declaration 
    void rename(ast::Dec& e);
  };

} // namespace bind

#include <bind/renamer.hxx>
