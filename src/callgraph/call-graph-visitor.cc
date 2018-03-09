/**
 ** \file callgraph/call-graph-visitor.cc
 ** \brief Implementation of callgraph::CallGraphVisitor.
 **/

#include <ast/call-exp.hh>
#include <ast/function-dec.hh>
#include <callgraph/call-graph-visitor.hh>

namespace callgraph
{

  const CallGraph*
  CallGraphVisitor::create(const ast::Ast& tree)
  {
    // Create a new empty callgraph
    callgraph = new CallGraph();

    // Launch visitor.
    tree.accept(*this);

    // Return created callgraph.
    return callgraph;
  }

  CallGraph*
  CallGraphVisitor::create(ast::Ast& tree)
  {
    return const_cast<CallGraph*>(create(const_cast<const ast::Ast&>(tree)));
  }

  /*-----------.
  | Visiting.  |
  `-----------*/

  void
  CallGraphVisitor::operator()(const ast::CallExp& e)
  {
  // FIXME: Some code was deleted here (Link the Caller with the CallExp's declaration).
  }

  void
  CallGraphVisitor::operator()(const ast::FunctionDecs& e)
  {
    // First define the nodes for each defined function.
    for (ast::FunctionDec* f : e.decs_get())
      callgraph->fundec_add(f);
    // Now bind callers and callees.
    super_type::operator()(e);
  }

  void
  CallGraphVisitor::operator()(const ast::FunctionDec& e)
  {
    // Current function becomes temporarily the caller function.
    ast::FunctionDec* save = caller;
    caller = const_cast<ast::FunctionDec*>(&e);
    super_type::operator()(e);
    caller = save;
  }

} // namespace callgraph
