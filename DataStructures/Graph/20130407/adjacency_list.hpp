#pragma once

// STL
#include <iostream>

//include
#include "globals.hpp"
#include "detail/detailed_globals.hpp"
#include "detail/adjacency_list_impl.hpp"

namespace adamcavendish {
namespace graph {

#if __cplusplus >= 201103L
#endif

template <
	typename Directed = directed,
	typename VertexProperties = DefaultVertex,
	typename EdgeProperties = DefaultEdge,
	VertexEdgeContainerEnum VertexContainerEnum = vector,
	VertexEdgeContainerEnum EdgeContainerEnum = vector>
class adjacency_list : private adjacency_list_impl
{
public: //types
	// vertex / edge container generator
	typedef detail::VertexEdgeContainerGen<
		EdgeContainerEnum,
		EdgeProperties
	>::type													edge_container;
	typedef detail::VertexEdgeContainerGen<
		VertexContainerEnum,
		std::pair<VertexProperties, edge_container>
	>::type													vertex_container;
	// descriptor(s) are used to traverse through vertexes / edges.
	typedef detail::VertexIterator<
		vertex_container,
		edge_container,
		VertexProperties,
		EdgeProperties>										vertex_iterator;
	typedef detail::EdgeIterator<
		vertex_container,
		edge_container,
		VertexProperties,
		EdgeProperties>										edge_iterator;
	typedef detail::ConstVertexIterator<
		vertex_container,
		edge_container,
		VertexProperties,
		EdgeProperties>										const_vertex_iterator;
	typedef detail::ConstEdgeIterator<
		vertex_container,
		edge_container,
		VertexProperties,
		EdgeProperties>										const_edge_iterator;
	
	typedef std::size_t										size_type;
private: //members
	vertex_container	_M_graph_data;
	size_type			_M_vertex_num;
	size_type			_M_edge_num;
public: //functions
	size_type
	num_vertexes() const;

	size_type
	num_edges() const;

	bool
	empty() const;

	vertex_iterator
	find(const VertexProperties & __v);
	const_vertex_iterator
	find(const VertexProperties & __v) const;

	edge_iterator
	find(const EdgeProperties & __e);
	const_edge_iterator
	find(const EdgeProperties & __e) const;

	vertex_iterator
	add_vertex(const VertexProperties & __v);

	edge_iterator
	add_edge(const vertex_iterator & __v1,
			const vertex_iterator & __v2,
			const EdgeProperties & __e);
	
	bool
	delete_vertex(const vertex_iterator & __v);

	bool
	delete_edge(const edge_iterator & __v);
};//class adjacency_list

}//namespace graph
}//namespace adamcavendish

