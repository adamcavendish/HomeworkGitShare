#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

#include "tree.hpp"

int main()
{
	Tree<int> t {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10
	};

	std::vector<int> vv;
	bool flag = true;
	int previous_data = std::numeric_limits<int>::min();

	std::cout << "INORDER: " << std::endl;
	t.inorder([=](tree_node<int> * nd) {
			std::cout << nd->_M_data << ' ';
	});
	std::cout << std::endl;

	t.inorder([&flag, &previous_data](tree_node<int> * nd) {
			if(flag == true) {
				if(previous_data > nd->_M_data) {
					flag = false;
					std::cout << "This is not a BST!" << std::endl;
				}//if
				previous_data = nd->_M_data;
			}//if
	});

	if(flag == true)
		std::cout << "This is a BST!" << std::endl;

	std::cout << "--------------------------------------------------" << std::endl;

	// Page 263 -- Graph 8.8
	Tree<int> t2 {
		100000,
		11, 68,
		8, 23, 46, NE,
		NE, NE, NE, 34, NE, NE, NE, NE
	};

	std::vector<int> vv2;
	bool flag2 = true;
	int previous_data2 = std::numeric_limits<int>::min();

	std::cout << "INORDER: " << std::endl;
	t2.inorder([=](tree_node<int> * nd) {
			std::cout << nd->_M_data << ' ';
	});
	std::cout << std::endl;

	t2.inorder([&flag2, &previous_data2](tree_node<int> * nd) {
			if(flag2 == true) {
				if(previous_data2 > nd->_M_data) {
					flag2 = false;
					std::cout << "This is not a BST!" << std::endl;
				}//if
				previous_data2 = nd->_M_data;
			}//if
	});

	if(flag2 == true)
		std::cout << "This is a BST!" << std::endl;

	return 0;

}//main




