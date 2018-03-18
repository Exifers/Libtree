/**
 ** \file callgraph/libcallgraph.hh
 ** \brief Declare functions and variables exported by callgraph module.
 */

#pragma once

#include <ast/fwd.hh>
#include <callgraph/fundec-graph.hh>

/// Computing static link related information.
namespace callgraph
{


#ifdef SWIG
  %newobject callgraph_compute;
#endif
  /// Build the callgraph.
  const CallGraph* callgraph_compute(const ast::Ast& tree);
  CallGraph* callgraph_compute(ast::Ast& tree);


} // namespace callgraph
