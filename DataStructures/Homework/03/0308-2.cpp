#include "slist"
#include <cstring>
#include <iostream>

int main(int argc, char * argv[])
{
	__gnu_cxx::slist<char> li(&argv[1][0], &(argv[1][strlen(argv[1])]));

	if(argc != 3)
		return 1;

	std::cout << "SList: ";
	for(__gnu_cxx::slist<char>::iterator i = li.begin();
			i != li.end();
			++i)
		std::cout << *i;
	std::cout << std::endl;

	li.remove(argv[2][0]);

	for(__gnu_cxx::slist<char>::iterator i = li.begin();
			i != li.end();
			++i)
		std::cout << *i;
	std::cout << std::endl;

	return 0;
}//main

