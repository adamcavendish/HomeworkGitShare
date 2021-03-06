#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "No_19/adjacency_list_undirected"

typedef adjacency_list_undirected<>	Graph;
typedef Graph::size_type			size_type;

class Vis : public BFSVisitor<Graph>
{
public:
	bool
	tree_edge(size_type s, size_type t, Graph & g) {
		std::cout << s << " --> " << t << std::endl;
		return true;
	}
};//class Vis

std::size_t
inputVertex();

void
inputEdge(Graph & g);

std::size_t
inputLength();

std::pair<size_type, size_type>
inputStartEndPoints();

std::vector<std::vector<size_type> >
search_path(
		const typename Graph::content_type & L_g,
		size_type L_start_vertex,
		size_type L_end_vertex,
		size_type L_length);

size_type
search_path_aux(
		const typename Graph::content_type & L_g,	// Graph to search
		const size_type L_start_vertex,				// search start_vertex
		const size_type L_end_vertex,				// search end_vertex
		bool L_visited[],							// tag for visited in dfs
		const size_type L_length,					// remaining length to go
		std::vector<std::vector<size_type> > & L_ret);// ret path(s)

int main()
{
	//std::size_t vertex_nums = inputVertex();
	std::size_t vertex_nums = 9;

	Graph g(vertex_nums);
	//inputEdge(g);
	g.add_edge(0, 1);
	g.add_edge(0, 3);
	g.add_edge(0, 4);
	g.add_edge(1, 2);
	g.add_edge(3, 6);
	g.add_edge(4, 5);
	g.add_edge(4, 6);
	g.add_edge(5, 7);
	g.add_edge(5, 8);
	g.add_edge(6, 7);
	g.add_edge(7, 8);

	std::pair<size_type, size_type> points = inputStartEndPoints();

	std::size_t length = inputLength();

	std::cout << "Edges: " << std::endl;
	auto dd = g.data();
	for(auto v_iter = 0lu; v_iter < dd.size(); ++v_iter) {
		for(auto e_iter = dd[v_iter].begin(); e_iter != dd[v_iter].end(); ++e_iter) {
			std::cout << v_iter << "->" << e_iter->first << std::endl;
		}//for
	}//for
	std::cout << std::endl;

	std::vector<size_type> tree = g.depth_first_search_n(points.first, points.second, length);

	if(tree.size() != 0) {
		for(auto i = 0lu; i < tree.size() - 1; ++i)
			std::cout << tree[i] << "->";
		std::cout << tree.back() << std::endl;
	}//if

	return 0;
}//main

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

std::vector<std::vector<size_type> >
search_path(
		const typename Graph::content_type & L_g,
		size_type L_start_vertex,
		size_type L_end_vertex,
		size_type L_length)
{
	std::vector<std::vector<size_type> > L_ret(1);

	bool L_visited[L_g.size()];
	std::fill_n(L_visited, L_g.size(), false);

	search_path_aux(
			L_g,				// Graph to search
			L_start_vertex,		// start_vertex
			L_end_vertex,		// end_vertex
			L_visited,			// tag for visited in dfs
			L_length,			// search length
			L_ret);				// ret path(s)
	
	L_ret.pop_back();
	return L_ret;
}//search_path

size_type
search_path_aux(
		const typename Graph::content_type & L_g,	// Graph to search
		const size_type L_start_vertex,				// search start_vertex
		const size_type L_end_vertex,				// search end_vertex
		bool L_visited[],							// tag for visited in dfs
		const size_type L_length,					// remaining length to go
		std::vector<std::vector<size_type> > & L_ret)// ret path(s)
{
	enum EXIT_VAL : size_type {
		CONTINUE = 0,
		SKIP_NODE,
		FOUND
	};

	L_visited[L_start_vertex] = true;
	L_ret.back().push_back(L_start_vertex);

#ifndef NDEBUG
std::cout << L_ret.size() << "th: " << L_length << ": ";
for(auto i : L_ret.back())
	std::cout << i << "->";
std::cout << "\b\b  " << std::endl;
#endif

	if(L_length == 0) {
		if(L_start_vertex == L_end_vertex) {
			return EXIT_VAL::FOUND;
		} else {
			return EXIT_VAL::CONTINUE;
		}//if-else
	}//if

	for(auto L_i = 0lu; L_i < L_g.size(); ++L_i) {
	for(auto L_iter = L_g[L_i].begin(),
			L_end = L_g[L_i].end();
			L_iter != L_end;
			++L_iter)
		if(L_visited[L_i] == false)
		{
			size_type L_aux_ret = search_path_aux(
						L_g,			// Graph to search
						L_i,			// start_vertex
						L_end_vertex,	// end_vertex
						L_visited,		// tag for visited in dfs
						L_length-1,		// remaining search length
						L_ret);			// ret path(s)

			switch(L_aux_ret) {
				case EXIT_VAL::CONTINUE:
					L_visited[L_i] = false;
					L_ret.back().pop_back();
					break;
				case EXIT_VAL::SKIP_NODE:
					L_visited[L_i] = false;
					L_ret.back().pop_back();
					return EXIT_VAL::CONTINUE;
				case EXIT_VAL::FOUND:
#ifndef NDEBUG
std::cout << std::endl;
#endif
					// copy the current path
					L_ret.push_back(
							std::vector<std::vector<size_type> >::value_type(
								L_ret.back()
							));
					// pop out the last one
					L_visited[L_i] = false;
					L_ret.back().pop_back();
					return EXIT_VAL::CONTINUE;
			}//switch
		}//if
	}//for

	return EXIT_VAL::CONTINUE;
}//search_path_aux
