#include <iostream>
#include <string>

#include "No_19/adjacency_list_undirected"

typedef adjacency_list_undirected<>	Graph;
typedef Graph::size_type			size_type;

class Vis : public DFSVisitor<Graph>
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

