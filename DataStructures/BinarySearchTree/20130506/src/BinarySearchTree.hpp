#pragma once

#include <functional>
#include <utility>
#include <memory>
#include <iostream>

#include "__bst_node.hpp"
#include "__bst_iterator.hpp"

namespace adamcavendish {
namespace container {

template <typename Key, typename Val, typename Compare = std::less<Key> >
class BinarySearchTree
{
public://types
	typedef Key											key_type;
	typedef	Val											mapped_type;
	typedef std::pair<const Key, Val>					value_type;
	typedef std::size_t									size_type;
	typedef std::ptrdiff_t								difference_type;
	typedef Compare										key_compare;
	typedef value_type &								reference;
	typedef const value_type &							const_reference;
	typedef value_type *								pointer;
	typedef const value_type *							const_pointer;
	typedef __detail::__bst_iterator<Key, Val>			iterator;
	typedef __detail::__bst_const_iterator<Key, Val>	const_iterator;
private://types
	typedef __detail::__bst_node_base					_T_node_base;
	typedef __detail::__bst_node<Key, Val>				_T_node;
private://members
	_T_node_base * _M_root;
	Compare	_M_comp;

public://functions
	explicit
	BinarySearchTree(const Compare & __comp = Compare()) :
		_M_root(nullptr),
		_M_comp(__comp)
	{}//default constructor
	
	BinarySearchTree(const BinarySearchTree & __rhs) :
		_M_root(nullptr),
		_M_comp(__rhs._M_comp)
	{ _M_root = _M_copy(__rhs._M_root); }//copy constructor

	BinarySearchTree(BinarySearchTree && __rhs) :
		_M_root(std::forward<_T_node_base *>(__rhs._M_root)),
		_M_comp(std::forward<Compare>(__rhs._M_comp))
	{}//move constructor

	BinarySearchTree(
			std::initializer_list<value_type> __il,
			const Compare & __comp = Compare()) :
		_M_root(nullptr),
		_M_comp(__comp)
	{ this->_M_insert_unique(__il.begin(), __il.end()); }
	//initializer_list constructor

	~BinarySearchTree()
	{
		//@todo
	}//destructor

	BinarySearchTree &
	operator=(const BinarySearchTree & __rhs) {
	//	this->clear(); @FIXME
		this->_M_comp = __rhs._M_comp;
		this->_M_root = this->_M_copy(__rhs._M_root);
	}//copy assignment

	BinarySearchTree &
	operator=(BinarySearchTree && __rhs) {
		this->_M_comp = std::forward<Compare>(__rhs._M_comp);
		this->_M_root = std::forward<_T_node_base *>(__rhs._M_root);
	}//move assignment

	/*
	 * --------------------------------------------------
	 * ELEMENT ACCESS
	 * --------------------------------------------------
	 */
#ifndef NDEBUG
	void
	traverse() {
		std::function<void(const _T_node_base *)> __preorder =
		[=, &__preorder](
				const _T_node_base * __node)
		{
			if(__node != nullptr) {
				auto __tmp = static_cast<const _T_node *>(__node)->_M_node;
				std::cout << __tmp.first << ' ' << __tmp.second << std::endl;
				__preorder(__node->_M_left);
				__preorder(__node->_M_right);
			}//if
		};//lambda __preorder

		__preorder(this->_M_root);
	}//traverse
#endif

	mapped_type &
	operator[](const key_type & __key) {
		std::pair<iterator, bool> __tmp;
		__tmp = this->_M_insert(std::make_pair(__key, mapped_type()));
		return ((*__tmp.first).second);
	}//operator[]

	iterator
	begin() {
		_T_node_base * __node = _M_root;
		if(__node == nullptr)
			return iterator(nullptr);
		while(__node->_M_left != nullptr)
			__node = __node->_M_left;
		return iterator(__node);
	}//begin()

	const_iterator
	begin() const {
		_T_node_base * __node = _M_root;
		if(__node == nullptr)
			return const_iterator(nullptr);
		while(__node->_M_left != nullptr)
			__node = __node->_M_left;
		return const_iterator(__node);
	}//begin() const

	iterator
	end()
	{ return iterator(nullptr); }//end()

	const_iterator
	end() const
	{ return const_iterator(nullptr); }//end() const

	/*
	 * --------------------------------------------------
	 *  CAPACITY
	 * --------------------------------------------------
	 */
	bool
	empty() const {
		return (this->_M_root->_M_left == nullptr
				&& this->_M_root->_M_right == nullptr);
	}//empty() const

	size_type
	size() const {
		size_type __cnt = 0;

		std::function<void(const _T_node_base *, size_type &)> __preorder =
		[=, &__preorder](
				const _T_node_base * __node,
				size_type & __counter)
		{
			if(__node != nullptr) {
				++__counter;
				__preorder(__node->_M_left, __counter);
				__preorder(__node->_M_right, __counter);
			}//if
		};//lambda __preorder

		__preorder(this->_M_root, __cnt);
		return __cnt;
	}//size() const

	/*
	 * --------------------------------------------------
	 *  MODIFIERS
	 * --------------------------------------------------
	 */
	void
	clear()
	{
		//@TODO
	}

	std::pair<iterator, bool>
	insert(const value_type & __pair)
	{ return this->_M_insert(__pair); }

	std::pair<iterator, bool>
	insert(value_type && __pair)
	{ return this->_M_insert(std::forward<value_type>(__pair)); }

	iterator
	erase(const_iterator __pos)
	{ return this->_M_erase(__pos); }

private://functions
	inline bool
	_M_compare(const _T_node * __lhs, const _T_node * __rhs)
	{ return _M_comp(__lhs->_M_node.first, __rhs->_M_node.first); }
	//_M_compare(lhs, rhs)

	inline bool
	_M_compare(const _T_node * __lhs, const Key & __rhs)
	{ return _M_comp(__lhs->_M_node.first, __rhs); }
	//_M_compare(__lhs, __rhs)

	inline bool
	_M_compare(const Key & __lhs, const _T_node * __rhs)
	{ return _M_comp(__lhs, __rhs->_M_node.first); }
	//_M_compare(__lhs, __rhs)

	_T_node_base *
	_M_copy(const _T_node_base * __from);

	std::pair<iterator, bool>
	_M_insert(const value_type & __pair);

	std::pair<iterator, bool>
	_M_insert(value_type && __pair);

	template <typename Iter>
	void
	_M_insert_unique(Iter __bgn, Iter __end) {
		for(; __bgn != __end; ++__bgn)
			this->_M_insert(*__bgn);
	}//_M_insert_unique(__bgn, __end)

	iterator
	_M_erase(const_iterator __pos);
};//class BinarySearchTree

}//namespace container
}//namespace adamcavendish

