/**
 ** \file callgraph/fundec-graph.hh
 ** \brief Declare and define fundec graph.
 */

#pragma once

#include <map>

#include <boost/graph/adjacency_list.hpp>

#include <ast/function-dec.hh>
#include <misc/graph.hh>

namespace callgraph
{

  /*--------------.
  | FundecGraph.  |
  `--------------*/

  class FundecGraph: public misc::directed_graph<ast::FunctionDec*>
  {
  public:
    virtual ~FundecGraph() = default;

    /// Add a vertex to the graph, and attach a function definition to it.
    void fundec_add(ast::FunctionDec* f);
    /// Create an edge between two vertices, identified by the
    /// FunctionDec attached to each of them.
    void fundec_link(ast::FunctionDec* fu, ast::FunctionDec* fv);

    /// Retrieve the vertex handle corresponding to a FunctionDec.
    vertex_descriptor hfundec_get(ast::FunctionDec* f) const;

  protected:
    /// Print the label of vertex of a graph.
    std::ostream&
    vertex_print(vertex_descriptor v, std::ostream& ostr) const override;

    using hfundecs_type = std::map<ast::FunctionDec*, vertex_descriptor>;
    hfundecs_type hfundecs;
  };

  using CallGraph = FundecGraph;


  /*------------.
  | Iterators.  |
  `------------*/

  /// Iterator on the vertices of a FundecGraph.
  using fundecgraph_vertex_iter_type =
    boost::graph_traits<FundecGraph>::vertex_iterator;
  /// Iterator on the edges of a FundecGraph.
  using fundecgraph_edge_iter_type =
    boost::graph_traits<FundecGraph>::edge_iterator;
  /// Iterator on the neighborhood of a vertex of a FundecGraph.
  using fundecgraph_neighb_iter_type =
    boost::graph_traits<FundecGraph>::adjacency_iterator;

  /// \name Aliases.
  /// \{
  /// Iterator on the vertices of a CallGraph.
  using callgraph_vertex_iter_type = fundecgraph_vertex_iter_type;
  /// Iterator on the neighborhood of a vertex of a CallGraph.
  using callgraph_neighb_iter_type = fundecgraph_neighb_iter_type;
  /// \}

} // namespace callgraph

#include <callgraph/fundec-graph.hxx>
