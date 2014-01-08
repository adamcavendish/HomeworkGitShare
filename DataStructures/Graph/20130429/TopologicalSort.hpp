#pragma once

#include <stdexcept>
#include <exception>
#include <string>

#include "DFSVisitor.hpp"

template <typename Graph, typename OutputIterator>
struct TopologicalSortVisitor : public DFSVisitor<Graph>
{
private:
	typedef Graph graph_type;
	typedef typename Graph::size_type size_type;
public: // functions
	explicit
	TopologicalSortVisitor(OutputIterator L_iter) :
		M_iter(L_iter)
	{}//constructor(OutputIterator)

	virtual bool
	back_edge(const size_type v1, const size_type v2, graph_type & g) override
	{
		std::throw_with_nested(std::logic_error(std::string(
						"Topological Sort Error: Graph is cyclic!")));
		return true;
	}//back_edge(v1, v2, g)

	virtual bool
	finish_vertex(const size_type v, graph_type & g) override {
		*(this->M_iter++) = v;
		return true;
	}//finish_vertex(v, g)

private: // members
	OutputIterator M_iter;
};//struct TopologicalSortVisitor

template <
	typename Graph,
	typename OutputIterator,
	typename Visitor = TopologicalSortVisitor<Graph, OutputIterator> >
void
topological_sort(Graph & L_g, OutputIterator L_iter) {
	Visitor L_vis(L_iter);
	L_g.depth_first_traverse(L_vis);
}//topological_sort(g, iter)

