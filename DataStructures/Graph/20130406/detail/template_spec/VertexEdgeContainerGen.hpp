#pragma once

// STL
#include <vector>
#include <list>
#include <set>
#include <map>

#include "../../globals.hpp"

/**
 * @file VertexEdgeContainerGen.hpp
 * template Specializations for VertexEdgeContainerGen Structure,
 * which is used to generate Vertex or Edge Containers
 */

namespace adamcavendish {
namespace graph {
namespace detail {

// For Specialization
template <VertexEdgeContainerEnum container_enum, typename value_type>
struct VertexEdgeContainerGen
{};//struct VertexContainerGen

template <typename value_type>
struct VertexEdgeContainerGen<vector, value_type>
{
	typedef std::vector<value_type> type;
};

template <typename value_type>
struct VertexEdgeContainerGen<list, value_type>
{
	typedef std::list<value_type> type;
};

template <typename value_type>
struct VertexEdgeContainerGen<set, value_type>
{
	typedef std::set<value_type> type;
};

template <typename value_type>
struct VertexEdgeContainerGen<map, value_type>
{
	typedef std::map<value_type> type;
};

}//namespace detail
}//namespace graph
}//namespace adamcavendish

