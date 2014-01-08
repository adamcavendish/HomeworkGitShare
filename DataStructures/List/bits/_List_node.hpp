#pragma once

#include <utility>

namespace adamcavendish {
namespace data_structure {

namespace __detail {

/**
 * Common part of a node in the Slist
 */
struct _List_node_base
{
	_List_node_base * _M_prev;
	_List_node_base * _M_next;
};//struct _List_node_base

/**
 * An actual node in the Slist
 */
template <typename T>
struct _List_node : public _List_node_base
{
	T _M_data;
public:	// member functions
	template <typename ... Args_t>
	_List_node(Args_t && ... __arg) :
		_M_data(std::forward<Args_t>(__arg)...)
	{}
};//struct _List_node

}// namespace __detail

}// namespace data_structure
}// namespace adamcavendish

