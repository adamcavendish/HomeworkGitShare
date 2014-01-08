#pragma once

#include <utility>
#include <algorithm>
#include <stdexcept>
#include <exception>

#include "AVL_node_base.hpp"
#include "AVL_node.hpp"

template <typename Key, typename T, typename Compare = std::less<Key> >
class AVL
{
public://types
	typedef Key							key_type;
	typedef T							mapped_type;
	typedef std::pair<const Key, T>		value_type;
	typedef std::size_t					size_type;
	typedef std::ptrdiff_t				difference_type;
	typedef Compare						key_compare;
	typedef T &							reference;
	typedef const T &					const_reference;
	typedef T *							pointer;
	typedef const T *					const_pointer;
	typedef //iterator;
	typedef //const_iterator;

private: //members
	AVL_node_base * _M_node;
	Compare			_M_comp;

public://functions
	explicit
	AVL(const Compare & comp = Compare()) :
		_M_node(nullptr),
		_M_comp(comp)
	{}//default constructor

	AVL(const AVL & rhs) :
		_M_node(nullptr),
		_M_comp(rhs._M_comp)
	{ this->_M_insert_unique(rhs.begin(), rhs.end()); }
	//copy constructor

	AVL(AVL && rhs) :
		_M_node(rhs._M_node),
		_M_comp(rhs._M_comp)
	{ rhs._M_node = nullptr; }
	//move constructor

	template <typename InputIt>
	AVL(InputIt first, InputIt last, const Compare & comp = Compare()) :
		_M_node(nullptr),
		_M_comp(comp)
	{ this->_M_insert_unique(first, last); }

	AVL(std::initializer_list<value_type> init
			const Compare & comp = Compare()) :
		_M_node(nullptr),
		_M_comp(comp)
	{ this->_M_insert_unique(first, last); }

	~AVL() {
		this->_M_clear();
	}//destructor

	AVL &
	operator=(const AVL & rhs) {
		if(this == &rhs)
			return (*this);

		this->_M_clear();
		this->_M_insert_unique(rhs.begin(), rhs.end());
		return (*this);
	}//copy assignment

	AVL &
	operator=(AVL && rhs) {
		if(this == &rhs)
			return (*this);

		this->_M_node = rhs._M_node;
		this->_M_comp = std::forward<Compare>(rhs._M_comp);
		return (*this);
	}//move assignment

	/**
	 * --------------------------------------------------
	 *  Element Access
	 * --------------------------------------------------
	 */
	T &
	operator[](const Key & key);

	T &
	operator[](Key && key);

	/**
	 * --------------------------------------------------
	 *  Iterators
	 * --------------------------------------------------
	 */
	iterator
	begin();

	const_iterator
	begin() const;

	iterator
	end();

	const_iterator
	end() const;

	/**
	 * --------------------------------------------------
	 *  Capacity
	 * --------------------------------------------------
	 */
	bool
	empty() const;

	size_type
	size() const;

	/**
	 * --------------------------------------------------
	 *  Modifiers
	 * --------------------------------------------------
	 */
	void
	clear();

	std::pair<iterator, bool>
	insert(const value_type & value);

	template <typename InputIt>
	void
	insert(InputIt first, InputIt last)

	void
	insert(std::initializer_list<value_type> ilist);

	iterator
	erase(const_iterator pos);

	iterator
	erase(const_iterator first, const_iterator last);

	void
	swap(AVL & other);

	/**
	 * --------------------------------------------------
	 *  LOOK UP
	 * --------------------------------------------------
	 */
	iterator
	find(const Key & key);

	const_iterator
	find(const Key & key) const;

private: //functions

};//AVL

