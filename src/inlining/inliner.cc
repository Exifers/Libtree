/**
 ** \file inlining/inliner.cc
 ** \brief Implementation of inlining::Inliner.
 */

#include <boost/graph/transitive_closure.hpp>

#include <callgraph/libcallgraph.hh>
#include <inlining/inliner.hh>
#include <parse/libparse.hh>
#include <parse/tweast.hh>

namespace inlining
{

  using namespace ast;

  Inliner::Inliner(const ast::Ast& tree)
    : super_type(), rec_funs_()
  {
    // Compute the transitive closure of the call graph to compute the
    // set of recursive functions.
    const callgraph::CallGraph* graph = callgraph::callgraph_compute(tree);
    callgraph::CallGraph closure;
    boost::transitive_closure(*graph, closure);

    // Re-attach properties to the vertices.
    for (auto [i, i_end] = boost::vertices(closure); i != i_end; ++i)
      closure[*i] = (*graph)[*i];
    // Detect recursive functions.
    for (auto [i, i_end] = boost::vertices(closure); i != i_end; ++i)
      {
        for (auto [j, j_end] = boost::adjacent_vertices(*i, closure);
             j != j_end; ++j)
          if (*i == *j)
            rec_funs_.insert(closure[*i]);
      }
    delete graph;
  }

#warning // FIXME: Some code was deleted here.

} // namespace inlining
