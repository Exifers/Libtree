/**
 ** \file misc/graph.hxx
 ** \brief Undirected/oriented graph implementation.
 */

#pragma once

#include <algorithm>
#include <fstream>
#include <sstream>
#include <tuple>

#include <misc/algorithm.hh>
#include <misc/contract.hh>
#include <misc/deref.hh>


namespace misc
{

  /*--------.
  | Graph.  |
  `--------*/

  template <typename Orientation, typename VertexLabel, typename EdgeLabel>
  typename graph<Orientation, VertexLabel, EdgeLabel>::vertex_descriptor
  graph<Orientation, VertexLabel, EdgeLabel>::
  vertex_add(const VertexLabel& l)
  {
    return boost::add_vertex(l, *this);
  }

  /*-----------------------------------------------------------------.
  | graph::print.                                                    |
  |                                                                  |
  | For oriented graph, keeping edges bound to the source node looks |
  | nicer, while an edge oriented dump is more appropriate for       |
  | unoriented graphs.  In the latter case, be sure not to output    |
  | each edge twice.                                                 |
  |                                                                  |
  | FIXME: We do lack something similar to Escape when "deref"ing,   |
  | for if there are strings in there, they should be escaped for    |
  | dotty.                                                           |
  |                                                                  |
  | FIXME: Enforce the order by sorting before outputting.           |
  `-----------------------------------------------------------------*/

  template <typename Orientation, typename VertexLabel, typename EdgeLabel>
  std::ostream&
  graph<Orientation, VertexLabel, EdgeLabel>::
  print(std::ostream& ostr) const
  {
    using misc::deref;

    std::string graphtype = boost::is_undirected(*this) ? "graph" : "digraph";
    std::string link =      boost::is_undirected(*this) ? "--"    : "->";
    ostr << "/* Graph Visualization */\n";

    ostr << graphtype << " \"" << name_get() << "\" {\n"
         << "  node [shape=box];\n";

    for (auto [vi, vi_end] = boost::vertices(*this); vi != vi_end; ++vi)
      {
        ostr << "  \"" << *vi << "\" "
             << "[label=\"";
        vertex_print(*vi, ostr);
        ostr << "\"]\n";
      }

    for (auto [ei, ei_end] = boost::edges(*this); ei != ei_end; ++ei)
      {
        std::ostringstream label;
        label << deref <<(*this)[*ei];
        ostr << "  \"" << boost::source(*ei, *this) << "\" "
             << link
             << " \""  << boost::target(*ei, *this) << "\"";
        if (label.str() != "")
          ostr << " [label=\"" << label.str() << "\"]";
        ostr << '\n';
      }

    epilogue_print(ostr);

    return ostr << "}\n";
  }

  template <typename Orientation, typename VertexLabel, typename EdgeLabel>
  std::ostream&
  graph<Orientation, VertexLabel, EdgeLabel>::
  epilogue_print(std::ostream& ostr) const
  {
    return ostr;
  }

  template <typename Orientation, typename VertexLabel, typename EdgeLabel>
  void
  graph<Orientation, VertexLabel, EdgeLabel>::
  print(std::string file) const
  {
    std::ofstream ofs;

    static unsigned cpt = 0;
    if (file.empty())
      {
        std::stringstream sstr;
        sstr << "graph-" << cpt << ".gv";
        ++cpt;
        file = sstr.str();
      }

    file += ".gv";
    ofs.open(file.c_str());
    print(ofs);
    ofs.close();
  }

  template <typename Orientation, typename VertexLabel, typename EdgeLabel>
  const std::string&
  graph<Orientation, VertexLabel, EdgeLabel>::name_get() const
  {
    // For some reason, the following cast is needed with Boost 1.45.
    return boost::get_property(static_cast<const super_type&>(*this),
                               boost::graph_name);
  }

  template <typename Orientation, typename VertexLabel, typename EdgeLabel>
  void
  graph<Orientation, VertexLabel, EdgeLabel>::
  name_set(const std::string& name)
  {
    boost::set_property(*this, boost::graph_name, name);
  }

  template <typename Orientation, typename VertexLabel, typename EdgeLabel>
  inline std::ostream&
  operator<<(std::ostream& ostr,
             const graph<Orientation, VertexLabel, EdgeLabel>& g)
  {
    return g.print(ostr);
  }

  inline std::ostream& operator<<(std::ostream& ostr, empty)
  {
    return ostr;
  }


  /*----------------.
  | DirectedGraph.  |
  `----------------*/

  template <typename VertexLabel, typename EdgeLabel>
  directed_graph<VertexLabel, EdgeLabel>::~directed_graph()
  {}

  template <typename VertexLabel, typename EdgeLabel>
  void
  directed_graph<VertexLabel, EdgeLabel>::
  edge_add(const vertex_descriptor& v1, const vertex_descriptor& v2)
  {
    boost::add_edge(v1, v2, *this);
  }


  template <typename NodeLabel, typename EdgeLabel>
  std::vector<typename directed_graph<NodeLabel, EdgeLabel>::vertex_descriptor>
  directed_graph<NodeLabel, EdgeLabel>::topological_sort() const
  {
    std::vector<vertex_descriptor> res;
    misc::set<vertex_descriptor> visited;
    return res;
  }


  /*------------------.
  | UndirectedGraph.  |
  `------------------*/

  template <typename VertexLabel, typename EdgeLabel>
  undirected_graph<VertexLabel, EdgeLabel>::~undirected_graph()
  {}

  template <typename VertexLabel, typename EdgeLabel>
  void
  undirected_graph<VertexLabel, EdgeLabel>::
  edge_add(const vertex_descriptor& v1, const vertex_descriptor& v2)
  {
    if (v1 > v2)
      boost::add_edge(v2, v1, *this);
    else
      boost::add_edge(v1, v2, *this);
  }

} // namespace misc
