#pragma once

#include "detail/VertexIterator.hpp"
#include "detail/EdgeIterator.hpp"

namespace adamcavendish {
namespace graph {

struct undirected {};
struct directed {};
struct bindirectional {};

enum VertexEdgeContainerEnum {
	vector,
	list
};//enum VertexEdgeContainerEnum


}//namespace graph
}//namespace adamcavendish

