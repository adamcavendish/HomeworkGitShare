#pragma once

/**
 *  Thanks to Wikipedia:
 *  http://en.wikipedia.org/wiki/XOR_linked_list
 *
 *	0^0 = 0
 *	A^0 = A
 *	A^A = 0
 *	A^B = B^A
 *	(A^B)^A = B
 *	(B^A)^B = A
 *
 *	nextprev = next ^ prev
 *	next = nextprev ^ prev
 *	prev = nextprev ^ next
 *	
 *	So, if we set head and tail to 0, it's ok to 
 *	traverse the whole list
 */

struct _xorlist_node_base
{
	_xorlist_node_base * _M_nextprev;
	
	explicit
	_xorlist_node_base() :
		_M_nextprev(nullptr)
	{}
};//struct _xorlist_node_base

template <typename T>
struct _xorlist_node : public _xorlist_node_base
{
	T _M_data;

	_xorlist_node(const T & __x) :
		_M_data(__x)
	{}
};//struct _xorlist_node

template <typename T>
class xorlist : protected _xorlist_node_base
{
	typedef xorlist<T>							_Self;
	typedef _xorlist_node_base					_Base;
public:	// member types
	typedef T									value_type;
	typedef T *									pointer;
	typedef const T *							const_pointer;
	typedef T &									reference;
	typedef const T &							const_reference;
	typedef _xorlist_node<T>					node_type;
private: // member variables
	_Base * _M_trav_next;
	_Base * _M_trav_prev;
public:
	explicit
	xorlist() :
		_M_trav_next(nullptr),
		_M_trav_prev(nullptr)
	{}

	void push_front(const value_type & __x)
	{
		node_type * _node = _M_create_node(__x);

		if(this->_M_nextprev == nullptr) {
			// if the list is empty
			this->_M_nextprev = (_Base *)(0); // let &head = 0
			_node->_M_nextprev = (_Base *)(0);

			_M_trav_next = _M_trav_prev = _node;
		} else {
			// if the list is not empty
			_node->_M_nextprev =
				(_Base *)((int)&(this->_M_nextprev) ^ (int)(_M_trav_prev));
			_M_trav_prev->_M_nextprev = 
				(_Base *)((int)_M_trav_prev->_M_nextprev ^ (int)&(this->_M_nextprev) ^ (int)_node);
			_M_trav_prev = _node;
		}//if-else
	}//push_front(value)

	void push_back(const value_type & __x)
	{
	}

	void pop_front()
	{
		node_type * __next = _M_trav_prev;
		node_type * __next2 = (_Base *)((int)_M_trav_prev->_M_nextprev ^ (int)&(this->_M_nextprev));
		node_type * __next3 = (_Base *)((int)__next2->_M_nextprev ^ (int));

		__next2->_M_nextprev = 
		_M_destroy_node(__next);
	}

	void pop_back()
	{}

	value_type front() const
	{
		return *_M_trav_prev;
	}//front()

	value_type back() const
	{
		return *_M_trav_next;
	}

private:
	node_type *
	_M_create_node(const value_type & __x)
	{
		return new node_type(__x);
	}//_M_create_node(__x)

	void
	_M_destroy_node(node_type * __x)
	{
		delete __x;
	}//_M_destroy_node(__x)

};//xorlist

