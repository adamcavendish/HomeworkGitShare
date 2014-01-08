#pragma once

// STL
#include <algorithm>
// include
#include "adjacency_list.hpp"

namespace adamcavendish {
namespace graph {

template <
	typename Directed,
	typename VertexProperties,
	typename EdgeProperties,
	VertexEdgeContainerEnum VertexContainerEnum,
	VertexEdgeContainerEnum EdgeContainerEnum>
size_type
adjacency_list::num_vertexes() const
{ return this->_M_vertex_num; }

template <
	typename Directed,
	typename VertexProperties,
	typename EdgeProperties,
	VertexEdgeContainerEnum VertexContainerEnum,
	VertexEdgeContainerEnum EdgeContainerEnum>
size_type
adjacency_list::num_edges() const
{ return this->_M_edge_num; }

template <
	typename Directed,
	typename VertexProperties,
	typename EdgeProperties,
	VertexEdgeContainerEnum VertexContainerEnum,
	VertexEdgeContainerEnum EdgeContainerEnum>
bool
adjacency_list::empty() const
{ return (this->_M_vertex_num == 0); }

template <
	typename Directed,
	typename VertexProperties,
	typename EdgeProperties,
	VertexEdgeContainerEnum VertexContainerEnum,
	VertexEdgeContainerEnum EdgeContainerEnum>
vertex_iterator
adjacency_list::find(const VertexProperties & __v) {
#if __cplusplus >= 201103L
	vertex_container_iterator __ret = 
	std::find_if((this->_M_graph_data).begin(),
			(this->_M_graph_data).end(),
			[=](const std::pair<VertexProperties, edge_container> & __dat) {
				return (__dat->first == __v);
			});
#else
	struct Predicate {
		bool
		operator() (const std::pair<VertexProperties, edge_container> & __dat)
		{ return (__dat->first == __v) };
	};//local functor Predicate

	vertex_container_iterator __ret = 
	std::find_if((this->_M_graph_data).begin(), (this->_M_graph_data).end(),
			Predicate());
#endif
	return vertex_iterator(__ret);
}//find(VertexProperties)

template <
	typename Directed,
	typename VertexProperties,
	typename EdgeProperties,
	VertexEdgeContainerEnum VertexContainerEnum,
	VertexEdgeContainerEnum EdgeContainerEnum>
const_vertex_iterator
find(const VertexProperties & __v) const {
#if __cplusplus >= 201103L
	vertex_container_iterator __ret = 
	std::find_if((this->_M_graph_data).begin(),
			(this->_M_graph_data).end(),
			[=](const std::pair<VertexProperties, edge_container> & __dat) {
				return (__dat->first == __v);
			});
#else
	struct Predicate {
		bool
		operator() (const std::pair<VertexProperties, edge_container> & __dat)
		{ return (__dat->first == __v) };
	};//local functor Predicate

	vertex_container_iterator __ret = 
	std::find_if((this->_M_graph_data).begin(), (this->_M_graph_data).end(),
			Predicate());
#endif//c++11
	return vertex_iterator(__ret);
}//find(VertexProperties) const

template <
	typename Directed,
	typename VertexProperties,
	typename EdgeProperties,
	VertexEdgeContainerEnum VertexContainerEnum,
	VertexEdgeContainerEnum EdgeContainerEnum>
edge_iterator
find(const EdgeProperties & __e) {
#if __cplusplus >= 201103L
	
#else
#endif//c++11
}//find(EdgeProperties)

template <
	typename Directed,
	typename VertexProperties,
	typename EdgeProperties,
	VertexEdgeContainerEnum VertexContainerEnum,
	VertexEdgeContainerEnum EdgeContainerEnum>
const_edge_iterator
find(const EdgeProperties & __e) const;

template <
	typename Directed,
	typename VertexProperties,
	typename EdgeProperties,
	VertexEdgeContainerEnum VertexContainerEnum,
	VertexEdgeContainerEnum EdgeContainerEnum>
vertex_iterator
add_vertex(const VertexProperties & __v);

template <
	typename Directed,
	typename VertexProperties,
	typename EdgeProperties,
	VertexEdgeContainerEnum VertexContainerEnum,
	VertexEdgeContainerEnum EdgeContainerEnum>
edge_iterator
add_edge(const vertex_iterator & __v1,
		const vertex_iterator & __v2,
		const EdgeProperties & __e);

template <
	typename Directed,
	typename VertexProperties,
	typename EdgeProperties,
	VertexEdgeContainerEnum VertexContainerEnum,
	VertexEdgeContainerEnum EdgeContainerEnum>
bool
delete_vertex(const vertex_iterator & __v);

template <
	typename Directed,
	typename VertexProperties,
	typename EdgeProperties,
	VertexEdgeContainerEnum VertexContainerEnum,
	VertexEdgeContainerEnum EdgeContainerEnum>
bool
delete_edge(const edge_iterator & __v);

}//namespace graph
}//namespace adamcavendish

