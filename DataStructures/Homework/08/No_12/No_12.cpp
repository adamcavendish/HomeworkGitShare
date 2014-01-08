#include "/files/Nutstore/000/CPPWorkSpace/SHUCourse/DataStructures/BinarySearchTree/20130514/BinarySearchTree"

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <iterator>
#include <map>

using namespace adamcavendish::container;

std::istream & operator>>(std::istream & in, std::pair<int, int> & pa)
{ in >> pa.first >> pa.second; return in; }

std::istream & operator>>(std::istream && in, std::pair<int, int> & pa)
{ in >> pa.first >> pa.second; return in; }

int main()
{
	std::ifstream in("No_12.in");

	BinarySearchTree<int, int> bst;
	while(true) {
		std::pair<int, int> pa;
		in >> pa;
		if(in.eof())
			break;
		bst.insert(pa);
	}//while
	/*
	bst.insert((std::istream_iterator<std::pair<int, int> >(in)),
			std::istream_iterator<std::pair<int, int> >());
	*/

	for(auto iter = bst.begin(); iter != bst.end(); ++iter)
		std::cout << iter->first << ' ';
	std::cout << std::endl;

	int find_num;

	std::cout << "What to find?" << std::endl;
	std::cin >> find_num;

	auto less_than_num = bst.end();
	auto greater_than_num = bst.end();

	for(auto iter = bst.begin(); iter != bst.end(); ++iter) {
		if(iter->first < find_num) {
			less_than_num = iter;
		} else if(iter->first == find_num) {
			greater_than_num = ++iter;
			break;
		} else {
			greater_than_num = iter;
			break;
		}//if-else
	}//for

	if(less_than_num == bst.end()) {
		std::cout << "No data is less than " << find_num << std::endl;
	} else {
		std::cout << "Data less than " << find_num << " is: "
			<< less_than_num->first << std::endl;
	}//if-else

	if(greater_than_num == bst.end()) {
		std::cout << "No data is greater than " << find_num << std::endl;
	} else {
		std::cout << "Data greater than " << find_num << " is: "
			<< greater_than_num->first << std::endl;
	}//if-else

	return 0;
}//main

