#include "tree.hpp"

#include <iostream>
#include <functional>

int main()
{
	// P187
	// ANSWER: ABEFKLCGDHIMNJ
	Tree<char> tt = {
		{'A',	'B',	'C',	'D',	'E',	'F',	'G',	'H',	'I',	'J',	'K',	'L',	'M',	'N'},
		{-1,	0,		0,		0,		1,		1,		2,		3,		3,		3,		5,		5,		8,		8}};
	
	tt.preorder([=](tree_node<char> * __node) { std::cout << __node->_M_data; });
	std::cout << std::endl;

	return 0;
}//main

