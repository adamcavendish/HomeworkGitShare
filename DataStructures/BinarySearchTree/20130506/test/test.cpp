#include "../BinarySearchTree"

#include <iostream>
#include <map>
#include <string>
#include <utility>

using namespace adamcavendish::container;

//typedef std::map<std::string, std::size_t> MAP;
typedef BinarySearchTree<std::string, std::size_t> MAP;

int main()
{
	MAP b;
	b["Hello"] = 100;
	b["World"] = 1000;

	std::string ss = "";
	for(auto i = 0; i < 26; ++i) {
		ss += char('a' + i);
		b[ss] = i;
	}//for

	ss = "";
	for(auto i = 0; i < 26; ++i) {
		ss += char('A' + i);
		b[ss] = i+100;
	}//for

	std::cout << "size: " << ss.size() << std::endl;
	for(auto i : b) {
		std::cout << i.first << ' ' << i.second << std::endl;
	}

	std::cout << b["Hello"] << std::endl;
	std::cout << b["World"] << std::endl;

	return 0;
}//main

