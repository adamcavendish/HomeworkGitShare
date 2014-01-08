#pragma once

#include "Slist.hpp"

template <typename DataType, typename ReferenceType, typename PointerType>
class Slist_iterator
{
private:
	// only insert_next() has access to private functions and variables
	//friend void Slist::insert_next(iterator position, const DataType & data);
	friend class Slist;
	
	typedef ReferenceType	reference;
	typedef PointerType		pointer;

	typedef Slist_iterator<DataType, DataType &, DataType *>				iterator;
	typedef Slist_iterator<DataType, const DataType &, const DataType *>	const_iterator;
	typedef Slist_iterator<DataType, ReferenceType, PointerType>			self;

	typedef Slist_node<DataType> node;

public: //functions
	Slist_iterator(node * nd, self * next) : _node(nd), _next(next) {}

	self & operator++() { this = this->_next; } // prefix++: ++i

	self operator++(int) { // suffix++: i++
		iterator cp(*this);
		this = this->_next;
		return cp;
	}//operator++(int)

	bool operator==(iterator & iter) const { return _node == iter->_node; }

	bool operator!=(iterator & iter) const { return _node != iter->_node; }

	reference operator*() const { return _node->getData(); }

	pointer operator->() const { return &(operator*()); }
	
	~Slist_iterator() { delete _node; delete _next; }
private: // functions
	Slist_iterator() {}	// default constructor

private: //variables
	node * _node;
	self * _next;
};//class Slist_iterator

