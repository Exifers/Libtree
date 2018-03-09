/**
 ** \file desugar/bounds-checking-visitor.hh
 ** \brief Declaration of desugar::BoundsCheckingVisitor.
 */

#pragma once

#include <map>

#include <astclone/cloner.hh>
#include <parse/tweast.hh>

namespace desugar
{

  /// \brief Add dynamic array bounds checks while duplicating an AST.
  class BoundsCheckingVisitor : public astclone::Cloner
  {
  public:
    /// Parent type.
    using super_type = astclone::Cloner;

    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build a BoundsCheckingVisitor.
    BoundsCheckingVisitor();

    /// Destroy a BoundsCheckingVisitor.
    virtual ~BoundsCheckingVisitor() = default;


    /// \name Visit methods.
    /// \{
  // FIXME: Some code was deleted here.
    /// \}

  private:
    /// The bounds checking runtime.
    ///
    /// Additional definitions to insert in the prelude.
    static const std::string prelude;

    // Symbols would be nicer, but maps of symbols are
    // inconvenient since there is no default ctor.
    using boxes_type = std::map<const type::Array*, std::string>;
    /// Map from an array type to the corresponding `box' type name.
    boxes_type boxes_;
  };

} // namespace desugar
