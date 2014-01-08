#include "../adjacency_list_directed"

#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <string>

class BFSVISITOR : public BFSVisitor<adjacency_list_directed<> >
{
	typedef adjacency_list_directed<> graph_type;
	typedef typename graph_type::size_type size_type;
public:
	bool initialize_vertex(const size_type v, graph_type & g) override {
		auto dummy = g.get_vertex(v);
		std::cout << std::setw(20) << "initialize_vertex: " << std::left << std::setw(10) << v << std::right
			<< " @" << &dummy << std::endl;
		return true;
	}

	bool discover_vertex(const size_type v, graph_type & g) override {
		auto dummy = g.get_vertex(v);
		std::cout << std::setw(20) << "discover_vertex: " << std::left << std::setw(10) << v << std::right
			<< " @" << &dummy << std::endl;
		return true;
	}

	bool examine_vertex(const size_type v, graph_type & g) override {
		auto dummy = g.get_vertex(v);
		std::cout << std::setw(20) << "examine_vertex: " << std::left << std::setw(10) << v << std::right
			<< " @" << &dummy << std::endl;
		return true;
	}

	bool examine_edge(const size_type v1, const size_type v2, graph_type & g) override {
		auto dummy = g.get_edge(v1, v2);
		std::string ss;
		ss += std::to_string(v1); ss += ", "; ss += std::to_string(v2);

		std::cout << std::setw(20) << "examine_edge: " << std::left << std::setw(10) << ss << std::right
			<< " @" << &dummy << std::endl;
		return true;
	}

	bool tree_edge(const size_type v1, const size_type v2, graph_type & g) override {
		auto dummy = g.get_edge(v1, v2);
		std::string ss;
		ss += std::to_string(v1); ss += ", "; ss += std::to_string(v2);

		std::cout << std::setw(20) << "tree_edge: " << std::left << std::setw(10) << ss << std::right
			<< " @" << &dummy << std::endl;
		return true;
	}

	bool non_tree_edge(const size_type v1, const size_type v2, graph_type & g) override {
		auto dummy = g.get_edge(v1, v2);
		std::string ss;
		ss += std::to_string(v1); ss += ", "; ss += std::to_string(v2);

		std::cout << std::setw(20) << "non_tree_edge: " << std::left << std::setw(10) << ss << std::right
			<< " @" << &dummy << std::endl;
		return true;
	}

	bool finish_vertex(const size_type v, graph_type & g) override {
		auto dummy = g.get_vertex(v);
		std::cout << std::setw(20) << "finish_vertex: " << std::left << std::setw(10) << v << std::right
			<< " @" << &dummy << std::endl;
		return true;
	}
};//class BFSVISITOR

class DFSVISITOR : public DFSVisitor<adjacency_list_directed<> >
{
	typedef adjacency_list_directed<> graph_type;
	typedef typename graph_type::size_type size_type;
public:
	bool initialize_vertex(const size_type v, graph_type & g) override {
		auto dummy = g.get_vertex(v);
		std::cout << std::setw(20) << "initialize_vertex: " << std::left << std::setw(10) << v << std::right
			<< " @" << &dummy << std::endl;
		return true;
	}

	bool start_vertex(const size_type v, graph_type & g) override {
		auto dummy = g.get_vertex(v);
		std::cout << std::setw(20) << "start_vertex: " << std::left << std::setw(10) << v << std::right
			<< " @" << &dummy << std::endl;
		return true;
	}

	bool discover_vertex(const size_type v, graph_type & g) override {
		auto dummy = g.get_vertex(v);
		std::cout << std::setw(20) << "discover_vertex: " << std::left << std::setw(10) << v << std::right
			<< " @" << &dummy << std::endl;
		return true;
	}

	bool examine_edge(const size_type v1, const size_type v2, graph_type & g) override {
		auto dummy = g.get_edge(v1, v2);
		std::string ss;
		ss += std::to_string(v1); ss += ", "; ss += std::to_string(v2);

		std::cout << std::setw(20) << "examine_edge: " << std::left << std::setw(10) << ss << std::right
			<< " @" << &dummy << std::endl;
		return true;
	}

	bool tree_edge(const size_type v1, const size_type v2, graph_type & g) override {
		auto dummy = g.get_edge(v1, v2);
		std::string ss;
		ss += std::to_string(v1); ss += ", "; ss += std::to_string(v2);

		std::cout << std::setw(20) << "tree_edge: " << std::left << std::setw(10) << ss << std::right
			<< " @" << &dummy << std::endl;
		return true;
	}

	bool back_edge(const size_type v1, const size_type v2, graph_type & g) override {
		auto dummy = g.get_edge(v1, v2);
		std::string ss;
		ss += std::to_string(v1); ss += ", "; ss += std::to_string(v2);

		std::cout << std::setw(20) << "back_edge: " << std::left << std::setw(10) << ss << std::right
			<< " @" << &dummy << std::endl;
		return true;
	}

	bool finish_vertex(const size_type v, graph_type & g) override {
		auto dummy = g.get_vertex(v);
		std::cout << std::setw(20) << "finish_vertex: " << std::left << std::setw(10) << v << std::right
			<< " @" << &dummy << std::endl;
		return true;
	}
};//class DFSVISITOR


int main()
{
	BFSVISITOR vv;
	DFSVISITOR vd;

	adjacency_list_directed<> g(9);
	
	g.add_edge(0, 1);
	g.add_edge(3, 0);
	g.add_edge(0, 4);
	g.add_edge(1, 2);
	g.add_edge(1, 4);
	g.add_edge(2, 4);
	g.add_edge(3, 6);
	g.add_edge(4, 5);
	g.add_edge(4, 6);
	g.add_edge(5, 8);
	g.add_edge(6, 7);

	g.breadth_first_traverse(vv);

	std:: cout << "--------------------------------------------------" << std::endl;

	g.depth_first_traverse(vd);
}//main

