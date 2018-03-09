/**
 ** \file callgraph/fundec-graph.hxx
 ** \brief Inline methods for callgraph/fundec-graph.hh.
 */

#pragma once

#include <callgraph/fundec-graph.hh>

namespace callgraph
{

  inline void
  FundecGraph::fundec_add(ast::FunctionDec* f)
  {
    hfundecs[f] = this->vertex_add(f);
  }

  inline void
  FundecGraph::fundec_link(ast::FunctionDec* fu, ast::FunctionDec* fv)
  {
    vertex_descriptor u = hfundecs[fu];
    vertex_descriptor v = hfundecs[fv];
    boost::add_edge(u, v, *this);
  }

  inline
  FundecGraph::vertex_descriptor
  FundecGraph::hfundec_get(ast::FunctionDec* f) const
  {
    hfundecs_type::const_iterator i = hfundecs.find(f);
    assertion(i != hfundecs.end());
    return i->second;
  }

  inline
  std::ostream&
  FundecGraph::vertex_print(vertex_descriptor v, std::ostream& ostr) const
  {
    return ostr << (*this)[v]->name_get();
  }

} // namespace callgraph
