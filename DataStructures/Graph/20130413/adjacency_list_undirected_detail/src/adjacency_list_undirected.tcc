#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include <iterator>
#include <queue>

#include "../adjacency_list_undirected.hpp"
#include "../../Visitor.hpp"

static_assert(__cplusplus >= 201103L, "Compile with -std=c++11");

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_list_undirected::add_edge(
		const size_type L_source,
		const size_type L_target,
		const EdgeInfo & L_info)
{
	if(L_source >= this->M_vertex_size || L_target >= this->M_vertex_size) {
		std::throw_with_nested(std::out_of_range(std::string(
						"adjacency_list_undirected error: "
						"add_edge() out of range.")));
	}//if

	if(L_source < L_target) {
		auto L_find_iter = std::find(
				this->M_list[L_source].begin(),
				this->M_list[L_source].end(),
				[=](const std::pair<size_type, EdgeInfo> & rhs) {
					return (rhs.first == L_target);
				});
		if(L_find_iter != this->M_list[L_source].end()) {
			return false;
		} else {
			this->M_list.push_back(std::make_pair(L_target, L_info));
			return true;
		}//if-else
	} else {
		auto L_find_iter = std::find(
				this->M_list[L_target].begin(),
				this->M_list[L_target].end(),
				[=](const std::pair<size_type, EdgeInfo> & rhs) {
					return (rhs.first == L_source);
				});
		if(L_find_iter != this->M_list[L_target].end()) {
			return false;
		} else {
			this->M_list.push_back(std::make_pair(L_source, L_info));
			return true;
		}//if-else
	}//if-else

	return false;
}//add_edge(source, target, info)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_list_undirected::remove_edge(
		const size_type L_source,
		const size_type L_target)
{
	if(L_source >= this->M_vertex_size || L_target >= this->M_vertex_size) {
		std::throw_with_nested(std::out_of_range(std::string(
						"adjacency_matrix_undirected error: "
						"remove_edge() out of range.")));
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
			this->M_list[L_source].erase(L_find_iter);
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
			this->M_list[L_target].erase(L_find_iter);
			return true;
		}//if-else
	}//if-else
	return false;
}//remove_edge(iter)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
adjacency_matrix_undirected::size_type
adjacency_matrix_undirected::add_vertex(const VertexInfo & L_info)
{
	this->M_vertex.push_back(L_info);
	this->M_list.push_back(std::list<std::pair<size_type, EdgeInfo> >());
	++this->M_vertex_size;
	return this->M_vertex_size-1;
}//add_vertex(info)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_matrix_undirected::remove_vertex(const size_type L_vertex_id)
{
	if(L_vertex_id >= this->M_vertex_size) {
		std::throw_with_nested(std::out_of_range(std::string(
						"adjacency_list_undirected error: "
						"remove_vertex() out of range.")));
	}//if

	--this->M_vertex_size;

	auto L_iter = this->M_vertex.begin();
	std::advance(L_iter, L_vertex_id);
	this->M_vertex.erase(L_iter);

	L_iter = this->M_list.begin();
	std::advance(L_iter, L_vertex_id);
	this->M_list.erase(L_iter);

	return true;
}//remove_vertex(iter)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
void
adjacency_list_undirected::breadth_first_traverse(Visitor & L_vis)
{
	
}//breadth_first_traverse(vis)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
void
adjacency_list_undirected::breadth_first_search(
		size_type L_start_vertex,
		Visitor & L_vis)
{
}//breadth_first_search(start_vertex, vis)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
void
adjacency_list_undirected::breadth_first_search_aux(
		const size_type L_start_vertex,
		bool L_visited[],
		Visitor & L_vis)
{
	std::queue<size_type> L_que;

	L_vis.discover_vertex(L_start_vertex, *this);
	L_visited[L_start_vertex] = true;
	L_que.push(L_start_vertex);

	

	
}//breadth_first_search_aux(start_vertex, visited, vis)

