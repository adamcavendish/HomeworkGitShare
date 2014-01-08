#pragma once

#include "_List_iterator.hpp"
#include "_List_node.hpp"

#include <cstddef>
#include <memory>
#include <iterator>
#include <initializer_list>
#include <utility>

namespace adamcavendish {
namespace data_structure {

template <typename T>
class List : public __detail::_List_node_base
{
	typedef List<T>									_Self;
	typedef __detail::_List_node_base				_Base;
public: //member types
	typedef T										value_type;
	typedef	T *										pointer;
	typedef const T *								const_pointer;
	typedef T &										reference;
	typedef const T &								const_reference;
	typedef __detail::_List_iterator<T>				iterator;
	typedef __detail::_List_const_iterator<T>		const_iterator;
	typedef std::reverse_iterator<iterator>			reverse_iterator;
	typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
	typedef std::size_t								size_type;
	typedef	std::ptrdiff_t							difference_type;
	typedef	__detail::_List_node<T>					node_type;
private: // member variables
	std::allocator<node_type> _M_allocator;
public: // member functions
	/**
	 * --------------------------------------------------
	 *  Constructors, destructor and assignments
	 * --------------------------------------------------
	 */
	explicit
	List() {
		this->_M_prev = this;
		this->_M_next = this;
	}//default constructor

	explicit
	List(const List & __x) :
		_M_allocator(__x._M_allocator)
	{
		this->_M_prev = this;
		this->_M_next = this;
		_M_range_init(__x.begin(), __x.end());
	}//copy constructor

	explicit
	List(List && __x) :
		_M_allocator(std::move(__x._M_allocator))
	{}//move constructor

	explicit
	List(std::initializer_list<value_type> __x) {
		this->_M_prev = this;
		this->_M_next = this;
		_M_range_init(__x.begin(), __x.end());
	}//initializer_list constructor

	template <typename InputIterator>
	explicit
	List(InputIterator __first, InputIterator __last) {
		this->_M_prev = this;
		this->_M_next = this;
		_M_range_init(__first, __last);
	}//range-iterator constructor

	_Self &
	operator=(const List & __x) {
		if(this == &__x)
			return (*this);
		_M_range_fill(__x.begin(), __x.end());
		return (*this);
	}//defalt assignment

	_Self &
	operator=(List && __x) {
		if(this == &__x)
			return (*this);
		this->_M_prev = __x._M_prev;
		this->_M_next = __x._M_next;
		_M_allocator = std::move(__x._M_allocator);
		return (*this);
	}//move assignment

	/**
	 * --------------------------------------------------
	 *  Iterators
	 * --------------------------------------------------
	 */
	iterator
	begin() noexcept { return iterator(_M_next); }
	const_iterator
	begin() const noexcept { return const_iterator(_M_next); } 
	const_iterator
	cbegin() const noexcept { return const_iterator(_M_next); }

	iterator
	end() noexcept { return iterator(this); }
	const_iterator
	end() const noexcept { return const_iterator(this); }
	const_iterator
	cend() const noexcept { return const_iterator(this); }

	reverse_iterator
	rbegin() noexcept { return reverse_iterator(end()); }
	const_reverse_iterator
	rbegin() const noexcept { return const_reverse_iterator(end());	}
	const_reverse_iterator
	crbegin() const noexcept { return const_reverse_iterator(end()); }

	reverse_iterator
	rend() noexcept { return reverse_iterator(begin()); }
	const_reverse_iterator
	rend() const noexcept { return const_reverse_iterator(begin()); }
	const_reverse_iterator
	crend() const noexcept { return const_reverse_iterator(begin()); }

	/**
	 * --------------------------------------------------
	 *  Capacity
	 * --------------------------------------------------
	 */
	bool empty() const noexcept {
		return this->_M_next == this;
	}//empty()

	size_type size() const noexcept {
		return std::distance(begin(), end());
	}//size()

