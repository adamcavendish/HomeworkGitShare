#pragma once
static_assert(__cplusplus >= 201103L, "Compile with -std=c++11");

#include <algorithm>
#include <exception>
#include <stdexcept>
#include <string>
#include <iterator>
#include <queue>
#include <utility>

#include "../adjacency_matrix_directed.hpp"
#include "../../BFSVisitor.hpp"
#include "../../DFSVisitor.hpp"

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_matrix_directed<EdgeInfo, VertexInfo, GraphInfo>::add_edge(
		const size_type L_source,
		const size_type L_target,
		const EdgeInfo & L_info)
{
	if(L_source >= this->M_vertex_size || L_target >= this->M_vertex_size) {
		std::throw_with_nested(std::out_of_range(std::string(
						"adjacency_matrix_directed error: "
						"add_edge() out of range.")));
	}//if

	if(this->M_list[L_source][L_target].first == false) {
		this->M_list[L_source][L_target].first = true;
		this->M_list[L_source][L_target].second = L_info;
		return true;
	}//if

	return false;
}//add_edge(source, target, info)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_matrix_directed<EdgeInfo, VertexInfo, GraphInfo>::remove_edge(
		const size_type L_source,
		const size_type L_target)
{
	if(L_source >= this->M_vertex_size || L_target >= this->M_vertex_size) {
		std::throw_with_nested(std::out_of_range(std::string(
						"adjacency_matrix_undirected error: "
						"remove_edge() out of range.")));
	}//if

	if(this->M_list[L_source][L_target].first == true) {
		this->M_list[L_source][L_target].first = false;
		this->M_list[L_source][L_target].second = EdgeInfo();
		return true;
	}//if

	return false;
}//remove_edge(iter)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
typename adjacency_matrix_directed<EdgeInfo, VertexInfo, GraphInfo>::size_type
adjacency_matrix_directed<EdgeInfo, VertexInfo, GraphInfo>::add_vertex(const VertexInfo & L_info)
{
	this->M_vertex.push_back(L_info);

	std::pair<bool, EdgeInfo> L_def_pair;
	for(std::size_t i = 0; i < this->M_list.size(); ++i)
		this->M_list[i].push_back(L_def_pair);
	++this->M_vertex_size;

	this->M_list.push_back(
			std::vector<std::pair<bool, EdgeInfo> >(this->M_vertex_size));

	this->M_list[this->M_vertex_size-1][this->M_vertex_size-1].first = false;

	return this->M_vertex_size-1;
}//add_vertex(info)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_matrix_directed<EdgeInfo, VertexInfo, GraphInfo>::remove_vertex(const size_type L_vertex_id)
{
	if(L_vertex_id >= this->M_vertex_size) {
		std::throw_with_nested(std::out_of_range(std::string(
						"adjacency_matrix_directed error: "
						"remove_vertex() out of range.")));
	}//if

	--this->M_vertex_size;

	auto L_iter = this->M_vertex.begin();
	std::advance(L_iter, L_vertex_id);
	this->M_vertex.erase(L_iter);

	L_iter = this->M_list.begin();
	std::advance(L_iter, L_vertex_id);
	this->M_list.erase(L_iter);

	for(typename content_type::size_type i = 0; i < this->M_list.size(); ++i) {
		L_iter = this->M_list[i].begin();
		std::advance(L_iter, L_vertex_id);
		this->M_list[i].erase(L_iter);
	}//for

	return true;
}//remove_vertex(iter)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
std::pair<bool, EdgeInfo>
adjacency_matrix_directed<EdgeInfo, VertexInfo, GraphInfo>::get_edge(
		const size_type L_source,
		const size_type L_target) const
{
	if(L_source >= this->M_vertex_size ||
			L_target >= this->M_vertex_size)
	{
		return std::make_pair(false, EdgeInfo());
	}//if

	if(this->M_list[L_source][L_target].first == false) {
		return std::make_pair(false, EdgeInfo());
	} else {
		return std::make_pair(true, this->M_list[L_source][L_target].second);
	}//if-else

	return std::make_pair(false, EdgeInfo());
}//get_edge(source, target)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_matrix_directed<EdgeInfo, VertexInfo, GraphInfo>::put_edge(
			const size_type L_source,
			const size_type L_target,
			const EdgeInfo & L_info)
{
	if(L_source >= this->M_vertex_size ||
			L_target >= this->M_vertex_size)
	{
		return false;
	}//if

	this->M_list[L_source][L_target].second = L_info;

	return false;
}//put_edge(source, target, info)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_matrix_directed<EdgeInfo, VertexInfo, GraphInfo>::breadth_first_search_aux(
		const size_type L_start_vertex,
		bool L_visited[],
		BFSVisitor<adjacency_matrix_directed> & L_vis)
{
	std::queue<size_type> L_que;

	if(!L_vis.discover_vertex(L_start_vertex, *this))
		return false;
	L_visited[L_start_vertex] = true;
	L_que.push(L_start_vertex);

	while(!L_que.empty()) {
		size_type L_cur_vertex = L_que.front();
		L_que.pop();
		if(!L_vis.examine_vertex(L_cur_vertex, *this))
			return false;

		for(typename std::vector<std::pair<bool, EdgeInfo> >::size_type
			L_iter = 0,
			L_end = this->M_list[L_cur_vertex].size();
			L_iter != L_end;
			++L_iter)
		{
			if(this->M_list[L_cur_vertex][L_iter].first == false)
				continue;

			const size_type L_target_vertex = L_iter;
			if(!L_vis.examine_edge(L_cur_vertex, L_target_vertex, *this))
				return false;

			// not visited
			if(L_visited[L_target_vertex] == false) {
				L_visited[L_target_vertex] = true;
				if(!L_vis.tree_edge(L_cur_vertex, L_target_vertex, *this))
					return false;
				if(!L_vis.discover_vertex(L_target_vertex, *this))
					return false;
				L_que.push(L_target_vertex);
			} else {
				if(!L_vis.non_tree_edge(L_cur_vertex, L_target_vertex, *this))
					return false;
			}//if-else
		}//for
		
		if(!L_vis.finish_vertex(L_cur_vertex, *this))
			return false;
	}//while

	return true;
}//breadth_first_search_aux(start_vertex, visited, vis)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_matrix_directed<EdgeInfo, VertexInfo, GraphInfo>::depth_first_search_aux(
		const size_type L_start_vertex,
		bool L_visited[],
		DFSVisitor<adjacency_matrix_directed> & L_vis)
{
	L_visited[L_start_vertex] = true;
	if(!L_vis.discover_vertex(L_start_vertex, *this))
		return false;

	for(typename std::vector<std::pair<bool, EdgeInfo> >::size_type
		L_iter = 0,
		L_end = this->M_list[L_start_vertex].size();
		L_iter != L_end;
		++L_iter)
	{
		if(this->M_list[L_start_vertex][L_iter].first == false)
			continue;

		const size_type L_target = L_iter;
		if(!L_vis.examine_edge(L_start_vertex, L_target, *this))
			return false;

		if(L_visited[L_target] == false) {
			if(!L_vis.tree_edge(L_start_vertex, L_target, *this))
				return false;
			if(!depth_first_search_aux(L_target, L_visited, L_vis))
				return false;
		} else {
			if(!L_vis.back_edge(L_start_vertex, L_target, *this))
				return false;
		}//if-else
	}//for
	if(!L_vis.finish_vertex(L_start_vertex, *this))
		return false;

	return true;
}//deapth_first_search_aus(start_vertex, visited[], vis)

