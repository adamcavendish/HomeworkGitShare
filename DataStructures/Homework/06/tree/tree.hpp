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

	// LEVEL ORDER INPUT!!!!!!!
	Tree(std::initializer_list<T> li) {
		std::cout << "Using " << (li.end() - li.begin())
			<< " to initialize" << std::endl;

		auto __arr = li.begin(); // Hack it.
		auto __boundary = li.end() - li.begin();

		if(__arr[0] != NE) {
			_M_create_head(__arr[0]);
		} else {
			return;
		}//if-else

		std::queue<T> que_array;
		std::queue<tree_node<T> *> que_tree;
		que_array.push(0);
		que_tree.push(_M_head);

		while(!que_array.empty()){
			int __parent_tag = que_array.front();
			tree_node<T> * __node = que_tree.front();

			//std::cout << __arr[__parent_tag] << ' ';

			que_array.pop();
			que_tree.pop();

			int __left_tag = 2 * __parent_tag + 1;
			int __right_tag = __left_tag + 1;

			if(__right_tag > __boundary)
				break;

			if(__arr[__left_tag] != NE) {
				_M_insert_left(__node, __arr[__left_tag]);
				que_array.push(__left_tag);
				que_tree.push(__node->_M_lnode);
			}//if

			if(__arr[__right_tag] != NE) {
				_M_insert_right(__node, __arr[__right_tag]);
				que_array.push(__right_tag);
				que_tree.push(__node->_M_rnode);
			}//if
		}//while
		
		// std::cout << std::endl;
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

