#pragma once

#include <initializer_list>
#include <stdexcept>
#include <exception>
#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <iostream>
#include <stack>

// NE means NE
const char NE = '\0';

template <typename T>
struct tree_node
{
	T _M_data;
	tree_node * _M_lnode;
	tree_node * _M_rnode;

	tree_node() :
		_M_data(T()),
		_M_lnode(nullptr),
		_M_rnode(nullptr)
	{}

	tree_node(const T & __val) :
		_M_data(__val),
		_M_lnode(nullptr),
		_M_rnode(nullptr)
	{}//T constructor
};//struct tree_node


template <typename T>
class Tree
{
public:// public all the stuffs.

	// members
	tree_node<T> * _M_head;

	// functions
	
	Tree() = delete;

	Tree(std::initializer_list<T> __data_li,
			std::initializer_list<int> __parent_li)
	{
		if(__data_li.size() != __parent_li.size())
			throw std::invalid_argument("data size != parent size");

		std::cout << "Using " << __data_li.size()
			<< " to initialize" << std::endl;

		auto __arr_size = __data_li.size();
		auto __arr_data = __data_li.begin(); // Hack it.
		auto __arr_parent = __parent_li.begin();

		_M_create_head(__arr_data[0]);

		std::queue<tree_node<T> *> __que;
		__que.push(_M_head);
		tree_node<T> * __prev_node = nullptr;
		int __prev_parent = -1;
		for(auto __i = 1ul; __i < __arr_size; ++__i) {
			auto __node = new tree_node<T>(__arr_data[__i]);

			if(__arr_parent[__i] != __prev_parent) {
				while(__arr_parent[__i] != ++__prev_parent)
					__que.pop();
				__prev_node = __que.front();
				__que.pop();
				__prev_node->_M_lnode = __node;	
			} else {
				__prev_node->_M_rnode = __node;
			}//if-else
			__prev_node = __node;
			__que.push(__node);
		}//for
	}//initializer_list constructor

	~Tree()
	{
		postorder([=](tree_node<T> * __node) { delete __node; });
	}//destructor

	void
	_M_create_head(const T & __val) {
		_M_head = new tree_node<T>(__val);
	}//_M_create_head(__val)
	
	void
	_M_insert_left(tree_node<T> * __parent, const T & __val) {
		__parent->_M_lnode = new tree_node<T>(__val);
	}//_M_insert_left(__parent, __val)

	void
	_M_insert_right(tree_node<T> * __parent, const T & __val) {
		__parent->_M_rnode = new tree_node<T>(__val);
	}//_M_insert_right(__parent, __val)

	void
	preorder(std::function< void(tree_node<T> *) > func) {
		tree_node<T> * __node = _M_head;
		if(__node == nullptr)
			return;

		std::stack<tree_node<T> *> stk;

		do {
			while(__node != nullptr) {
				func(__node);
				stk.push(__node);
				__node = __node->_M_lnode;
			}//while
			
			if(stk.empty())
				break;

			__node = stk.top();
			stk.pop();
			__node = __node->_M_rnode;
		} while(1);
	}//preorder(func)

	void
	inorder(std::function< void(tree_node<T> * __node) > func) {
		std::function< void(tree_node<T> *) >  __aux_func =
			[=, &__aux_func](tree_node<T> * __node)
		{
			if(__node != nullptr) {
				__aux_func(__node->_M_lnode);
				func(__node);
				__aux_func(__node->_M_rnode);
			}//if
		};//lambda
		
		__aux_func(_M_head);
	}//inorder(func)

	void
	postorder(std::function< void(tree_node<T> * __node) > func) {
		std::function< void(tree_node<T> *) > __aux_func =
			[=, &__aux_func](tree_node<T> * __node)
		{
			if(__node != nullptr) {
				__aux_func(__node->_M_lnode);
				__aux_func(__node->_M_rnode);
				func(__node);
			}//if
		};//lambda
		
		__aux_func(_M_head);
	}//postorder(func)

	void
	levelorder(std::function< void(tree_node<T> *) > func) {
		if(_M_head == nullptr)
			return;

		std::queue<tree_node<T> *> que;
		que.push(_M_head);

		while(!que.empty()) {
			tree_node<T> * __node = que.front();
			func(__node);
			que.pop();

			if(__node->_M_lnode != nullptr)
				que.push(__node->_M_lnode);
			if(__node->_M_rnode != nullptr)
				que.push(__node->_M_rnode);
		}//while
	}//levelorder(func)

};//class Tree

