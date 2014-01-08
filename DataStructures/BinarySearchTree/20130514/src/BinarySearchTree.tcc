#pragma once

namespace adamcavendish {
namespace container {

template <typename Key, typename Val, typename Compare>
typename BinarySearchTree<Key, Val, Compare>::_T_node_base *
BinarySearchTree<Key, Val, Compare>::_M_copy(const _T_node_base * __from) {
	_T_node * __ret_root = nullptr;
	_T_node * __ret_root_prev = nullptr;

	std::function<
		_T_node_base *(
				const _T_node_base *,
				_T_node_base *,
				_T_node_base *)
		> __preorder =
	[=, &__preorder](
			const _T_node_base * __node,
			_T_node_base * __new_root,
			_T_node_base * __root_prev)
	{
		if(__node != nullptr) {
			__new_root = new _T_node(
					static_cast<const _T_node *>(__node)->_M_node);
			__new_root->_M_parent = __root_prev;
			__new_root->_M_left =
				__preorder(__node->_M_left, __new_root->_M_left, __new_root);
			__new_root->_M_right =
				__preorder(__node->_M_right, __new_root->_M_right, __new_root);
			return __new_root;
		}//if
		return (_T_node_base *)(nullptr);
	};//lambda __preorder

	__ret_root = static_cast<_T_node *>(
			__preorder(__from, __ret_root, __ret_root_prev));

	return static_cast<_T_node_base *>(__ret_root);
}//_M_copy(__from)

template <typename Key, typename Val, typename Compare>
std::pair<typename BinarySearchTree<Key, Val, Compare>::iterator, bool>
BinarySearchTree<Key, Val, Compare>::_M_insert(const value_type & __pair) {
	_T_node * __node = static_cast<_T_node *>(this->_M_root);
	_T_node * __node_prev = nullptr;

	if(__node == nullptr) {
		this->_M_root = new _T_node(__pair);
		return std::make_pair(iterator(this->_M_root), true);
	}//if

	while(true) {
		if(this->_M_compare(__node, __pair.first) == true) {
			__node_prev = __node;
			__node = static_cast<_T_node *>(__node->_M_right);
			if(__node == nullptr) {
				__node = new _T_node(__pair);
				__node_prev->_M_right = __node;
				__node->_M_parent = __node_prev;
				return std::make_pair(iterator(__node), true);
			}//if
		} else if(this->_M_compare(__pair.first, __node) == true) {
			__node_prev = __node;
			__node = static_cast<_T_node *>(__node->_M_left);
			if(__node == nullptr) {
				__node = new _T_node(__pair);
				__node_prev->_M_left = __node;
				__node->_M_parent = __node_prev;
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
BinarySearchTree<Key, Val, Compare>::_M_insert(value_type && __pair) {
	_T_node * __node = static_cast<_T_node *>(this->_M_root);
	_T_node * __node_prev = nullptr;

	if(__node == nullptr) {
		this->_M_root = new _T_node(__pair);
		return std::make_pair(iterator(this->_M_root), true);
	}//if

	while(true) {
		if(this->_M_compare(__node, __pair.first) == true) {
			__node_prev = __node;
			__node = static_cast<_T_node *>(__node->_M_right);
			if(__node == nullptr) {
				__node = new _T_node(std::forward<value_type>(__pair));
				__node_prev->_M_right = __node;
				__node->_M_parent = __node_prev;
				return std::make_pair(iterator(__node), true);
			}//if
		} else if(this->_M_compare(__pair.first, __node) == true) {
			__node_prev = __node;
			__node = static_cast<_T_node *>(__node->_M_left);
			if(__node == nullptr) {
				__node = new _T_node(std::forward<value_type>(__pair));
				__node_prev->_M_left = __node;
				__node->_M_parent = __node_prev;
				return std::make_pair(iterator(__node), true);
			}//if
		} else {
			return std::make_pair(iterator(__node), false);
		}//if-else
	}//while

	return std::make_pair(this->end(), false);
}//_M_insert(__pair)

template <typename Key, typename Val, typename Compare>
typename BinarySearchTree<Key, Val, Compare>::iterator
BinarySearchTree<Key, Val, Compare>::_M_erase(const_iterator __pos) {
	iterator __ret(__pos._M_node);

	if(__pos._M_node->_M_left != nullptr) {
		if(__pos._M_node->_M_right != nullptr) {
			// Left && Right neither nullptr
			_T_node_base * __replace_node = __pos._M_node->_M_right;
			while(__replace_node->_M_left != nullptr)
				__replace_node = __replace_node->_M_left;

			bool __circular_check = false;
			if(__replace_node == __pos._M_node->_M_right) {
				__circular_check = true;
			} else {
				// move __replace_node from the tree:
				if(__replace_node->_M_parent->_M_left == __replace_node) {
					__replace_node->_M_parent->_M_left = nullptr;
				} else {
					__replace_node->_M_parent->_M_right = nullptr;
				}//if-else
			}//if-else

			// parent
			__replace_node->_M_parent = __pos._M_node->_M_parent;
			if(__pos._M_node->_M_parent != nullptr) {
				if(__pos._M_node->_M_parent->_M_left == __pos._M_node) {
					__pos._M_node->_M_parent->_M_left = __replace_node;
				} else {
					__pos._M_node->_M_parent->_M_right = __replace_node;
				}//if-else
			};

			// left
			__replace_node->_M_left = __pos._M_node->_M_left;
			if(__pos._M_node->_M_left != nullptr)
				__pos._M_node->_M_left->_M_parent = __replace_node;

			// right, and ... Prevent circular reference
			if(!__circular_check) {
				__replace_node->_M_right = __pos._M_node->_M_right;
				if(__pos._M_node->_M_right != nullptr)
					__pos._M_node->_M_right->_M_parent = __replace_node;
			}//if

			// Check if it's root
			if(__pos._M_node->_M_parent == nullptr)
				this->_M_root = __replace_node;
			// update iterator
			__ret = iterator(__replace_node);
		} else {
			// Left != nullptr && Right == nullptr
			_T_node_base * __replace_node = __pos._M_node->_M_left;

			// update iterator
			++__ret;

			// move __replace_node from the tree
			__pos._M_node->_M_left = nullptr;

			__replace_node->_M_parent = __pos._M_node->_M_parent;
			if(__pos._M_node->_M_parent != nullptr) {
				if(__pos._M_node->_M_parent->_M_left == __pos._M_node) {
					__pos._M_node->_M_parent->_M_left = __replace_node;
				} else {
					__pos._M_node->_M_parent->_M_right = __replace_node;
				}//if-else
			} else {
				// it's root node so update it
				this->_M_root = __replace_node;
			}//if-else
		}//if-else
	} else {
		if(__pos._M_node->_M_right != nullptr) {
			// Left == nullptr && Right != nullptr
			_T_node_base * __replace_node = __pos._M_node->_M_right;

			// update iterator
			++__ret;

			// move __replace_node from the tree
			__pos._M_node->_M_right = nullptr;

			__replace_node->_M_parent = __pos._M_node->_M_parent;
			if(__pos._M_node->_M_parent != nullptr) {
				if(__pos._M_node->_M_parent->_M_left == __pos._M_node) {
					__pos._M_node->_M_parent->_M_left = __replace_node;
				} else {
					__pos._M_node->_M_parent->_M_right = __replace_node;
				}//if-else
			} else {
				// it's root node so update it
				this->_M_root = __replace_node;
			}//if-else
		} else {
			// Left && Right both nullptr
			
			// update iterator
			++__ret;

			// move current node from tree
			if(__pos._M_node->_M_parent != nullptr) {
				if(__pos._M_node->_M_parent->_M_left == __pos._M_node) {
					__pos._M_node->_M_parent->_M_left = nullptr;
				} else {
					__pos._M_node->_M_parent->_M_right = nullptr;
				}//if-else
			} else {
				// it's root node so update it
				this->_M_root = nullptr;
			}//if-else
		}//if-else
	}//if-else
	delete __pos._M_node;

	return __ret;
}//_M_erase(__pos)

}//namespace container
}//namespace adamcavendish

