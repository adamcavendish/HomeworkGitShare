#pragma once

// STL
#include <utility>
#include <stdexcept>
#include <exception>

#include "BinarySearchTree.hpp"
#include "__bst_iterator.hpp"
#include "__bst_node.hpp"

namespace adamcavendish {
namespace container {

template <typename Key, typename Val, typename Compare>
__detail::__bst_node_base *
BinarySearchTree<Key, Val, Compare>::_M_copy(const __detail::__bst_node_base * __from) {
	__detail::__bst_node<Key, Val> * __ret_root;

	auto __preorder =
	[=, &__preorder](
			const __detail::__bst_node_base * __node,
			const __detail::__bst_node_base * __root)
	{
		if(__node != nullptr) {
			__root = new __detail::__bst_node<Key, Val>(
					static_cast<__detail::__bst_node<Key, Val> *>(__node)->_M_node);
			__preorder(__node->_M_left, __root->_M_left);
			__preorder(__node->_M_right, __root->_M_right);
		}//if
	};//lambda __preorder

	__preorder(__from, __ret_root);

	return static_cast<__detail::__bst_node_base *>(__ret_root);
}//_M_copy(__from)

template <typename Key, typename Val, typename Compare>
std::pair<typename BinarySearchTree<Key, Val, Compare>::iterator, bool>
BinarySearchTree<Key, Val, Compare>::_M_insert(const std::pair<Key, Val> & __pair) {
	__detail::__bst_node_base * __node = this->_M_root;
	__detail::__bst_node_base * __node_prev = nullptr;

	while(true) {
		if(this->_M_compare(__node, __pair.first) == true) {
			__node_prev = __node;
			__node = __node->_M_right;
			if(__node == nullptr) {
				__node = static_cast<__detail::__bst_node_base *>(
						new __detail::__bst_node<Key, Val>(__pair));
				__node_prev->_M_right = __node;
				return std::make_pair(iterator(__node), true);
			}//if
		} else if(this->_M_compare(__pair.first, __node) == true) {
			__node_prev = __node;
			__node = __node->_M_left;
			if(__node == nullptr) {
				__node = static_cast<__detail::__bst_node_base *>(
						new __detail::__bst_node<Key, Val>(__pair));
				__node_prev->_M_left = __node;
				return std::make_pair(iterator(__node), true);
			}//if
		} else {
			return std::make_pair(iterator(__node), false);
		}//if-else
	}//while

	return std::make_pair(this->end(), false);
}//_M_insert(__pair)

template <typename Key, typename Val, typename Compare>
std::pair<typename BinarySearchTree<Key, Val, Compare>::iterator, bool>
BinarySearchTree<Key, Val, Compare>::_M_insert(std::pair<Key, Val> && __pair) {
	__detail::__bst_node_base * __node = this->_M_root;
	__detail::__bst_node_base * __node_prev = nullptr;

	while(true) {
		if(this->_M_compare(__node, __pair.first) == true) {
			__node_prev = __node;
			__node = __node->_M_right;
			if(__node == nullptr) {
				__node = static_cast<__detail::__bst_node_base *>(
						new __detail::__bst_node<Key, Val>(std::forward<std::pair<Key, Val> >(__pair)));
				__node_prev->_M_right = __node;
				return std::make_pair(iterator(__node), true);
			}//if
		} else if(this->_M_compare(__pair.first, __node) == true) {
			__node_prev = __node;
			__node = __node->_M_left;
			if(__node == nullptr) {
				__node = static_cast<__detail::__bst_node_base *>(
						new __detail::__bst_node<Key, Val>(std::forward<std::pair<Key, Val> >(__pair)));
				__node_prev->_M_left = __node;
				return std::make_pair(iterator(__node), true);
			}//if
		} else {
			return std::make_pair(iterator(__node), false);
		}//if-else
	}//while

	return std::make_pair(this->end(), false);
}//_M_insert(__pair)

}//namespace container
}//namespace adamcavendish

