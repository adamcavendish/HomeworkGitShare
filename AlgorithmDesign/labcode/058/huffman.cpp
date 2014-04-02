#include <iostream>
#include <string>
#include <utility>
#include <queue>

std::size_t g_id;

std::size_t g_sz;
std::size_t g_temp[50];
std::string g_huff[50];

struct Node {
	Node * left;
	Node * right;
	Node * parent;
	std::size_t data;
	std::size_t length;
	std::size_t index;
};

typedef std::pair<std::size_t, Node *> type;
class compare
{
public:
	bool operator()(const type & lhs, const type & rhs)
	{
		if(lhs.first < rhs.first) {
			return false;
		} else if(lhs.first > rhs.first) {
			return true;
		} else {
			// equal
			if(lhs.second->index < rhs.second->index) {
				return true;
			} else if(lhs.second->index > rhs.second->index) {
				return false;
			} else {
				if(lhs.second->length < rhs.second->length) {
					return true;
				} else if(lhs.second->length > rhs.second->length) {
					return false;
				} else {
					return false;
				}//if-else
			}//if-else

		}//if-else

		return false;
	}//compare(lhs, rhs)
};
std::priority_queue<type, std::vector<type>, compare> g_que;

void input();
void output();
void calculate();
void backtrace(Node * iter, std::string & ss);
void display();

int main()
{
	int counter;
	g_id = 1;
	std::cin >> counter;
	while(counter-- > 0) {
		input();
		calculate();
		output();
	}//while

	return 0;
}//main

void input()
{
	std::cin >> g_sz;
	for(std::size_t i = 0; i < g_sz; ++i) {
		std::cin >> g_temp[i];
		g_huff[i].clear();
	}//for
}//input()

void output()
{
	std::cout << "Case " << g_id++ << std::endl;
	for(std::size_t i = 0; i < g_sz; ++i) {
		std::cout << g_temp[i] << ' ';
		std::cout << g_huff[i] << std::endl;
	}//for
	std::cout << std::endl;
}

void calculate()
{
	std::size_t index_cnt = g_sz;

	for(std::size_t i = 0; i < g_sz; ++i) {
		Node * nd = new Node;
		nd->left = NULL;
		nd->right = NULL;
		nd->parent = NULL;
		nd->data = g_temp[i];
		nd->length = 1;
		nd->index = i;
		g_que.push(std::make_pair(g_temp[i], nd));
	}//for

	while(g_que.size() > 1) {
		std::pair<std::size_t, Node *> n1 = g_que.top();
		g_que.pop();
		std::pair<std::size_t, Node *> n2 = g_que.top();
		g_que.pop();

		Node * nd = new Node;
		nd->left = n2.second;
		nd->right = n1.second;
		nd->parent = NULL;
		nd->data = 0;
		nd->length = n1.second->length + n2.second->length + 1;
		nd->index = index_cnt++;
		n1.second->parent = nd;
		n2.second->parent = nd;

		g_que.push(std::make_pair(n1.first + n2.first, nd));
	}//while

	if(g_que.size() > 0) {
		std::pair<std::size_t, Node *> n = g_que.top();
		g_que.pop();

		std::string ss;
		backtrace(n.second, ss);
	}//if
}//calculate()

void backtrace(Node * iter, std::string & ss)
{
	if(iter != NULL) {
		ss.push_back('0');
		backtrace(iter->left, ss);
		ss.resize(ss.size() - 1);
		if(iter->data > 0) {
			g_huff[iter->index] = ss;
		}//if
		ss.push_back('1');
		backtrace(iter->right, ss);
		ss.resize(ss.size() - 1);

		delete iter;
		iter = NULL;
	}//if
}//backtrace()