	size_type max_size() const noexcept {
		return _M_allocator.max_size();
	}//max_size()

	/**
	 * --------------------------------------------------
	 *  Operations
	 * --------------------------------------------------
	 */
	reference
	front() {
		return *begin();
	}//front()
	const_reference
	front() const {
		return *begin();
	}//front() const

	reference
	back() {
		iterator ret(end());
		return *(--ret);
	}//back()
	const_reference
	back() const {
		const_iterator ret(end());
		return *(--ret);
	}//back() const

	void push_front(const value_type & __x) {
		_M_insert(begin(), __x);
	}//push_front(value)
	void push_front(value_type && __x) {
		_M_insert(begin(), std::move(__x));
	}//push_front(value) -- move
	template <typename ... Args_t>
	void emplace_front(Args_t && ... __arg) {
		_M_insert(begin(), std::forward<Args_t>(__arg)...);
	}//emplace_front(value) -- variadic

	void pop_front() {
		_M_erase(iterator(this->_M_next));
	}//pop_front()

	void push_back(const value_type & __x) {
		_M_insert(end(), __x);
	}//push_back(value)
	void push_back(value_type && __x) {
		_M_insert(end(), std::move(__x));
	}//push_back(value) -- move
	template <typename ... Args_t>
	void emplace_back(Args_t && ... __arg) {
		_M_insert(end(), std::forward<Args_t>(__arg)...);
	}//emplace_back(value) -- variadic

	void pop_back() {
		_M_erase(iterator(this->_M_prev));
	}//pop_back()

	iterator insert(iterator __pos, const value_type & __x) {
		node_type * __tmp = _M_create_node(__x);
		_M_insert(__pos, __x);
		return __tmp;
	}//insert(__pox, __x)

	iterator insert(iterator __pos, value_type && __x)  {
		node_type * _node = _M_create_node(std::move(__x));
		_node->_M_next = __pos._M_node;
		_node->_M_prev = __pos._M_node->_M_prev;
		__pos._M_node->_M_prev->_M_next = _node;
		__pos._M_node->_M_prev = _node;

		return _node;
	}//insert(__pos, __x) -- move

	void insert(iterator __pos, std::initializer_list<value_type> __ll) {
		insert(__pos, __ll.begin(), __ll.end());
	}//insert(__pos, initializer_list)

	void insert(iterator __pos, size_type __n, const value_type & __x) {
		_Self __tmp(__pos, __n, __x);
		splice(__pos, __tmp);
	}//insert(__pos, __n, __x)

	template <typename InputIterator>
	void insert(iterator __pos,
			InputIterator __first, InputIterator __last)
	{
		_Self __tmp(__first, __last);
		splice(__pos, __tmp);
	}//insert(__pos, __first, __last)

	iterator erase(iterator __position) {
		iterator __tmp(__position);
		++__tmp;
		_M_erase(__position);
		return __tmp;
	}//erase(__position)

	void erase(iterator __first, iterator __last) {
		while(__first != __last)
			__first = erase(__first);
		
	}//erase(__first, __last)
	
	void splice(iterator __pos, List<value_type> & __x) {
		splice(__pos, std::move(__x));
	}//splice(__pos, __x)
	void splice(iterator __pos, List<value_type> && __x);

private: //member functions
	template <typename... Args_t>
	node_type * _M_create_node(Args_t... __arg);
	inline void _M_destroy_node(iterator __x);

	template <typename InputIterator>
	void _M_range_init(InputIterator __first, InputIterator __last);

	template <typename InputIterator>
	void _M_range_fill(InputIterator __first, InputIterator __last);

	template <typename... Args_t>
	void _M_insert(iterator __pos, Args_t && ... __arg);

	void _M_erase(iterator __pos);

	void _M_transfer(iterator __pos, iterator __first, iterator __last);
	
};//class List

}//namespace data_structrue
}//namespace adamcavendish

