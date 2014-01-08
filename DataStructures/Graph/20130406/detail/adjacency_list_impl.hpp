#pragma once

//STL
#include <vector>
#include <list>
#include <utility>
//include
#include "detailed_globals.hpp"

namespace adamcavendish {
namespace graph {
namespace detail {

#if __cplusplus >= 201103L
#endif

template <
	typename Directed = directed,
	typename VertexProperties = DefaultVertex,
	typename EdgeProperties = DefaultEdge,
	VertexEdgeContainerEnum VertexContainerEnum = vector,
	VertexEdgeContainerEnum EdgeContainerEnum = vector>
class adjacency_list_impl
{
private://types

	// vertex / edge container generator
	typedef VertexEdgeContainerGen<
		EdgeContainerEnum,
		EdgeProperties
	>::type													edge_container;
	typedef VertexEdgeContainerGen<
		VertexContainerEnum,
		std::pair<VertexProperties, edge_container>
	>::type													vertex_container;
	// descriptor(s) are used to traverse through vertexes / edges.
	typedef vertex_container::iterator						vertex_descriptor;
	typedef edge_container::iterator						edge_descriptor;
	typedef vertex_container::const_iterator				const_vertex_descriptor;
	typedef edge_container::const_iterator					const_edge_descriptor;
	
	typedef std::size_t										size_type;
private://members
	vertex_container _M_graph_data;
	 
public:
	/**
	 *--------------------------------------------------
	 *--------------------------------------------------
	 */
	explicit
	adjacency_list_impl()
	{}

	explicit
	adjacency_list_impl(size_type __num)
	{
		if(VertexContainerEnum == vector)
			_M_graph_data.reserve(__num);
	}//constructor(__num)

	template <typename VertexIterator>
	explicit
	adjacency_list_impl(VertexIterator __beg, VertexIterator __end) {
		for(VertexIterator __ii = __beg; __ii != __end; ++__ii)
			_M_graph_data.push_back(std::make_pair(*__ii, edge_container()));
	}//constructor(vertex_beg_iter, vertex_end_iter)
	
	_M_add_edge()

};//class adjacency_list_impl

}//namespace detail
}//namespace graph
}//namespace adamcavendish

