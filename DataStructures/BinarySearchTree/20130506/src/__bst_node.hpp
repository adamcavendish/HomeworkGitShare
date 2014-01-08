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

	__bst_node_base() :
		_M_parent(nullptr),
		_M_left(nullptr),
		_M_right(nullptr)
	{}//default constructor

	__bst_node_base(const __bst_node_base & __rhs) :
		_M_parent(__rhs._M_parent),
		_M_left(__rhs._M_left),
		_M_right(__rhs._M_right)
	{}//copy constructor

	__bst_node_base(__bst_node_base && __rhs) :
		_M_parent(__rhs._M_parent),
		_M_left(__rhs._M_left),
		_M_right(__rhs._M_right)
	{
		__rhs._M_parent = nullptr;
		__rhs._M_left = nullptr;
		__rhs._M_right = nullptr;
	}//move constructor

	__bst_node_base &
	operator=(const __bst_node_base & __rhs) {
		this->_M_parent = __rhs._M_parent;
		this->_M_left = __rhs._M_left;
		this->_M_right = __rhs._M_right;

		return (*this);
	}//copy assignment

	__bst_node_base &
	operator=(__bst_node_base && __rhs) {
		this->_M_parent = __rhs._M_parent;
		__rhs._M_parent = nullptr;
		this->_M_left = __rhs._M_left;
		__rhs._M_left = nullptr;
		this->_M_right = __rhs._M_right;
		__rhs._M_right = nullptr;

		return (*this);
	}//move assignment

	~__bst_node_base() {
		this->_M_parent = nullptr;
		this->_M_left = nullptr;
		this->_M_right = nullptr;
	}//destructor
};//struct __bst_node_base

template <typename Key, typename Val>
struct __bst_node : public __bst_node_base
{
	std::pair<Key, Val> _M_node;

	__bst_node() :
		_M_node()
	{}//default constructor

	__bst_node(const __bst_node & __rhs) :
		_M_node(__rhs._M_node)
	{}//copy constructor

	__bst_node(__bst_node && __rhs) :
		_M_node(std::forward<__bst_node>(__rhs))
	{}//move constructor

	__bst_node(const std::pair<Key, Val> & __rhs) :
		_M_node(__rhs)
	{}//constructor(const std::pair<Key, Val> &)

	__bst_node(std::pair<Key, Val> && __rhs) :
		_M_node(std::forward<std::pair<Key, Val> >(__rhs))
	{}//constructor(std::pair<Key, Val> &&)

	__bst_node &
	operator=(const __bst_node & __rhs)
	{ _M_node = __rhs._M_node; }//copy assignment

	__bst_node &
	operator=(__bst_node && __rhs)
	{ _M_node = std::forward<__bst_node>(__rhs); }//move assignment

	~__bst_node() {}//destructor
};//struct __bst_node

}//namespace __detail
}//namespace container
}//namespace adamcavendish

