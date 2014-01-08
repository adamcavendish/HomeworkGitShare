#include "../tree/tree.hpp"

#include <iostream>

int main()
{
	Tree<int> tt = {
		0, 1, 2, 3, 4,
		NODE_END, 5, NODE_END, NODE_END, 6,
		NODE_END, NODE_END, NODE_END, 7, 8,
		NODE_END, NODE_END, NODE_END, NODE_END, NODE_END,
		9, NODE_END, NODE_END, NODE_END, NODE_END,
		NODE_END, NODE_END, NODE_END, NODE_END, NODE_END,
		NODE_END
	};

	std::cout << std::endl << "LEVELORDER: " << std::endl;
	tt.levelorder([=](int x) {
		std::cout << x << ' ';
	});
	std::cout << std::endl;

	std::cout << std::endl << "PREORDER: " << std::endl;
	tt.preorder([=](int x) {
		std::cout << x << ' ';
	});
	std::cout << std::endl;

	return 0;
}//main

