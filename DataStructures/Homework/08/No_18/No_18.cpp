#include "/files/Nutstore/000/CPPWorkSpace/SHUCourse/DataStructures/BinarySearchTree/20130514/BinarySearchTree"

#include <iostream>
#include <string>
#include <fstream>

using namespace adamcavendish::container;

std::istream & operator>>(std::istream & in, std::pair<int, int> & pa)
{ in >> pa.first >> pa.second; return in; }

int main()
{
	std::ifstream in("1.in");

	BinarySearchTree<int, int> bst;

	while(true) {
		std::pair<int, int> pa;
		in >> pa;
		if(in.eof())
			break;
		bst.insert(pa);
	}//while

	std::cout << "1st BST: " << std::endl;
	for(auto i : bst)
		std::cout << i.first << ' ';
	std::cout << std::endl;
	
	in.close();

	in.open("2.in");
	
	BinarySearchTree<int, int> bst2;

	while(true) {
		std::pair<int, int> pa;
		in >> pa;
		if(in.eof())
			break;
		bst2.insert(pa);
	}//while

	std::cout << "2nd bst: " << std::endl;
	for(auto i : bst2)
		std::cout << i.first << ' ';
	std::cout << std::endl;

	for(auto i : bst2)
		bst.insert(i);

	std::cout << "Merged bst: " << std::endl;
	for(auto i : bst)
		std::cout << i.first << ' ';
	std::cout << std::endl;

	return 0;
}//main

