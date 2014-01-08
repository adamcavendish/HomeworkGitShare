#pragma once

// include
#include "../globals.hpp"
#include "detailed_globals.hpp"
#include "VertexIterator.hpp"

namespace adamcavendish {
namespace graph {
namespace detail {

template <
	typename VertexContainerType,
	typename EdgeContainerType,
	typename VertexProperties,
	typename EdgeProperties>
struct EdgeIterator
{
private: //types
	typedef EdgeIterator<
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

	typedef edge_properties &				reference;
	typedef edge_properties *				pointer;
public://members
	edge_container_iterator _M_iter;
	VertexIterator			_M_source_vertex;
	VertexIterator			_M_target_vertex;

public://functions
	EdgeIterator() :
		this->_M_iter(),
		this->_M_source_vertex(),
		this->_M_target_vertex()
	{}//default constructor

	EdgeIterator(const EdgeIterator & __rhs) :
		this->_M_iter(__rhs._M_iter),
		this->_M_source_vertex(__rhs._M_source_vertex),
		this->_M_target_vertex(__rhs._M_target_vertex)
	{}//copy constructor

#if __cplusplus >= 201103L
	EdgeIterator(EdgeIterator && __rhs) :
		this->_M_iter(std::move(__rhs._M_iter)),
		this->_M_source_vertex(std::move(__rhs._M_source_vertex)),
		this->_M_target_vertex(std::move(__rhs._M_target_vertex))
	{}
#endif//c++11

	EdgeIterator(const edge_container_iterator & __iter,
			const VertexIterator & __source_vertex,
			const VertexIterator & __target_vertex) :
		this->_M_iter(__iter),
		this->_M_source_vertex(__source_vertex),
		this->_M_target_vertex(__target_vertex)
	{}//constructor(edge_container_iterator, source_vertex, target_vertex)

	~EdgeIterator()
	{}//destructor

	reference
	operator*() const
	{ return (this->_M_iter).operator*(); }

	pointer
	operator->() const
	{ return (this->_M_iter).operator->(); }

	EdgeIterator &
	operator++() {
		++(this->_M_iter);
		return (*this);
	}//operator++()

	EdgeIterator
	operator++(int) {
		_Self __ret;
		++(this->_M_iter);
		return __ret;
	}//operator++(int)

	EdgeIterator &
	operator--() {
		--(this->_M_iter);
		return (*this);
	}//operator--()

	EdgeIterator
	operator--(int) {
		_Self __ret;
		--(this->_M_iter);
		return __ret;
	}//operator--(int)

	bool
	operator==(const EdgeIterator & __rhs) const
	{ return (this->_M_iter == __rhs._M_iter); }

	bool
	operator!=(const EdgeIterator & __rhs) const
	{ return !(this->operator==(__rhs)); }
};//struct EdgeIterator

template <
	typename VertexContainerType,
	typename EdgeContainerType,
	typename VertexProperties,
	typename EdgeProperties>
struct ConstEdgeIterator
{
private: //types
	typedef VertexIterator<
		VertexContainerType,
		EdgeContainerType,
		VertexProperties,
		EdgeProperties>						_Self;

	typedef VertexContainerType				vertex_container;
	typedef	EdgeContainerType				edge_container;
	typedef vertex_container::iterator		vertex_container_iterator;
	typedef edge_container::iterator		edge_container_iterator;

	typedef VertexProperties				vertex_properties;
	typedef EdgeProperties					edge_properties;

	typedef const edge_properties &			reference;
	typedef const edge_properties *			pointer;
private://members
	edge_container_iterator _M_iter;

public://functions
	reference
	operator*() const
	{ return (this->_M_iter).operator*(); }

	pointer
	operator->() const
	{ return (this->_M_iter).operator->(); }

	ConstEdgeIterator &
	operator++() {
		++(this->_M_iter);
		return (*this);
	}//operator++()

	ConstEdgeIterator
	operator++(int) {
		_Self __ret;
		++(this->_M_iter);
		return __ret;
	}//operator++(int)

	ConstEdgeIterator &
	operator--() {
		--(this->_M_iter);
		return (*this);
	}//operator--()

	ConstEdgeIterator
	operator--(int) {
		_Self __ret;
		--(this->_M_iter);
		return __ret;
	}//operator--(int)

	bool
	operator==(const ConstEdgeIterator & __rhs) const
	{ return (this->_M_iter == __rhs._M_iter); }

	bool
	operator!=(const ConstEdgeIterator & __rhs) const
	{ return !(this->operator==(__rhs)); }
};//class ConstEdgeIterator

}//namespace detail
}//namespace graph
}//namespace adamcavendish

