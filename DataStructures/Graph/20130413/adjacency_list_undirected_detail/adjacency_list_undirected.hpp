#pragma once

#include <vector>
#include <list>
#include <string>
#include <utility>

#include <stdexcept>
#include <exception>

#include "../Visitor.hpp"

static_assert(__cplusplus >= 201103L, "Compile with -std=c++11");

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
class adjacency_list_undirected
{
public://types
	typedef std::size_t							size_type;

	typedef std::vector<std::list<
		std::pair<size_type, EdgeInfo> > >		content_type;

	typedef content_type::iterator				vertex_iterator;
	typedef content_type::const_iterator		const_vertex_iterator;

	typedef std::list<std::pair<
		size_type, EdgeInfo> >::iterator		edge_iterator;
	typedef std::list<std::pair<
		size_type, EdgeInfo> >::const_iterator	const_edge_iterator;

private://members
	content_type M_list;
	std::vector<VertexInfo> M_vertex;
	GraphInfo M_info;

	size_type M_vertex_size;
	size_type M_edge_size;

public://functions
	adjacency_list_undirected() :
		M_list(),
		M_vertex(),
		M_info(),
		M_vertex_size(0),
		M_edge_size(0)
	{}//default constructor

	explicit
	adjacency_list_undirected(const adjacency_list_undirected & L_rhs) :
		M_list(L_rhs.M_list),
		M_vertex_size(L_rhs.M_vertex),
		M_info(L_rhs.M_info),
		M_vertex_size(L_rhs.M_vertex_size),
		M_edge_size(L_rhs.M_edge_size)
	{}//copy constructor

	explicit
	adjacency_list_undirected(const GraphInfo & L_g) :
		M_list(),
		M_vertex(),
		M_info(L_g),
		M_vertex_size(0),
		M_edge_size(0)
	{}//constructor(GraphInfo)

	explicit
	adjacency_list_undirected(const size_type L_vertex_size) :
		M_list(L_vertex_size),
		M_vertex(L_vertex_size),
		M_info(),
		M_vertex_size(L_vertex_size),
		M_edge_size(0)
	{
		for(auto L_row_iter = 0lu;
				L_row_iter < this->M_vertex_size;
				++L_row_iter)
		{
			this->M_list[L_row_iter].resize(
					this->M_vertex_size - L_row_iter);
		}//for
	}//constructor(vertex_size)

	explicit
	adjacency_list_undirected(
			const size_type L_vertex_size,
			const GraphInfo & L_g) :
		M_list(L_vertex_size),
		M_vertex(L_vertex_size),
		M_info(L_g),
		M_vertex_size(L_vertex_size),
		M_edge_size(0)
	{
		for(auto L_row_iter = 0lu;
				L_row_iter < this->M_vertex_size;
				++L_row_iter)
		{
			this-M_list[L_row_iter].resize(
					this->M_vertex_size - L_row_iter);
		}//for
	}//constructor(vertex_size, GraphInfo)

	adjacency_list_undirected &
	operator=(const adjacency_list_undirected & L_rhs) {
		if(&L_rhs == this)
			return (*this);

		this->M_list = L_rhs.M_list;
		this->M_vertex = L_rhs.M_vertex;
		this->M_info = L_rhs.M_info;
		this->M_vertex_size = L_rhs.M_vertex_size;
		this->M_edge_size = L_rhs.M_edge_size;

		return (*this);
	}//assign operator

	size_type
	vertex_num() const
	{ return this->M_vertex_size; }

	size_type
	edge_num() const
	{ return this->M_edge_size; }
	
	bool
	add_edge(
			const size_type L_source,
			const size_type L_target,
			const EdgeInfo & L_info = EdgeInfo());

	bool
	remove_edge(
			const size_type L_source,
			const size_type L_target);

	vertex_iterator
	add_vertex(const VertexInfo & L_info = VertexInfo());

	bool
	remove_vertex(const size_type L_vertex_id);

	std::pair<bool, VertexInfo>
	get_vertex(const size_type L_vertex_id) const {
		if(L_vertex_id < this->M_vertex_size)
			return std::make_pair(true, this->M_vertex[L_vertex_id]);
		return std::make_pair(false, VertexInfo());
	}//get_vertex(vertex_id)

	std::pair<bool, EdgeInfo>
	get_edge(const size_type L_source, const size_type L_target) const {
		if(L_source >= this->M_vertex_size ||
				L_target >= this->M_vertex_size)
		{
			return std::make_pair(false, EdgeInfo());
		}//if

		if(L_source < L_target) {
			auto L_find_iter = std::find(
					this->M_list[L_source].begin(),
					this->M_list[L_source].end(),
					[=](const std::pair<size_type, EdgeInfo> & rhs) {
						return (rhs.first == L_target);
					});
			if(L_find_iter == this->M_list[L_source].end()) {
				return std::make_pair(false, EdgeInfo());
			} else {
				return std::make_pair(true, L_find_iter->second);
			}//if-else
		} else {
			auto L_find_iter = std::find(
					this->M_list[L_target].begin(),
					this->M_list[L_target].end(),
					[=](const std::pair<size_type, EdgeInfo> & rhs) {
						return (rhs.first == L_source);
					});
			if(L_find_iter == this->M_list[L_target].end()) {
				return std::make_pair(false, EdgeInfo());
			} else {
				return std::make_pair(true, L_find_iter->second);
			}//if-else
		}//if-else

		return std::make_pair(false, EdgeInfo());
	}//get_edge(source, target)

	bool
	put_vertex(const size_type L_vertex_id, const VertexInfo & L_info) {
		if(L_vertex_id >= this->M_vertex_size)
			return false;

		this->M_vertex[L_vertex_id] = L_info;
		return true;
	}//put_vertex(vertex_id, info)

	bool
	put_edge(
			const size_type L_source,
			const size_type L_target,
			const EdgeInfo & L_info)
	{
		if(L_source >= this->M_vertex_size ||
				L_target >= this->M_vertex_size)
		{
			return false;
		}//if

		if(L_source < L_target) {
			auto L_find_iter = std::find(
					this->M_list[L_source].begin(),
					this->M_list[L_source].end(),
					[=](const std::pair<size_type, EdgeInfo> & rhs) {
						return (rhs.first == L_target);
					});
			if(L_find_iter == this->M_list[L_source].end()) {
				return false;
			} else {
				L_find_iter->second = L_info;
				return true;
			}//if-else
		} else {
			auto L_find_iter = std::find(
					this->M_list[L_target].begin(),
					this->M_list[L_target].end(),
					[=](const std::pair<size_type, EdgeInfo> & rhs) {
						return (rhs.first == L_source);
					});
			if(L_find_iter == this->M_list[L_target].end()) {
				return false;
			} else {
				L_find_iter->second = L_info;
				return true;
			}//if-else
		}//if-else
		return false;
	}//put_edge(source, target, info)

void
breadth_first_traverse(Visitor & L_vis);

void
breadth_first_search(const size_type L_start_vertex, Visitor & L_vis);

private://functions
void
breadth_first_search_aux(
		const size_type L_start_vertex,
		bool L_visited[],
		Visitor & L_vis);

};//class adjacency_matrix_undirected

