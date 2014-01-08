#pragma once

#include <utility>
#include <algorithm>
#include <stdexcept>
#include <exception>

#include "AVL_node.hpp"

template <typename Key, typename T, typename Compare = std::less<Key> >
class AVL

/**
 * --------------------------------------------------
 *  Element Access
 * --------------------------------------------------
 */
template <typename Key, typename T, typename Compare = std::less<Key> >
T &
AVL<Key, T, Compare>::operator[](const Key & key);

template <typename Key, typename T, typename Compare = std::less<Key> >
T &
AVL<Key, T, Compare>::operator[](Key && key);

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
