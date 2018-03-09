/**
 ** \file callgraph/call-graph-visitor.hh
 ** \brief Definition of callgraph::CallGraphVisitor.
 **/
#pragma once

#include <ast/default-visitor.hh>
#include <ast/non-object-visitor.hh>
#include <callgraph/fundec-graph.hh>

namespace callgraph
{

  /// Computes the CallGraph.
  class CallGraphVisitor
    : protected ast::DefaultConstVisitor
    , protected ast::NonObjectConstVisitor
  {
  public:
    using super_type = ast::DefaultConstVisitor;
    using super_type::operator();
    const CallGraph* create(const ast::Ast& tree);
    CallGraph* create(ast::Ast& tree);

  protected:
    void operator()(const ast::CallExp& e) override;
    void operator()(const ast::FunctionDecs& e) override;
    void operator()(const ast::FunctionDec& e) override;

  protected:
    /// Current function.
    ast::FunctionDec* caller = nullptr;
    /// Call graph.
    CallGraph* callgraph = nullptr;
  };

} // namespace callgraph
