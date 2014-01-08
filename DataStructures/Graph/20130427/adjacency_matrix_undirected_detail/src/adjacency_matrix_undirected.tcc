#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include <iterator>

#include "../adjacency_matrix_undirected.hpp"

static_assert(__cplusplus >= 201103L, "Compile with -std=c++11");

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_matrix_undirected::add_edge(
		const size_type L_source,
		const size_type L_target,
		const EdgeInfo & L_info)
{
	if(L_source >= this->M_vertex_size || L_target >= this->M_vertex_size) {
		std::throw_with_nested(std::out_of_range(std::string(
						"adjacency_matrix_undirected error: "
						"add_edge() out of range.")));
	}//if

	if(this->M_at(L_source, L_target).first == true) {
		return false;
	} else {
		this->M_at(L_source, L_target).first = true;
		this->M_at(L_source, L_target).second = L_info;
		++this->M_edge_size;

		return true;
	}//if-else

	return false;
}//add_edge(row, col, info)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_matrix_undirected::remove_edge(
		const size_type L_source,
		const size_type L_target)
{
	if(L_source >= this->M_vertex_size || L_target >= this->M_vertex_size) {
		std::throw_with_nested(std::out_of_range(std::string(
						"adjacency_matrix_undirected error: "
						"add_edge() out of range.")));
	}//if
	
	if(this->M_at(L_source, L_target) == true) {
		this->M_at(L_source, L_target).first = false;
		this->M_at(L_source, L_target).second = EdgeInfo();
		--this->M_edge_size;
		return true;
	} else {
		return false;
	}//if-else
}//remove_edge(iter)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
adjacency_matrix_undirected::size_type
adjacency_matrix_undirected::add_vertex(const VertexInfo & L_info)
{
	this->M_vertex.push_back(L_info);
	for(auto L_row_iter : this->M_matrix)
		L_row_iter.push_back(std::pair<bool, EdgeInfo>());
	++this->M_vertex_size;
	return this->M_vertex_size-1;
}//add_vertex(info)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_matrix_undirected::remove_vertex(const size_type L_vertex_id)
{
	if(L_vertex_id >= this->M_vertex_size) {
		std::throw_with_nested(std::out_of_range(std::string(
						"adjacency_matrix_undirected error: "
						"remove_vertex() out of range.")));
	}//if

	--this->M_vertex_size;

	auto L_iter = this->M_vertex.begin();
	std::advance(L_iter, L_vertex_id);

	this->M_vertex.erase(L_iter);

	L_iter = this->M_matrix.begin();
	std::advance(L_iter, L_vertex_id);
	this->M_matrix.erase(L_iter);

	for(auto L_row_cnt = 0lu;
			L_row_cnt < this->M_vertex_size;
			++L_row_cnt)
	{
		L_iter = this->M_matrix[L_row_cnt].begin();
		std::advance(L_iter, L_vertex_id);
		this->M_matrix[L_row_cnt].erase(L_iter);
	}//for
	return true;
}//remove_vertex(iter)

