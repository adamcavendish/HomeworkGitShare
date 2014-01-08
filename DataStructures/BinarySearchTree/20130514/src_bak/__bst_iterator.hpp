#pragma once

// STL
#include <memory>

#include "__bst_node.hpp"

namespace adamcavendish {
namespace container {
namespace __detail {

template <typename Key, typename Val>
class __bst_iterator;

template <typename Key, typename Val>
class __bst_const_iterator;

template <typename Key, typename Val>
inline bool
operator==(const __bst_iterator<Key, Val> & __lhs,
	const __bst_const_iterator<Key, Val> & __rhs);

template <typename Key, typename Val>
inline bool
operator!=(const __bst_iterator<Key, Val> & __lhs,
	const __bst_const_iterator<Key, Val> & __rhs);

template <typename Key, typename Val, typename Compare>
class BinarySearchTree;

struct __bst_iterator_base
{
	// members
	__bst_node_base * _M_node;

	__bst_iterator_base() :
		_M_node(nullptr)
	{}//default constructor

	__bst_iterator_base(const __bst_iterator_base & __rhs) :
		_M_node(__rhs._M_node)
	{}//copy constructor

	__bst_iterator_base(__bst_iterator_base && __rhs) :
		_M_node(std::move(_M_node))
	{}//move constructor

	__bst_iterator_base(__bst_node_base * __rhs) :
		_M_node(__rhs)
	{}//constructor(__bst_node_base)

	// functions
	inline void
	inc() {
		if(this->_M_node->_M_right != nullptr) {
			this->_M_node = this->_M_node->_M_right;
			while(this->_M_node->_M_left != nullptr)
				this->_M_node = this->_M_node->_M_left;
		} else {
			do {
				this->_M_node = this->_M_node->_M_parent;
			} while(this->_M_node != nullptr
					&& this->_M_node == this->_M_node->_M_parent->_M_right);
		}//if-else
	}//inc()

	inline void
	dec() {
		if(this->_M_node->_M_left != nullptr) {
			this->_M_node = this->_M_node->_M_left;
			while(this->_M_node->_M_right != nullptr)
				this->_M_node = this->_M_node->_M_right;
		} else {
			do {
				this->_M_node = this->_M_node->_M_parent;
			} while(this->_M_node != nullptr
					&& this->_M_node == this->_M_node->_M_parent->_M_left);
		}//if-else
	}//dec()
};//struct __bst_iterator_base

template <typename Key, typename Val>
class __bst_iterator
{
private://friends
	friend bool
	operator== <> (const __bst_iterator<Key, Val> & __lhs,
		const __bst_const_iterator<Key, Val> & __rhs);

	friend bool
	operator!= <> (const __bst_iterator<Key, Val> & __lhs,
		const __bst_const_iterator<Key, Val> & __rhs);

	template <typename Key_, typename Val_, typename Compare_>
	friend class BinarySearchTree;
public: //types
	typedef std::pair<Key, Val>				value_type;
	typedef std::pair<Key, Val> &			reference;
	typedef std::pair<Key, Val> *			pointer;
private://members
	__bst_iterator_base _M_iter;
public://functions
	explicit
	__bst_iterator() :
		_M_iter()
	{}//default constructor

	explicit
	__bst_iterator(const __bst_iterator & __rhs) :
		_M_iter(__rhs._M_iter)
	{}//copy constructor

	explicit
	__bst_iterator(__bst_iterator && __rhs) :
		_M_iter(std::move(__rhs._M_iter))
	{}//move constructor

	explicit
	__bst_iterator(__bst_node_base * __rhs) :
		_M_iter(__rhs)
	{}//constructor(__bst_node_base)

	__bst_iterator &
	operator=(const __bst_iterator & __rhs)
	{ _M_iter = __rhs._M_iter; }

	__bst_iterator &
	operator=(__bst_iterator && __rhs)
	{ _M_iter = __rhs._M_iter; }

	reference
	operator*() const {
		return static_cast<__bst_node<Key, Val> *>(
			this->_M_iter._M_node)->_M_node;
	}//operator*() const

