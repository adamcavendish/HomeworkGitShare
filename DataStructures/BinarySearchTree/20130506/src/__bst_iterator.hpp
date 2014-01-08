#pragma once

#include <utility>

#include "__bst_node.hpp"

namespace adamcavendish {
namespace container {
namespace __detail {

template <typename Key, typename Val>
struct __bst_iterator
{
//types
	typedef std::pair<Key, Val>			value_type;
	typedef std::pair<Key, Val> &		reference;
	typedef std::pair<Key, Val> *		pointer;

//members
	__bst_node_base * _M_node;

//functions
	__bst_iterator() :
		_M_node(nullptr)
	{}//default constructor

	__bst_iterator(const __bst_iterator & __rhs) :
		_M_node(__rhs._M_node)
	{}//copy constructor

	__bst_iterator(__bst_iterator && __rhs) :
		_M_node(std::forward<__bst_node_base *>(__rhs._M_node))
	{}//move constructor

	__bst_iterator(__bst_node_base * __rhs) :
		_M_node(__rhs)
	{}//constructor(__bst_node_base *)

	~__bst_iterator()
	{ this->_M_node = nullptr; }//destructor

	__bst_iterator &
	operator=(const __bst_iterator & __rhs) {
		this->_M_node = __rhs._M_node;
		return (*this);
	}//copy assignment

	__bst_iterator &
	operator=(__bst_iterator && __rhs) {
		this->_M_node = std::forward<__bst_node_base *>(__rhs._M_node);
		return (*this);
	}//move assignment

	reference
	operator*() const
	{ return static_cast<__bst_node<Key, Val> *>(this->_M_node)->_M_node; }

	pointer
	operator->() const {
		return std::addressof(
				static_cast<__bst_node<Key, Val> *>(this->_M_node)->_M_node);
	}//operator->() const

	__bst_iterator &
	operator++() {
		this->inc();
		return (*this);
	}//operator++()

	__bst_iterator
	operator++(int) {
		__bst_iterator __ret(*this);
		this->inc();
		return __ret;
	}//operator++(int)

	__bst_iterator &
	operator--() {
		this->dec();
		return (*this);
	}//operator--()

	__bst_iterator
	operator--(int) {
		__bst_iterator __ret(*this);
		this->dec();
		return __ret;
	}//operator--(int)

	bool
	operator==(const __bst_iterator & __rhs)
	{ return this->_M_node == __rhs._M_node; }

	bool
	operator!=(const __bst_iterator & __rhs)
	{ return this->_M_node != __rhs._M_node; }

private:// functions
	inline void
	inc() {
		if(this->_M_node->_M_right != nullptr) {
			this->_M_node = this->_M_node->_M_right;
			while(this->_M_node->_M_left != nullptr)
				this->_M_node = this->_M_node->_M_left;
		} else {
			if(this->_M_node == nullptr)
				return;
			if(this->_M_node->_M_parent == nullptr) {
				this->_M_node = nullptr;
				return;
			}//if

			while(this->_M_node == this->_M_node->_M_parent->_M_right) {
				this->_M_node = this->_M_node->_M_parent;
				if(this->_M_node->_M_parent == nullptr) {
					this->_M_node = nullptr;
					return;
				}//if
			}//while
			this->_M_node = this->_M_node->_M_parent;
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
};//struct __bst_iterator

template <typename Key, typename Val>
struct __bst_const_iterator
{
//types
	typedef std::pair<Key, Val>				value_type;
	typedef const std::pair<Key, Val> &		reference;
	typedef const std::pair<Key, Val> *		pointer;

//members
	__bst_node_base * _M_node;

//functions
	__bst_const_iterator() :
		_M_node(nullptr)
	{}//default constructor

	__bst_const_iterator(const __bst_const_iterator & __rhs) :
		_M_node(__rhs._M_node)
	{}//copy constructor

	__bst_const_iterator(__bst_const_iterator && __rhs) :
		_M_node(std::forward<__bst_node_base *>(__rhs._M_node))
	{}//move constructor

	__bst_const_iterator(const __bst_iterator<Key, Val> & __rhs) :
		_M_node(__rhs._M_node)
	{}//constructor(__bst_iterator)

	__bst_const_iterator(__bst_node_base * __rhs) :
		_M_node(__rhs)
	{}//constructor(__bst_node_base *)

	~__bst_const_iterator()
	{ _M_node = nullptr; }//destructor

	__bst_const_iterator &
	operator=(const __bst_const_iterator & __rhs)
	{ _M_node = __rhs._M_node; }

	__bst_const_iterator &
	operator=(__bst_const_iterator && __rhs)
	{ _M_node = std::forward<__bst_node_base *>(__rhs._M_node); }

	reference
	operator*() const
	{ return static_cast<__bst_node<Key, Val> *>(this->_M_node)->_M_node; }

	pointer
	operator->() const {
		return std::addressof(
				static_cast<__bst_node<Key, Val> *>(this->_M_node)->_M_node);
	}//operator->() const

	__bst_const_iterator &
	operator++() {
		this->inc();
		return (*this);
	}//operator++()

	__bst_const_iterator
	operator++(int) {
		__bst_const_iterator __ret(*this);
		this->inc();
		return __ret;
	}//operator++(int)

	__bst_const_iterator &
	operator--() {
		this->dec();
		return (*this);
	}//operator--()

	__bst_const_iterator
	operator--(int) {
		__bst_const_iterator __ret(*this);
		this->dec();
		return __ret;
	}//operator--(int)

	bool
	operator==(const __bst_const_iterator & __rhs)
	{ return this->_M_node == __rhs._M_node; }

	bool
	operator!=(const __bst_const_iterator & __rhs)
	{ return this->_M_node != __rhs._M_node; }

private:// functions
	inline void
	inc() {
		if(this->_M_node->_M_right != nullptr) {
			this->_M_node = this->_M_node->_M_right;
			while(this->_M_node->_M_left != nullptr)
				this->_M_node = this->_M_node->_M_left;
		} else {
			if(this->_M_node == nullptr)
				return;
			if(this->_M_node->_M_parent == nullptr) {
				this->_M_node = nullptr;
				return;
			}//if

			while(this->_M_node == this->_M_node->_M_parent->_M_right) {
				this->_M_node = this->_M_node->_M_parent;
				if(this->_M_node->_M_parent == nullptr) {
					this->_M_node = nullptr;
					return;
				}//if
			}//while
			this->_M_node = this->_M_node->_M_parent;
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
};//struct __bst_const_iterator

template <typename Key, typename Val>
inline bool
operator==(const __bst_iterator<Key, Val> & __lhs,
		const __bst_const_iterator<Key, Val> & __rhs)
{ return __lhs._M_node == __rhs._M_node; }

template <typename Key, typename Val>
inline bool
operator!=(const __bst_iterator<Key, Val> & __lhs,
		const __bst_const_iterator<Key, Val> & __rhs)
{ return __lhs._M_node != __rhs._M_node; }

}//namespace __detail
}//namespace container
}//namespace adamcavendish

