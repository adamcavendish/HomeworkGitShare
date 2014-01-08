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

const int NODE_END = -1;

template <typename T>
struct tree_node
{
	enum class DIRECT { ACCESS, LEFT, RIGHT };
	T _M_data;
	tree_node * _M_lchild;
	tree_node * _M_rchild;
	tree_node * _M_parent;
	DIRECT _M_direct;

	tree_node() :
		_M_data(T()),
		_M_lchild(nullptr),
		_M_rchild(nullptr),
		_M_parent(nullptr),
		_M_direct(ACCESS)
	{}

	tree_node(const T & __val) :
		_M_data(__val),
		_M_lchild(nullptr),
		_M_rchild(nullptr),
		_M_parent(nullptr)
		_M_direct(ACCESS)
	{}//T constructor
};//struct tree_node


template <typename T>
class Tree2
{
public:// public all the stuffs.

	// members
	tree_node<T> * _M_head;

	// functions
	
	Tree() = delete;

	Tree(std::initializer_list<T> li) {
		std::cout << "Using " << (li.end() - li.begin())
			<< " to initialize" << std::endl;

		auto __arr = li.begin(); // Hack it.
		auto __boundary = li.end() - li.begin();

		if(__arr[0] != NODE_END) {
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

			if(__arr[__left_tag] != NODE_END) {
				_M_insert_left(__node, __arr[__left_tag]);
				que_array.push(__left_tag);
				que_tree.push(__node->_M_lchild);
			}//if

			if(__arr[__right_tag] != NODE_END) {
				_M_insert_right(__node, __arr[__right_tag]);
				que_array.push(__right_tag);
				que_tree.push(__node->_M_rchild);
			}//if
		}//while
		
		// std::cout << std::endl;
	}//initializer_list constructor

	~Tree()
	{
		std::cout << "Memory Leaking..." << std::endl;
		std::cout << "Finished!" << std::endl;
	}//destructor

	void
	_M_create_head(const T & __val) {
		_M_head = new tree_node<T>(__val);
	}//_M_create_head(__val)
	
	void
	_M_insert_left(tree_node<T> * __parent, const T & __val) {
		__parent->_M_lchild = new tree_node<T>(__val);
		__parent->_M_lchild->_M_parent = __parent;
	}//_M_insert_left(__parent, __val)

	void
	_M_insert_right(tree_node<T> * __parent, const T & __val) {
		__parent->_M_rchild = new tree_node<T>(__val);
		__parent->_M_rchild->_M_parent = __parent;
	}//_M_insert_right(__parent, __val)

	void
	levelorder(std::function< void(T) > func) {
		if(_M_head == nullptr)
			return;

		std::queue<tree_node<T> *> que;
		que.push(_M_head);

		while(!que.empty()) {
			tree_node<T> * __node = que.front();
			func(__node->_M_data);
			que.pop();

			if(__node->_M_lchild != nullptr)
				que.push(__node->_M_lchild);
			if(__node->_M_rchild != nullptr)
				que.push(__node->_M_rchild);
		}//while
	}//levelorder(func)


};//class Tree

