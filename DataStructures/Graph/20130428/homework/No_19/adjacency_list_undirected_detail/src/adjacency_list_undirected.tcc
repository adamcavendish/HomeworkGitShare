#pragma once

#include <algorithm>
#include <exception>
#include <stdexcept>
#include <string>
#include <iterator>
#include <queue>

#include "../adjacency_list_undirected.hpp"
#include "../../../../BFSVisitor.hpp"
#include "../../../../DFSVisitor.hpp"

static_assert(__cplusplus >= 201103L, "Compile with -std=c++11");

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_list_undirected<EdgeInfo, VertexInfo, GraphInfo>::add_edge(
		const size_type L_source,
		const size_type L_target,
		const EdgeInfo & L_info)
{
	if(L_source >= this->M_vertex_size || L_target >= this->M_vertex_size) {
		std::throw_with_nested(std::out_of_range(std::string(
						"adjacency_list_undirected error: "
						"add_edge() out of range.")));
	}//if

	auto L_find_iter = std::find_if(
			this->M_list[L_source].begin(),
			this->M_list[L_source].end(),
			[=](const std::pair<size_type, EdgeInfo> & rhs) {
				return (rhs.first == L_target);
			});
	if(L_find_iter != this->M_list[L_source].end()) {
		return false;
	} else {
		this->M_list[L_source].push_back(std::make_pair(L_target, L_info));
		this->M_list[L_target].push_back(std::make_pair(L_source, L_info));
		return true;
	}//if-else

	return false;
}//add_edge(source, target, info)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_list_undirected<EdgeInfo, VertexInfo, GraphInfo>::remove_edge(
		const size_type L_source,
		const size_type L_target)
{
	if(L_source >= this->M_vertex_size || L_target >= this->M_vertex_size) {
		std::throw_with_nested(std::out_of_range(std::string(
						"adjacency_matrix_undirected error: "
						"remove_edge() out of range.")));
	}//if

	auto L_find_iter = std::find_if(
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

	L_find_iter = std::find_if(
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

	return false;
}//remove_edge(iter)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
typename adjacency_list_undirected<EdgeInfo, VertexInfo, GraphInfo>::size_type
adjacency_list_undirected<EdgeInfo, VertexInfo, GraphInfo>::add_vertex(const VertexInfo & L_info)
{
	this->M_vertex.push_back(L_info);
	this->M_list.push_back(std::list<std::pair<size_type, EdgeInfo> >());
	++this->M_vertex_size;
	return this->M_vertex_size-1;
}//add_vertex(info)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_list_undirected<EdgeInfo, VertexInfo, GraphInfo>::remove_vertex(const size_type L_vertex_id)
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

	for(typename std::list<std::pair<size_type, EdgeInfo> >::iterator
				L_iter_bgn = L_iter->begin(),
				L_iter_end = L_iter->end();
			L_iter_bgn != L_iter_end;
			++L_iter_bgn)
	{
		std::find_if(
				this->M_list[L_iter_bgn->first].begin(),
				this->M_list[L_iter_bgn->first].end(),
			[=](const std::pair<size_type, EdgeInfo> & rhs) {
				return (rhs.first == L_vertex_id);
			});
	}//for

	this->M_list.erase(L_iter);

	return true;
}//remove_vertex(iter)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
std::pair<bool, EdgeInfo>
adjacency_list_undirected<EdgeInfo, VertexInfo, GraphInfo>::get_edge(const size_type L_source, const size_type L_target) const {
	if(L_source >= this->M_vertex_size ||
			L_target >= this->M_vertex_size)
	{
		return std::make_pair(false, EdgeInfo());
	}//if

	auto L_find_iter = std::find_if(
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

	return std::make_pair(false, EdgeInfo());
}//get_edge(source, target)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_list_undirected<EdgeInfo, VertexInfo, GraphInfo>::put_edge(
			const size_type L_source,
			const size_type L_target,
			const EdgeInfo & L_info)
{
	if(L_source >= this->M_vertex_size ||
			L_target >= this->M_vertex_size)
	{
		return false;
	}//if

	auto L_find_iter = std::find_if(
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

	return false;
}//put_edge(source, target, info)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_list_undirected<EdgeInfo, VertexInfo, GraphInfo>::breadth_first_search_aux(
		const size_type L_start_vertex,
		bool L_visited[],
		BFSVisitor<adjacency_list_undirected> & L_vis)
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

		for(typename std::list<std::pair<size_type, EdgeInfo> >::iterator
			L_iter = this->M_list[L_cur_vertex].begin(),
			L_end = this->M_list[L_cur_vertex].end();
			L_iter != L_end;
			++L_iter)
		{
			size_type L_target_vertex = L_iter->first;
			if(!L_vis.examine_edge(L_cur_vertex, L_target_vertex, *this))
				return false;

			// not visted
			if(L_visited[L_target_vertex] == false) {
				L_visited[L_target_vertex] = true;
				if(!L_vis.tree_edge(L_cur_vertex, L_target_vertex, *this))
					return false;
				if(!L_vis.discover_vertex(L_target_vertex, *this))
					return false;
				L_que.push(L_target_vertex);
			}//if
		}//for
		
		if(!L_vis.finish_vertex(L_cur_vertex, *this))
			return false;
	}//while

	return true;
}//breadth_first_search_aux(start_vertex, visited, vis)

template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
bool
adjacency_list_undirected<EdgeInfo, VertexInfo, GraphInfo>::depth_first_search_aux(
		const size_type L_start_vertex,
		bool L_visited[],
		DFSVisitor<adjacency_list_undirected> & L_vis)
{
	L_visited[L_start_vertex] = true;
	if(!L_vis.discover_vertex(L_start_vertex, *this))
		return false;

	for(typename std::list<std::pair<size_type, EdgeInfo> >::iterator
		L_iter = this->M_list[L_start_vertex].begin(),
		L_end = this->M_list[L_start_vertex].end();
		L_iter != L_end;
		++L_iter)
	{
		size_type L_target = L_iter->first;
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
}//deapth_first_search_aux(start_vertex, visited[], vis)


template <typename EdgeInfo, typename VertexInfo, typename GraphInfo>
int
adjacency_list_undirected<EdgeInfo, VertexInfo, GraphInfo>::depth_first_search_n_aux(
		const size_type L_start_vertex,
		const size_type L_end_vertex,
		bool L_visited[],
		std::vector<size_type> & tree_vec,
		const size_type length)
{
	const int CONTINUE_RET = 0;
	const int FOUND_TARGET_RET = 1;
	const int LENGTH_ZERO_RET = 2;

	L_visited[L_start_vertex] = true;
	tree_vec.push_back(L_start_vertex);

	if(length == 0) {
		if(L_start_vertex == L_end_vertex)
			return FOUND_TARGET_RET;
		return LENGTH_ZERO_RET;
	}//if

	for(typename std::list<std::pair<size_type, EdgeInfo> >::iterator
		L_iter = this->M_list[L_start_vertex].begin(),
		L_end = this->M_list[L_start_vertex].end();
		L_iter != L_end;
		++L_iter)
	{
		size_type L_target = L_iter->first;

		if(L_visited[L_target] == false) {
			if(depth_first_search_n_aux(L_target, L_end_vertex, L_visited,	tree_vec, length-1) == FOUND_TARGET_RET)
			{
				return FOUND_TARGET_RET;
			}//if
		}//if
	}//for
	L_visited[L_start_vertex] = false;
	tree_vec.pop_back();

	return CONTINUE_RET;
}//depth_first_search_n_aux

