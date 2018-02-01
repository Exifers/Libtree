/**
 ** \file ast/decs-list.hh
 ** \brief Declaration of ast::DecsList.
 */

#pragma once

#include <ast/ast.hh>

namespace ast
{

  /// DecsList.
  class DecsList : public Ast
  {
  public:
    using decs_type = std::list<Decs*>;

    /// Prepend \a d.
    void push_front(Decs* d);
    /// Append \a d.
    void emplace_back(Decs* d);

    /// Splice the content of \a ds in front of this list.
    void splice_front(DecsList& ds);
    /// Splice the content of \a ds at the back this list.
    void splice_back(DecsList& ds);

    /// Construct a DecsList node.
    DecsList(const Location& location);

  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a DecsList node.
    DecsList(const Location& location, const DecsList::decs_type& decs);
    DecsList(const DecsList&) = delete;
    DecsList& operator=(const DecsList&) = delete;
    /// Destroy a DecsList node.
    virtual ~DecsList();
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return declarations.
    const DecsList::decs_type& decs_get() const;
    /// Return declarations.
    DecsList::decs_type& decs_get();
    /** \} */

  protected:
    /// Declarations.
    DecsList::decs_type decs_;
  };

} // namespace ast

#include <ast/decs-list.hxx>

