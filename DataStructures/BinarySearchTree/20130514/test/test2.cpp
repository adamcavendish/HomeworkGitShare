#include "../BinarySearchTree"
#include <iostream>
#include <utility>
#include <string>

typedef adamcavendish::container::BinarySearchTree<std::size_t, std::size_t> MAP;

int main()
{
	MAP a;
	a[86] = 1;
	a[75] = 2;
	a[46] = 3;
	a[11] = 4;
	a[17] = 5;
	a[23] = 6;
	a[71] = 7;
	a[68] = 8;
	a[39] = 9;
	a[8] = 10;
	a[34] = 11;
	a[99] = 12;

	a.traverse();
	std::cout << "----------" << std::endl;

	std::size_t cnt = 0;
	for(auto i = a.begin(); i != a.end(); ++i) {
		//std::cout << i._M_node << std::endl;
		std::cout << i->first << ' ' << i->second << std::endl;
		++cnt;
		if(cnt == 20)
			break;
	}//for
	std::cout << "----------" << std::endl;
	std::cout << "B: " << std::endl;

	MAP b(a);

	b.traverse();
	std::cout << "----------" << std::endl;

	cnt = 0;
	for(auto i = b.begin(); i != b.end(); ++i) {
		//std::cout << i._M_node << std::endl;
		std::cout << i->first << ' ' << i->second << std::endl;
		++cnt;
		if(cnt == 20)
			break;
	}//for

	std::cout << "----------" << std::endl;
	std::cout << "Test Erase: " << std::endl;

	/*
	auto finding = b.insert(std::make_pair(68, 0));
	auto titer = b.erase(finding.first);

	cnt = 0;
	for(auto i = titer; i != b.end(); ++i) {
		//std::cout << i._M_node << std::endl;
		std::cout << i->first << ' ' << i->second << std::endl;
		++cnt;
		if(cnt == 20)
			break;
	}//for
	*/
	for(auto i = b.begin(); i != b.end();) {
		i = b.erase(i);
		for(auto j : b)
			std::cout << j.first << ' ';
		std::cout << std::endl;
	}//for

	return 0;
}//main

