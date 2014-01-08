#pragma once

// STL
#include <utility>
// include
#include "../globals.hpp"
#include "detailed_globals.hpp"

namespace adamcavendish {
namespace graph {
namespace detail {

template <
	typename VertexNodeContainerType,
	typename EdgeNodeContainerType,
	typename VertexProperties,
	typename EdgeProperties>
struct VertexIterator
{
public: //types
	typedef VertexIterator<
		VertexNodeContainerType,
		EdgeNodeContainerType,
		VertexProperties,
		EdgeProperties>						_Self;

	typedef vertex_container::iterator		vertex_container_iterator;
	typedef edge_container::iterator		edge_container_iterator;

	typedef GraphType::VertexProperties		vertex_properties;
	typedef GraphType::EdgeProperties		edge_properties;

	typedef vertex_properties &				reference;
	typedef vertex_properties *				pointer;
public://members
	vertex_container_iterator _M_iter;

public://functions
	explicit
	VertexIterator() :
		this->_M_iter()
	{}//default constructor

	explicit
	VertexIterator(const VertexIterator & __rhs) :
		this->_M_iter(__rhs->_M_iter)
	{}//copy constructor

#if __cplusplus >= 201103L
	explicit
	VertexIterator(VertexIterator && __rhs) :
		this->_M_iter(std::move(__rhs->_M_iter))
	{}//move constructor
#endif//c++11
	
	explicit
	VertexIterator(const vertex_container_iterator & __rhs) :
		this->_M_iter(__rhs)
	{}//constructor(vertex_container_iterator)

	~VertexIterator()
	{}//destructor

	reference
	operator*() const
	{ return _M_iter->first; }

	pointer
	operator->() const
	{ return &(_M_iter->first); }

	VertexIterator &
	operator++() {
		++_M_iter;
		return (*this);
	}//operator++()

	VertexIterator
	operator++(int) {
		_Self __ret;
		++_M_iter;
		return __ret;
	}//operator++(int)

	VertexIterator &
	operator--() {
		--_M_iter;
		return (*this);
	}//operator--()

	VertexIterator
	operator--(int) {
		_Self __ret;
		--_M_iter;
		return __ret;
	}//operator--(int)

	bool
	operator==(const VertexIterator & __rhs) const
	{ return (_M_iter == __rhs._M_iter); }

	bool
	operator!=(const VertexIterator & __rhs) const
	{ return !(this->operator==(__rhs)); }
};//struct VertexIterator

template <
	typename VertexContainerType,
	typename EdgeContainerType,
	typename VertexProperties,
	typename EdgeProperties>
struct ConstVertexIterator
{
private: //types
	typedef ConstVertexIterator<
		VertexContainerType,
		EdgeContainerType,
		VertexProperties,
		EdgeProperties>						_Self;

	typedef VertexContainerType				vertex_container;
	typedef EdgeContainerType				edge_container;
	typedef vertex_container::iterator		vertex_container_iterator;
	typedef edge_container::iterator		edge_container_iterator;

	typedef VertexProperties				vertex_properties;
	typedef EdgeProperties					edge_properties;

	typedef const vertex_properties &		reference;
	typedef const vertex_properties *		pointer;
public://members
	vertex_container_iterator _M_iter;

public://functions
	explicit
	ConstVertexIterator() :
		this->_M_iter()
	{}//default constructor

	explicit
	ConstVertexIterator(const ConstVertexIterator & __rhs) :
		this->_M_iter(__rhs->_M_iter)
	{}//copy constructor

#if __cplusplus >= 201103L
	explicit
	ConstVertexIterator(ConstVertexIterator && __rhs) :
		this->_M_iter(std::move(__rhs->_M_iter))
	{}//move constructor
#endif//c++11

	explicit
	ConstVertexIterator(const vertex_container_iterator & __rhs) :
		this->_M_iter(__rhs)
	{}//constructor(vertex_container_iterator)

	~ConstVertexIterator()
	{}//destructor

	reference
	operator*() const
	{ return _M_iter->first; }

	pointer
	operator->() const
	{ return &(_M_iter->first); }

	ConstVertexIterator &
	operator++() {
		++_M_iter;
		return (*this);
	}//operator++()

	ConstVertexIterator
	operator++(int) {
		_Self __ret;
		++_M_iter;
		return __ret;
	}//operator++(int)

	ConstVertexIterator &
	operator--() {
		--_M_iter;
		return (*this);
	}//operator--()

	ConstVertexIterator
	operator--(int) {
		_Self __ret;
		--_M_iter;
		return __ret;
	}//operator--(int)

	bool
	operator==(const ConstVertexIterator & __rhs) const
	{ return (_M_iter == __rhs._M_iter); }

	bool
	operator!=(const ConstVertexIterator & __rhs) const
	{ return !(this->operator==(__rhs)); }
};//struct ConstVertexIterator

}//namespace detail
}//namespace graph
}//namespace adamcavendish

