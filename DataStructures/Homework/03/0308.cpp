#include <ext/slist>
//#include "slist"
#include <cstring>
#include <iostream>

int main(int argc, char * argv[])
{
	__gnu_cxx::slist<char> li;

	if(argc != 3)
		return 1;

	for(char * i = &argv[1][0]; *i; ++i) {
		li.push_front(*i);
	}//for

	std::cout << "SList: ";
	for(auto i : li)
		std::cout << i << ' ';
	std::cout << std::endl;

	li.remove(argv[2][0]);

	for(auto i : li)
		std::cout << i << ' ';
	std::cout << std::endl;

	return 0;
}//main

