#include "stkque"

#include <iostream>

using namespace adamcavendish::data_structure;

int main()
{
	stkque<int> ll;

	ll.push_in(2);
	ll.push_in(3);
	ll.push_in(1);
	ll.push_in(4);
	std::cout << ll.pop_out() << ' ';
	std::cout << ll.pop_out() << ' ';
	std::cout << std::endl;

	ll.push_in(5);
	ll.push_in(8);

	while(!ll.empty())
		std::cout << ll.pop_out() << ' ';

	std::cout << std::endl;

	return 0;
}//main

