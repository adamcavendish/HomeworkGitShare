#include "../adjacency_matrix_directed"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

typedef adjacency_matrix_directed<std::size_t>	Graph;
typedef Graph::size_type						size_type;

std::size_t
inputVertex();

void
inputEdge(Graph & g);

std::size_t
inputLength();

std::pair<size_type, size_type>
inputStartEndPoints();

std::vector<std::pair<size_type, size_type> >
critical_path(const Graph & g);

void
critical_path_aux(
	const Graph & L_g,
	const size_type L_start_vertex,
	bool L_visited[],
	size_type L_early[],
	size_type L_late[]);

/*
void
critical_path_early_aux(
	const Graph & L_g,
	const size_type L_start_vertex,
	bool L_visited[],
	size_type L_early[]);

void
critical_path_late_aux(
		const Graph & L_g,
		const size_type L_start_vertex,
		size_type L_late[]);
*/

int main()
{
	// Using Graph at Page 243, answer at Page 245
//	std::size_t vertex_nums = inputVertex();
	std::size_t vertex_nums = 7;

	Graph g(vertex_nums);
	//inputEdge(g);
	g.add_edge(0, 1, 3lu);
	g.add_edge(0, 2, 2lu);
	g.add_edge(0, 3, 6lu);
	g.add_edge(1, 4, 4lu);
	g.add_edge(1, 3, 2lu);
	g.add_edge(2, 3, 1lu);
	g.add_edge(2, 5, 3lu);
	g.add_edge(3, 4, 1lu);
	g.add_edge(4, 6, 3lu);
	g.add_edge(5, 6, 4lu);
	//g.add_edge(6, 1, 100lu); // make cyclic graph

	const auto & cri_paths = critical_path(g);

	std::cout << "Critical Paths Are: " << std::endl;
	for(auto i : cri_paths)
		std::cout << i.first << ' ' << i.second << std::endl;

	return 0;
}//main

std::vector<std::pair<size_type, size_type> >
critical_path(const Graph & g) {
	std::vector<std::pair<size_type, size_type> > ret;

	size_type * early = new size_type[g.vertex_num()];
	size_type * late = new size_type[g.vertex_num()];

	bool * visited = new bool[g.vertex_num()];

	std::fill_n(early, g.vertex_num(), 0);
	std::fill_n(late, g.vertex_num(), std::numeric_limits<size_type>::max());

	critical_path_aux(g, 0, visited, early, late);

	size_type sub_val =
		std::numeric_limits<size_type>::max() - early[g.vertex_num()-1];
	for(auto i = 0lu; i < g.vertex_num(); ++i)
		late[i] -= sub_val;

#ifndef NDEBUG
	std::cout << "Early: ";
	for(auto i = 0lu; i < g.vertex_num(); ++i)
		std::cout << early[i] << ' ';
	std::cout << std::endl;
	std::cout << "Late: ";
	for(auto i = 0lu; i < g.vertex_num(); ++i)
		std::cout << late[i] << ' ';
	std::cout << std::endl;
#endif//NDEBUG

	for(auto i = 0lu; i < g.vertex_num(); ++i) {
		for(auto j = 0lu; j < g.vertex_num(); ++j) {
			auto L_edge = g.get_edge(i, j);
			if(L_edge.first == true) {
				if(early[i] - late[j] + L_edge.second == 0)
					ret.push_back(std::make_pair(i, j));
			}//if
		}//for
	}//for

	delete[] visited;

	delete[] late;
	delete[] early;

	return ret;
}//critical_path(g)

void
critical_path_aux(
	const Graph & L_g,
	const size_type L_start_vertex,
	bool L_visited[],
	size_type L_early[],
	size_type L_late[])
{
	L_visited[L_start_vertex] = true;

	for(auto i = 0lu; i != L_g.vertex_num(); ++i) {
		auto L_edge = L_g.get_edge(L_start_vertex, i);
		if(L_edge.first == true) {
			if(L_visited[i] == true)
				throw std::logic_error(std::string("Cyclic Graph!"));

			auto L_path_early_sum = L_early[L_start_vertex] + L_edge.second;
			if(L_early[i] < L_path_early_sum)
				L_early[i] = L_path_early_sum;

			critical_path_aux(L_g, i, L_visited, L_early, L_late);

			auto L_path_late_sum = L_late[i] - L_edge.second;
			if(L_late[L_start_vertex] > L_path_late_sum)
				L_late[L_start_vertex] = L_path_late_sum;
		}//if
	}//for

	L_visited[L_start_vertex] = false;
}//critical_path_aux

/*
void
critical_path_early_aux(
	const Graph & L_g,
	const size_type L_start_vertex,
	bool L_visited[],
	size_type L_early[])
{
	L_visited[L_start_vertex] = true;

	for(auto i = 0lu; i != L_g.vertex_num(); ++i) {
		auto L_edge = L_g.get_edge(L_start_vertex, i);
		if(L_edge.first == true) {
			if(L_visited[i] == true)
				throw std::logic_error(std::string("Cyclic Graph!"));

			auto L_path_sum = L_early[L_start_vertex] + L_edge.second;
			if(L_early[i] < L_path_sum)
				L_early[i] = L_path_sum;
			critical_path_early_aux(L_g, i, L_visited, L_early);
		}//if
	}//for

	L_visited[L_start_vertex] = false;
}//critical_path_early_aux

void
critical_path_late_aux(
		const Graph & L_g,
		const size_type L_start_vertex,
		size_type L_late[])
{
	for(auto i = 0lu; i != L_g.vertex_num(); ++i) {
		auto L_edge = L_g.get_edge(L_start_vertex, i);
		if(L_edge.first == true) {
			critical_path_late_aux(L_g, i, L_late);

			auto L_path_sum = L_late[i] - L_edge.second;
			if(L_late[L_start_vertex] > L_path_sum)
				L_late[L_start_vertex] = L_path_sum;
		}//if
	}//for
}//critical_path_late_aux
*/

std::size_t
inputVertex() {
	std::size_t vertex_nums;

	std::cout << "Input Vertex Number: " << std::endl;
	std::cin >> vertex_nums;
	while(!std::cin) {
		std::cin.clear();
		std::cout << "Input Error, Reinput Vertex Number: " << std::endl;
		std::cin >> vertex_nums;
	}//while

	return vertex_nums;
}//inputVertex(Graph)

std::size_t
inputLength() {
	std::size_t length;

	std::cout << "Input Length: " << std::endl;
	std::cin >> length;
	while(!std::cin) {
		std::cin.clear();
		std::cout << "Input Error, Reinput Length: " << std::endl;
		std::cin >> length;
	}//while

	return length;
}//inputVertex(Graph)

void
inputEdge(Graph & g) {
	size_type source, target;

	while(!std::cin.eof()) {
		std::cout << "Input source, target: " << std::endl;
		std::cin >> source >> target;

		g.add_edge(source, target);
	}//while

	std::cin.clear();
}//inputEdge(Graph)

std::pair<size_type, size_type>
inputStartEndPoints() {
	size_type start_point, end_point;

	std::cout << "Input Starting Point, End Point: " << std::endl;
	std::cin >> start_point >> end_point;
	while(!std::cin) {
		std::cin.clear();
		std::cout << "Input Error, Reinput Starting Point, End Point: "
			<< std::endl;
		std::cin >> start_point >> end_point;
	}//while

	return std::make_pair(start_point, end_point);
}//inputStartEndPoints()

