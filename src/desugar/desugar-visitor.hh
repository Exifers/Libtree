/**
 ** \file desugar/desugar-visitor.hh
 ** \brief Declaration of desugar::DesugarVisitor.
 */

#pragma once

#include <map>

#include <astclone/cloner.hh>

namespace desugar
{

  /// \brief Desugar some syntactic structures while duplicating an Ast.
  class DesugarVisitor : public astclone::Cloner
  {
  public:
    /// Superclass.
    using super_type = astclone::Cloner;

    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build a DesugarVisitor.
    DesugarVisitor(bool desugar_for_p,
                   bool desugar_string_cmp_p);

    /// Destroy a DesugarVisitor.
    virtual ~DesugarVisitor() = default;

    /// \name Visit methods.
    /// \{
    /// Desugar string comparisons.
    void operator()(const ast::OpExp&) override;
    /// Desugar `for' loops as `while' loops.
    void operator()(const ast::ForExp&) override;
    /// \}

  private:
    /// Desugar `for' loops?
    bool desugar_for_p_;
    /// Desugar string comparisons?
    bool desugar_string_cmp_p_;
  };

} // namespace desugar
