#pragma once

#include "../../List/List"

#include <iostream>

namespace adamcavendish {
namespace data_structure {

template <typename T, typename Container = List<T> >
class stack
{
public: // member types
	typedef Container							container_type;
	typedef typename Container::value_type		value_type;
	typedef typename Container::pointer			pointer;
	typedef typename Container::const_pointer	const_pointer;
	typedef typename Container::reference		reference;
	typedef typename Container::const_reference	const_reference;
	typedef typename Container::size_type		size_type;

protected: // member variables
	Container _M_container;

public:	// member functions
	/**
	 * ------------------------------------------------- 
	 *  Constructors, destructor, assignments
	 * ------------------------------------------------- 
	 */
	explicit stack(const Container & __cont) :
		_M_container(__cont)
	{}//default constructor

	explicit stack(const Container && __cont = Container()) :
		_M_container(std::move(__cont))
	{}//default constructor2 -- moving container

	stack(const stack & __other) :
		_M_container(__other._M_container)
	{}//copy constructor

	stack(stack && __other) :
		_M_container(std::move(__other._M_container))
	{}//move constructor

	~stack()
	{}//destructor

	stack & operator=(const stack & __other)
	{ _M_container = __other; }

	stack & operator=(stack && __other)
	{ _M_container = std::move(__other); }

	/**
	 * --------------------------------------------------
	 *  Element Access
	 * --------------------------------------------------
	 */
	reference top()
	{ return _M_container.front(); }

	const_reference top() const
	{ return _M_container.front(); }

	/**
	 * --------------------------------------------------
	 *  Capacity
	 * --------------------------------------------------
	 */
	bool empty() const
	{ return _M_container.empty(); }

	size_type size() const
	{ return _M_container.size(); }

	/**
	 * --------------------------------------------------
	 * Modifiers
	 * --------------------------------------------------
	 */
	void push(const T & value)
	{ _M_container.push_front(value); }
	void push(T && value)
	{ _M_container.push_front(std::move(value)); }

	template <typename ... _Args>
	void emplace(_Args && ... __args)
	{ _M_container.emplace_front(std::forward<_Args>(__args)...); }

	void pop()
	{ _M_container.pop_front(); }
	
	void swap(const stack & __other)
	{ swap(_M_container, __other._M_container); }

};//class stack

template <typename T, typename Container>
bool operator==(stack<T, Container> & lhs,
		stack<T, Container> & rhs)
{ return lhs._M_container == rhs._M_container; }

template <typename T, typename Container>
bool operator!=(stack<T, Container> & lhs,
		stack<T, Container> & rhs)
{ return !(lhs._M_container == rhs._M_container); }

template <typename T, typename Container>
bool operator<(stack<T, Container> & lhs,
		stack<T, Container> & rhs)
{ return lhs._M_container < rhs._M_container; }

template <typename T, typename Container>
bool operator<=(stack<T, Container> & lhs,
		stack<T, Container> & rhs)
{ return !(rhs._M_container < lhs._M_container); }

template <typename T, typename Container>
bool operator>(stack<T, Container> & lhs,
		stack<T, Container> & rhs)
{ return rhs._M_container < lhs._M_container; }

template <typename T, typename Container>
bool operator>=(stack<T, Container> & lhs,
		stack<T, Container> & rhs)
{ return !(lhs._M_container < rhs._M_container); }

}//namespace data_structure
}//namespace adamcavendish