	pointer
	operator->() const {
		return std::addressof(static_cast<__bst_node<Key, Val> *>(
					this->_M_iter._M_node)->_M_node);
	}//operator->() const

	__bst_iterator &
	operator++() {
		this->_M_iter.inc();
		return (*this);
	}//operator++()

	__bst_iterator
	operator++(int) {
		__bst_iterator __ret(*this);
		this->_M_iter.inc();
		return (*this);
	}//operator++(int)

	__bst_iterator &
	operator--() {
		this->_M_iter.dec();
		return (*this);
	}//operator--()

	__bst_iterator
	operator--(int) {
		__bst_iterator __ret(*this);
		this->_M_iter.dec();
		return (*this);
	}//operator--(int)

	bool
	operator==(const __bst_iterator & __rhs) const
	{ return this->_M_iter == __rhs._M_iter; }

	bool
	operator!=(const __bst_iterator & __rhs) const
	{ return this->_M_iter != __rhs._M_iter; }
};//class __bst_iterator

template <typename Key, typename Val>
class __bst_const_iterator
{
private: //friends
	friend bool
	operator== <> (const __bst_iterator<Key, Val> & __lhs,
		const __bst_const_iterator<Key, Val> & __rhs);

	friend bool
	operator!= <> (const __bst_iterator<Key, Val> & __lhs,
		const __bst_const_iterator<Key, Val> & __rhs);

	template <typename Key_, typename Val_, typename Compare_>
	friend class BinarySearchTree;
public: //types
	typedef std::pair<Key, Val>				value_type;
	typedef const std::pair<Key, Val> &		reference;
	typedef const std::pair<Key, Val> *		pointer;
private://members
	__bst_iterator_base _M_iter;
public://functions
	explicit
	__bst_const_iterator() :
		_M_iter()
	{}//default constructor

	explicit
	__bst_const_iterator(const __bst_const_iterator & __rhs) :
		_M_iter(__rhs->_M_iter)
	{}//copy constructor

	explicit
	__bst_const_iterator(__bst_node_base * __rhs) :
		_M_iter(__rhs)
	{}//constructor(__bst_node_base)

	explicit
	__bst_const_iterator(const __bst_iterator<Key, Val> & __rhs) :
		_M_iter(__rhs._M_iter)
	{}//constructor(__bst_iterator)

	reference
	operator*() const {
		return static_cast<__bst_node<Key, Val> *>(
			this->_M_iter->_M_node)->_M_node;
	}//operator*() const

	pointer
	operator->() const {
		return std::addressof(static_cast<__bst_node<Key, Val> *>(
					this->_M_iter->_M_node)->_M_node);
	}//operator->() const

	__bst_const_iterator &
	operator++() {
		this->_M_iter.inc();
		return (*this);
	}//operator++()

	__bst_const_iterator
	operator++(int) {
		__bst_iterator<Key, Val> __ret(*this);
		this->_M_iter.inc();
		return (*this);
	}//operator++(int)

	__bst_const_iterator &
	operator--() {
		this->_M_iter.dec();
		return (*this);
	}//operator--()

	__bst_const_iterator
	operator--(int) {
		__bst_iterator<Key, Val> __ret(*this);
		this->_M_iter.dec();
		return (*this);
	}//operator--(int)

	bool
	operator==(const __bst_const_iterator & __rhs) const
	{ return this->_M_iter == __rhs._M_iter; }

	bool
	operator!=(const __bst_const_iterator & __rhs) const
	{ return this->_M_iter != __rhs._M_iter; }
};//class __bst_const_iterator

template <typename Key, typename Val>
inline bool
operator==(const __bst_iterator<Key, Val> & __lhs,
		const __bst_const_iterator<Key, Val> & __rhs)
{ return __lhs._M_iter == __rhs._M_iter; }

template <typename Key, typename Val>
inline bool
operator!=(const __bst_iterator<Key, Val> & __lhs,
		const __bst_const_iterator<Key, Val> & __rhs)
{ return __lhs._M_iter != __rhs._M_iter; }

}//namespace __detail
}//namespace container
}//namespace adamcavendish

