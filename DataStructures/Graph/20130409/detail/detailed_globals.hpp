#pragma once


#include "../globals.hpp"
// Template and their Specializations
#include "template_spec/VertexEdgeContainerGen.hpp"
#include "template_spec/meta"

namespace adamcavendish {
namespace graph {
namespace detail {

template <
	typename VertexPropertiesContainer,
	typename EdgePropertiesContainer,
	bool whether_const>
struct GraphNode {
	typename meta_if<whether_const,
		VertexPropertiesContainer::const_iterator,
		VertexPropertiesContainer::iterator
	>::type								_M_vertex_iter;
	typename meta_if<whether_const,
		EdgePropertiesContainer::const_iterator,
		EdgePropertiesContainer::iterator
	>::type								_M_edge_iter;
}//struct GraphNode

template <
	typename VertexPropertiesContainer,
	typename EdgePropertiesContainer,
	bool whether_const>
struct VertexContainerContents {
	typename meta_if<whether_const,
		VertexPropertiesContainer::const_iterator,
		VertexPropertiesContainer::iterator
	>::type										_M_vertex_iter,
	EdgeContainerContents<VertexPropertiesContainer, EdgePropertiesContainer> _M_row_edges,

	struct {
		bool _M_vertex_flag;
	} _M_aux;
};//struct VertexContainerContents

template <
	typename VertexPropertiesContainer,
	typename EdgePropertiesContainer>
struct EdgeContainerContents {
	GraphNode _M_graph_node;

	struct {
		bool _M_edge_flag;
	} _M_aux;
};//struct EdgeContainerContents

struct DefaultVertex {};

struct DefaultEdge {};

struct DefaultGraph {};

}//namespace detail
}//namespace graph
}//namespace adamcavendish

