#include "tree.hpp"

#include <iostream>
#include <functional>

void
print(tree_node<char> * __pa, tree_node<char> * __pb) {
	std::cout << '(' << __pa->_M_data << ',' << __pb->_M_data << ')'
		<< std::endl;
}//print

int main()
{
	// See Page 190
	Tree<char> __tree {
		'A',
		'B',					NE ,
		'E',		'C',		NE ,		NE ,
		NE , 'F',	'G', 'D',	NE , NE ,	NE ,  NE
	};
	
	if(__tree._M_head->_M_lnode == nullptr) {
		std::cout << "Only Head in Tree!" << std::endl;
		return 0;
	}//if

	auto __search_func =
		[=](tree_node<char> * __parent)
	{
		if(__parent->_M_lnode == nullptr)
			return;

		for(auto __child = __parent->_M_lnode;
				__child != nullptr; __child = __child->_M_rnode)
		{
			print(__parent, __child);
		}//for
	};//lambda __search_func

	__tree.preorder(__search_func);

	return 0;
}//main

