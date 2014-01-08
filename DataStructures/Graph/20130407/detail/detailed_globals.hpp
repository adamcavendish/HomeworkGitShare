#pragma once


#include "../globals.hpp"
// Template and their Specializations
#include "template_spec/VertexEdgeContainerGen.hpp"

namespace adamcavendish {
namespace graph {
namespace detail {

template <
	typename VertexProperties,
	typename VertexIterator>
struct Vertex {
	VertexProperties	_M_vertex_properties;
	VertexIterator		_M_vertex_iterator;
};//struct

template <
	typename EdgeProperties,
	typename EdgeIterator>
struct Edge {
	EdgeProperties		_M_edge_properties;
	EdgeIterator		_M_edge_iterator;
};//struct Edge

struct GraphNode {
	VertexIterator	_M_vertex_iter;
	EdgeIterator	_M_edge_iter;
}//struct GraphNode

struct DefaultVertex {};

struct DefaultEdge {};

struct DefaultGraph {};

}//namespace detail
}//namespace graph
}//namespace adamcavendish

