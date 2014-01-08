#include "../adjacency_matrix_directed"
#include "../adjacency_list_directed"
#include "../adjacency_list_undirected"

#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <string>

typedef adjacency_list_undirected<DefaultEdgeInfo, std::string> graph_type;
typedef typename graph_type::size_type size_type;

class DFSVISITOR : public DFSVisitor<graph_type>
{
public:
	/*
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
	*/

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
		/*
		std::cout << std::setw(20) << "finish_vertex: " << std::left << std::setw(10) << v << std::right
			<< " @" << &dummy << std::endl;
		*/
		std::cout << dummy.second << std::endl;
		return true;
	}
};//class DFSVISITOR


int main()
{
	//BFSVISITOR vv;
	DFSVISITOR vd;

	graph_type g;

	g.add_vertex(std::string("Dummy Begin"));
	g.add_vertex("高等數學");
	g.add_vertex("程序設計基礎");
	g.add_vertex("離散數學");
	g.add_vertex("數據結構");
	g.add_vertex("高級語言程序設計");
	g.add_vertex("編譯原理");
	g.add_vertex("操作系統");
	g.add_vertex("普通物理");
	g.add_vertex("計算機原理");
	g.add_vertex("Dummy End");
	
	g.add_edge(0, 1);
	g.add_edge(0, 2);
	g.add_edge(2, 5);
	g.add_edge(5, 6);
	g.add_edge(2, 3);
	g.add_edge(2, 4);
	g.add_edge(4, 6);
	g.add_edge(1, 3);
	g.add_edge(3, 4);
	g.add_edge(1, 8);
	g.add_edge(8, 9);
	g.add_edge(9, 7);
	g.add_edge(4, 7);
	g.add_edge(6, 10);
	g.add_edge(7, 10);

	/*
	auto dd = g.data();
	for(auto i = 0lu; i < dd.size(); ++i) {
		for(auto j = 0lu; j < dd[i].size(); ++j) {
			std::cout << dd[i][j].first << ' ';
		}//for
		std::cout << std::endl;
	}//for
	*/

	// print reverse topological sort
	g.depth_first_traverse(vd);
}//main

