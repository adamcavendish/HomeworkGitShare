#pragma once

// STL
#include <utility>
#include <stdexcept>
#include <exception>

#include "__bst_iterator.hpp"
#include "__bst_node.hpp"

namespace adamcavendish {
namespace container {

template <typename Key, typename Val, typename Compare = std::less<Key> >
class BinarySearchTree
{
public: // types
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

private://members
	__detail::__bst_node_base * _M_root;
	Compare	_M_comp;
public://functions
	explicit
	BinarySearchTree(const Compare & comp = Compare()) :
		_M_root(),
		_M_comp(comp)
	{}//default constructor
	
	explicit
	BinarySearchTree(const BinarySearchTree & __rhs) :
		_M_root(),
		_M_comp(__rhs._M_comp)
	{
		this->_M_root = _M_copy(__rhs._M_root);
	}//copy constructor

	explicit
	BinarySearchTree(BinarySearchTree && __rhs) :
		_M_root(std::move(__rhs._M_root)),
		_M_comp(std::move(__rhs._M_comp))
	{
		__rhs._M_root->_M_parent = nullptr;
		__rhs._M_root->_M_left = nullptr;
		__rhs._M_root->_M_right = nullptr;
	}//move constructor

	explicit
	BinarySearchTree(std::initializer_list<Val> __il,
			const Compare & comp = Compare()) :
		_M_root(),
		_M_comp(comp)
	{ this->_M_insert_unique(__il.begin(), __il.end()); }
	//initializer_list constructor
	
	BinarySearchTree &
	operator=(const BinarySearchTree & __rhs) {
		//@FIXME clear();
		this->_M_comp = __rhs._M_comp;
		this->_M_root = _M_copy(__rhs._M_root);
	}//operator=
	
	/*
	 * --------------------------------------------------
	 * ELEMENT ACCESS
	 * --------------------------------------------------
	 */
	Val &
	operator[](const Key & __key) {
		std::pair<iterator, bool> __tmp;
		__tmp = this->_M_insert(std::make_pair(__key, Val()));
		return __tmp.first->second;
	}//operator[]

	iterator
	begin() {
		__detail::__bst_node_base * __node = _M_root;
		while(__node->_M_left != nullptr)
			__node = __node->_M_left;
		return iterator(__node);
	}//begin()

	const_iterator
	begin() const {
		__detail::__bst_node_base * __node = _M_root;
		while(__node->_M_left != nullptr)
			__node = __node->_M_left;
		return const_iterator(__node);
	}//begin() const

	iterator
	end()
	{
		__detail::__bst_node_base * __ret = nullptr;
		__detail::__bst_iterator<Key, Val> __ret2(__ret);
		return __ret2;
	}//end()

	const_iterator
	end() const
	{ return nullptr; }

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

		auto __preorder =
		[=, &__preorder](
				const __detail::__bst_node_base * __node,
				size_type & __counter) {
			if(__node != nullptr) {
				++__counter;
				__preorder(__node->_M_left, __counter);
				__preorder(__node->_M_right, __counter);
			}//if
		};//lambda __preorder

		__preorder(this->_M_root);
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
	insert(const std::pair<Key, Val> & __pair)
	{ return this->_M_insert(__pair); }

	std::pair<iterator, bool>
	insert(std::pair<Key, Val> && __pair)
	{ return this->_M_insert(std::forward(__pair)); }

private://functions
	inline bool
	_M_compare(const __detail::__bst_node_base * const __lhs,
			const __detail::__bst_node_base * const __rhs)
	{
		return _M_comp(
				static_cast<__detail::__bst_node<Key, Val> *>(
					__lhs)->_M_node.first,
				static_cast<__detail::__bst_node<Key, Val> *>(
					__rhs)->_M_node.first);
	}//_M_compare(lhs, rhs)

	inline bool
	_M_compare(const __detail::__bst_node_base * const __lhs,
			const Key & __rhs) {
		return _M_comp(static_cast<const __detail::__bst_node<Key, Val> *>(
					__lhs)->_M_node.first, __rhs); 
	}//_M_compare(__lhs, __rhs)

	inline bool
	_M_compare(const Key & __lhs,
			const __detail::__bst_node_base * const __rhs) {
		return _M_comp(__lhs, static_cast<const __detail::__bst_node<Key, Val> *>(
				__rhs)->_M_node.first);
	}//_M_compare(__lhs, __rhs)

	__detail::__bst_node_base *
	_M_copy(const __detail::__bst_node_base * __from);

	std::pair<BinarySearchTree<Key, Val, Compare>::iterator, bool>
	_M_insert(const std::pair<Key, Val> & __pair);

	std::pair<iterator, bool>
	_M_insert(std::pair<Key, Val> && __pair);

	template <typename Iter>
	void
	_M_insert_unique(Iter __bgn, Iter __end) {
		while(__bgn++ != __end)
			this->_M_insert(*__bgn);
	}//_M_insert_unique(__bgn, __end)
};//class BinarySearchTree

}//namespace container
}//namespace adamcavendish

