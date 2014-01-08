#pragma once

#include <vector>
#include <string>
#include <utility>

#include <stdexcept>
#include <exception>

static_assert(__cplusplus >= 201103L, "Compile with -std=c++11");

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
class adjacency_matrix_undirected
{
public://types
	typedef std::vector<std::vector<
		std::pair<bool, EdgeInfo> > > content_type;
	typedef std::vector<std::pair<bool, EdgeInfo> >::iterator

	typedef std::size_t size_type;
	
private://members
	content_type M_matrix;
	std::vector<VertexInfo> M_vertex;
	GraphInfo M_info;

	size_type M_vertex_size;
	size_type M_edge_size;

public://functions
	adjacency_matrix_undirected() :
		M_matrix(),
		M_vertex(),
		M_info(),
		M_vertex_size(0),
		M_edge_size(0)
	{}//default constructor

	explicit
	adjacency_matrix_undirected(const adjacency_matrix_undirected & L_rhs) :
		M_matrix(L_rhs.M_matrix),
		M_vertex_size(L_rhs.M_vertex),
		M_info(L_rhs.M_info),
		M_vertex_size(L_rhs.M_vertex_size),
		M_edge_size(L_rhs.M_edge_size)
	{}//copy constructor

	explicit
	adjacency_matrix_undirected(const GraphInfo & L_g) :
		M_matrix(),
		M_vertex(),
		M_info(L_g),
		M_vertex_size(0),
		M_edge_size(0)
	{}//constructor(GraphInfo)

	explicit
	adjacency_matrix_undirected(const size_type L_vertex_size) :
		M_matrix(L_vertex_size),
		M_vertex(L_vertex_size),
		M_info(),
		M_vertex_size(L_vertex_size),
		M_edge_size(0)
	{
		for(auto L_row_iter = 0lu;
				L_row_iter < this->M_vertex_size;
				++L_row_iter)
		{
			this-M_matrix[L_row_iter].resize(this->M_vertex_size - L_row_iter);
		}//for
	}//constructor(vertex_size)

	explicit
	adjacency_matrix_undirected(
			const size_type L_vertex_size,
			const GraphInfo & L_g) :
		M_matrix(L_vertex_size),
		M_vertex(L_vertex_size),
		M_info(L_g),
		M_vertex_size(L_vertex_size)
		M_edge_size(0)
	{
		for(auto L_row_iter = 0lu;
				L_row_iter < this->M_vertex_size;
				++L_row_iter)
		{
			this-M_matrix[L_row_iter].resize(this->M_vertex_size - L_row_iter);
		}//for
	}//constructor(vertex_size, GraphInfo)

	adjacency_matrix_undirected &
	operator=(const adjacency_matrix_undirected & L_rhs) {
		if(&L_rhs == this)
			return (*this);

		this->M_matrix = L_rhs.M_matrix;
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

	size_type
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
		if(L_source >= this->M_vertex_size
				|| L_target >= this->M_vertex_size)
		{
			return std::make_pair(false, EdgeInfo());
		}//if
		return this->M_at(L_source, L_target);
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
		if(L_source >= this->M_vertex_size || L_target >= this->M_vertex_size)
			return false;
		
		this->M_at(L_source, L_target).second = L_info;
		return true;
	}//put_edge(source, target, info)

private://functions
	inline std::pair<bool, EdgeInfo> &
	M_at(const size_type L_row, const size_type L_col) const {
		if(L_row < L_col) {
			return this->M_matrix[L_row][L_col - L_row];
		} else {
			return this->M_matrix[L_col][L_row - L_col];
		}//if-else

		return std::pair<bool, EdgeInfo>();
	}//M_at(row, col)
};//class adjacency_matrix_undirected

