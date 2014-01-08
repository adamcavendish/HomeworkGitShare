#include "../adjacency_list_directed"

#include <string>
#include <iostream>
#include <fstream>

typedef adjacency_list_directed<>	Graph;
typedef Graph::size_type			size_type;

class Vis : public DFSVisitor<Graph>
{
public:
	Vis(size_type start, size_type end) :
		M_start(start),
		M_end(end)
	{}

	bool
	discover_vertex(size_type s, Graph & g) {
		if(s == this->M_end) {
			std::cout << "A Routine Found!" << std::endl;
			return false;
		}//if
		return true;
	}//discover_vertex(vertex, Graph)

	bool
	tree_edge(size_type s, size_type t, Graph & g) {
		std::cout << s << " --> " << t << std::endl;
		return true;
	}//examine_edge(s, t, g)

private:
	size_type M_start;
	size_type M_end;
};//class Vis

std::size_t
inputVertex();

std::size_t
inputVertexFromFile(std::ifstream & in);

void
inputEdge(Graph & g);

void
inputEdgeFromFile(Graph & g, std::ifstream & in);

std::pair<size_type, size_type>
inputStartEndPoints();

int main(int argc, char * argv[])
{
	if(argc != 2) {
		std::cout << argv[0] << " filename." << std::endl;
		exit(EXIT_FAILURE);
	}//if

	std::ifstream in(argv[1]);
	std::size_t vertex_nums = inputVertexFromFile(in);

	Graph g(vertex_nums);
	inputEdgeFromFile(g, in);

	std::pair<size_type, size_type> points = inputStartEndPoints();

	Vis visitor(points.first, points.second);
	g.depth_first_search(points.first, visitor);

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
inputVertexFromFile(std::ifstream & in) {
	std::size_t vertex_nums;

	in >> vertex_nums;

	return vertex_nums;
}//inputVertexFromFile(in)

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

void
inputEdgeFromFile(Graph & g, std::ifstream & in) {
	size_type source, target;

	while(!in.eof()) {
		in >> source >> target;

		g.add_edge(source, target);
	}//while
}//inputEdgeFromFile(Graph, in)

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

