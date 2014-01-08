#include <iostream>
#include <cstdlib>
#include <queue>

#include <future>

const int NODE_END = -1;

struct Tree
{
	int head;
	int * L;
	int * R;
};//struct Tree

bool test(const Tree * tt, const int u, const int v);
bool test_aux(const Tree * tt, const int u, const int v, const int parent);

int find_parent(const Tree * tt, const int tag)
{
	/**
	 * @brief to see is to understand
	 */
	
	if(tag <= 0)
		return NODE_END;

	int __next = 1; // next tag: head's next is 1

	std::queue<int> __queue;
	__queue.push(0); // push the head
	
	while(!__queue.empty()) {
		int __parent = __queue.front();
		__queue.pop();

		if(tt->L[__parent] != NODE_END) {
			if(__next == tag)
				return __parent;
			__queue.push(__next);
			++__next;
		}//if
		if(tt->R[__parent] != NODE_END) {
			if(__next == tag)
				return __parent;
			__queue.push(__next);
			++__next;
		}//if
	}//while
	return NODE_END;
}//find_parent(tt, tag)

bool test(const Tree * tt, const int u, const int v)
{
	/**
	 * @brief test whether u is a child of v, -1 is nullptr
	 * @param u the expected child tag
	 * @param v the expected parent tag
	 * @return whether u is the child of v
	 */
	if(tt->head == NODE_END || u <= v)
		return false;

	int __u_recurse = u;
	do {
		int __direct_parent = find_parent(tt, __u_recurse);
		if(__direct_parent == v)
			return true;
		if(__direct_parent == NODE_END)
			return false;
		__u_recurse = __direct_parent;
	} while(1);

	return false;
}//test(tt, u, v)

int main(int argc, char * argv[])
{
	int __L[11] = {1, 3, 5, 6, 7, -1, -1, -1, 9, -1, -1};
	int __R[11] = {2, 4, -1, -1, -1, 8, -1, -1, -1, 10, -1};
	Tree * t = new Tree;
	t->head = 0;
	t->L = __L;
	t->R = __R;

	if(argc != 3) {
		std::cout << argv[0] << " u v" << std::endl;
		exit(EXIT_FAILURE);
	}//if

	std::cout << std::boolalpha
		<< test(t, std::atoi(argv[1]), std::atoi(argv[2])) << std::endl;

	delete t;
}//main

