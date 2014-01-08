#include "../adjacency_list_directed"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>
#include <utility>

typedef adjacency_list_directed<DefaultEdgeInfo, std::string> graph_type;
typedef typename graph_type::size_type size_type;

int main()
{
	// using Graph on Page 238
	graph_type g;

	/*
	g.add_vertex("Dummy Begin");
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
	*/

    g.add_vertex("高等數學");
    g.add_vertex("程序設計基礎");
    g.add_vertex("離散數學");
    g.add_vertex("數據結構");
    g.add_vertex("高級語言程序設計");
    g.add_vertex("編譯原理");
    g.add_vertex("操作系統");
    g.add_vertex("普通物理");
    g.add_vertex("計算機原理");
    
    g.add_edge(1, 4);
    g.add_edge(4, 5);
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(3, 5);
    g.add_edge(0, 2);
    g.add_edge(2, 3);
    g.add_edge(0, 7);
    g.add_edge(7, 8);
    g.add_edge(8, 6);
    g.add_edge(3, 6);

	std::vector<size_type> reverse_topo;
	topological_sort(g, std::back_inserter(reverse_topo));

	for(auto i = reverse_topo.rbegin(), i_end = reverse_topo.rend();
			i != i_end;
			++i)
	{
		std::cout << g.get_vertex(*i).second << std::endl;
	}//for
	return 0;
}//main

