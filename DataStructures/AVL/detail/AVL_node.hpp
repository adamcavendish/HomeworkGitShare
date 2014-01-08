#pragma once

#include "AVL_node_base.hpp"

template <typename Val>
struct AVL_node : public AVL_node_base
{
	Val _M_data;

	AVL_node() :
		_M_parent(nullptr),
		_M_left(nullptr),
		_M_right(nullptr),
		_M_data()
	{}//default constructor

	AVL_node(const AVL_node & L_rhs) :
		_M_parent(L_rhs._M_parent),
		_M_left(L_rhs._M_left),
		_M_right(L_rhs._M_right),
		_M_data(L_rhs._M_data)
	{}//copy constructor

	AVL_node(AVL_node && L_rhs) :
		_M_parent(L_rhs._M_parent),
		_M_left(L_rhs._M_left),
		_M_right(L_rhs._M_right),
		_M_data(std::forward<Val>(L_rhs._M_data))
	{
		L_rhs._M_parent = nullptr;
		L_rhs._M_left = nullptr;
		L_rhs._M_right = nullptr;
	}//move constructor

	~AVL() {
		this->_M_parent = nullptr;
		this->_M_left = nullptr;
		this->_M_right = nullptr;
	}//destructor

	AVL_node &
	operator=(const AVL_node & L_rhs) {
		if(this == &L_rhs)
			return (*this);
		this->_M_parent = L_rhs._M_parent;
		this->_M_left = L_rhs._M_left;
		this->_M_right = L_rhs._M_right;
		this->_M_data = L_rhs._M_data;
		return (*this);
	}//copy assignment

	AVL_node &
	operator=(AVL_node && L_rhs) {
		if(this == &L_rhs)
			return (*this);
		this->_M_parent = L_rhs._M_parent;
		this->_M_left = L_rhs._M_left;
		this->_M_right = L_rhs._M_right;
		this->_M_data = std::forward<Val>(L_rhs._M_data);
		L_rhs._M_parent = nullptr;
		L_rhs._M_left = nullptr;
		L_rhs._M_right = nullptr;
		return (*this);
	}//move assignment
};//struct AVL_node

