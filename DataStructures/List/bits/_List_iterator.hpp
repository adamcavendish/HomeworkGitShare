#pragma once

#include "_List_node.hpp"

#include <cstddef>
#include <iterator>

namespace adamcavendish {
namespace data_structure {

namespace __detail {

/**
 * _List_iterator
 *
 * A List::iterator implementation
 * All the functions are operation overloads
 */
template <typename T>
struct _List_iterator
{
public: // member type
	typedef std::ptrdiff_t						difference_type;
	typedef std::bidirectional_iterator_tag		iterator_category;
	typedef T									value_type;
	typedef T *									pointer;
	typedef T &									reference;
private: // member type
	typedef _List_iterator<T>					_Self;
	typedef _List_node<T>						_Node;

public: // member functions
	explicit _List_iterator() : _M_node() {}
	explicit _List_iterator(_List_node_base * __x) : _M_node(__x) {}
	
	reference operator*() const {
		return static_cast<_Node *>(_M_node)->_M_data;
	}//operator*()
	pointer operator->() const {
		return std::addressof(static_cast<_Node *>(_M_node)->_M_data);
	}//operator->()

	_Self & operator++() {
		_M_node = _M_node->_M_next;
		return (*this);
	}//operator++()
	_Self operator++(int) {
		_Self ret(*this);
		_M_node = _M_node->_M_next;
		return ret;
	}//operator++(int)
	_Self & operator--() {
		_M_node = _M_node->_M_prev;
		return (*this);
	}//operator--()
	_Self operator--(int) {
		_Self ret(*this);
		_M_node = _M_node->_M_prev;
		return ret;
	}//operator--(int)

	bool operator==(const _Self & __x) const {
		return _M_node == __x._M_node;
	}//operator==
	bool operator!=(const _Self & __x) const {
		return _M_node != __x._M_node;
	}//operator!=

public: // member variable
	_List_node_base * _M_node;
};//struct _List_iterator

/**
 * A List const_iterator implementation
 * All the functions are opration overloads.
 */
template <typename T>
struct _List_const_iterator
{
public:// member type
	typedef _List_iterator<T>					iterator;
	typedef std::ptrdiff_t						difference_type;
	typedef std::bidirectional_iterator_tag		iterator_category;
	typedef T									value_type;
	typedef const T *							pointer;
	typedef const T &							reference;
private:// member type
	typedef _List_const_iterator<T>				_Self;
	typedef const _List_node<T>					_Node;

public:// member functions
	explicit _List_const_iterator() : _M_node() {}
	explicit _List_const_iterator(const _List_node_base * __x) :
		_M_node(__x)
	{}
	explicit _List_const_iterator(const iterator & __x) :
		_M_node(__x._M_node)
	{}
	
	reference operator*() const {
		return static_cast<_Node *>(_M_node)->_M_data;
	}//operator*()
	pointer operator->() const {
		return std::addressof(static_cast<_Node *>(_M_node)->_M_data);
	}//operator->()

	_Self & operator++() {
		_M_node = _M_node->_M_next;
		return (*this);
	}//operator++()
	_Self operator++(int) {
		_Self ret(*this);
		_M_node = _M_node->_M_next;
		return ret;
	}//operator++(int)
	_Self & operator--() {
		_M_node = _M_node->_M_prev;
		return (*this);
	}//operator--()
	_Self operator--(int) {
		_Self ret(*this);
		_M_node = _M_node->_M_prev;
		return ret;
	}//operator--(int)

	bool operator==(const _Self & __x) const {
		return _M_node == __x._M_node;
	}//operator==(__x)
	bool operator!=(const _Self & __x) const {
		return _M_node != __x._M_node;
	}//operator!=(__x)
	
public:// member variables
	const _List_node_base * _M_node;
};//struct _List_const_iterator

template <typename T>
inline bool
operator==(const _List_iterator<T> & __one,
		const _List_const_iterator<T> & __two)
{
	return __one._M_node == __two._M_node;
}//operator==(iterator, const_iterator)

template <typename T>
inline bool
operator!=(const _List_iterator<T> & __one,
		const _List_const_iterator<T> & __two)
{
	return __one._M_node != __two._M_node;
}//operator!=(iterator, const_iterator)

}// namespace __detail

}// namespace data_structure
}// namespace adamcavendish

