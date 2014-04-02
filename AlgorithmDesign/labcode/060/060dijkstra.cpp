#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <limits>

#define DEBUG if(1)

void input();
void output();
void calculate();
void backtrack();

struct node
{
	int cost;
	int pos;

	bool operator<(const node & rhs) const {
		if(this->cost != rhs.cost)
			return this->cost < rhs.cost;
		if(this->pos != rhs.pos)
			return this->pos < rhs.pos;
		return false;
	}//operator<(lhs, rhs)
};//struct node

int g_id = 1;
int g_node_num;
int g_graph[50*50];
int g_short[50];
bool g_visited[50];
int g_start;
int g_end;
std::vector<node> g_link_graph[50];

int g_parent[50];

int g_result;
int g_result_length;

int main()
{
	while(true) {
		input();
		if(std::cin.eof())
			break;

		calculate();
		backtrack();
		output();
	}//while

	return 0;
}//main

void input()
{
	std::cin >> g_node_num;
	for(int i = 0; i < g_node_num; ++i) {
		for(int j = 0; j < g_node_num; ++j) {
			std::cin >> g_graph[i * 50 +j];
		}//for
	}//for

	std::cin >> g_start;
	std::cin >> g_end;
	--g_start;
	--g_end;

	for(int i = 0; i < g_node_num; ++i) {
		g_link_graph[i].clear();
	}//for

	for(int i = 0; i < g_node_num; ++i) {
		for(int j = 0; j < g_node_num; ++j) {
			if(g_graph[i * 50 + j] != -1) {
				node n;
				n.cost = g_graph[i * 50 + j];
				n.pos = j;
				g_link_graph[i].push_back(n);
			}//if
		}//for
	}//for
	
	for(int i = 0; i < g_node_num; ++i) {
		g_short[i] = std::numeric_limits<int>::max();
		g_visited[i] = false;
		g_parent[i] = -1;
	}//for

	for(int i = 0; i < g_node_num; ++i) {
		DEBUG std::cout << "from: " << i << std::endl;
		for(std::vector<node>::iterator iter = g_link_graph[i].begin(); iter != g_link_graph[i].end(); ++iter) {
			DEBUG std::cout << " " << iter->pos << ": " << iter->cost << std::endl;
		}//for
	}//for
}//input()

void output()
{
	std::cout << "Case " << g_id++ << std::endl;
	std::cout << g_result << ' ' << g_result_length << std::endl;
}//output()

void calculate()
{
	std::queue<int> que;

	node n;
	n.cost = g_short[g_start];
	n.pos = g_start;
	que.push(n);

	while(!que.empty()) {
		node from_node = que.front();
		que.pop();
		g_visited[from_node.pos] = true;

		for(std::size_t i = 0; i < g_link_graph[from_node.pos].size(); ++i) {
			node to_node = g_link_graph[from_node.pos][i];
			if(!g_visited[to_node.pos] && (g_short[from_node.pos] + to_node.cost >= g_short[to_node.pos]))
			{
				g_short[to_node.pos] = g_short[from_node.pos] + to_node.cost;
			}//if
		}//for
	}//while
}//calculate()

void backtrack()
{
	std::vector<int> path;
	int dest = g_end;
	while(dest != g_start) {
		path.push_back(dest);
		dest = g_parent[dest];
	}//while
	path.push_back(g_start);
	std::reverse(path.begin(), path.end());

	for(std::vector<int>::iterator iter = path.begin(); iter != path.end()-1; ++iter) 
		DEBUG std::cout << *iter << "->";
	DEBUG std::cout << *(path.end()-1) << std::endl;

	g_result_length = path.size();
}


