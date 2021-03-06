/**
 ** \file ast/string-exp.hh
 ** \brief Declaration of ast::StringExp.
 */

#pragma once

#include <ast/exp.hh>
#include <string>

namespace ast
{

  /// StringExp.
  /** This is a leaf node and represents a basic string as returned by the lexer
  **  . */
  class StringExp : public Exp
  {
    public:

    StringExp(const Location& location, std::string value);
    StringExp(const StringExp&) = delete;
    StringExp& operator=(const StringExp&) = delete;
    // Destroy a StringExp node.
    virtual ~StringExp() = default;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    std::string value_get() const;

    protected:
      std::string value_;
  };

} // namespace ast

#include <ast/string-exp.hxx>

