#pragma once

#include <utility>

namespace adamcavendish {
namespace container {
namespace __detail {

struct __bst_node_base
{
	__bst_node_base * _M_parent;
	__bst_node_base * _M_left;
	__bst_node_base * _M_right;

	__bst_node_base() = default;
	__bst_node_base(const __bst_node_base &) = default;
	__bst_node_base(__bst_node_base &&) = default;
};//struct __bst_node_base

template <typename Key, typename Val>
struct __bst_node : public __bst_node_base
{
	std::pair<Key, Val> _M_node;

	explicit
	__bst_node(const std::pair<Key, Val> & __node) :
		_M_node(__node)
	{}

	explicit
	__bst_node(std::pair<Key, Val> && __node) :
		_M_node(std::forward<std::pair<Key, Val> >(__node))
	{}
};//struct __bst_node

}//namespace __detail
}//namespace container
}//namespace adamcavendish

