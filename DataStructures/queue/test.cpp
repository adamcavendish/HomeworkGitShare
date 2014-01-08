#include "stack"

#include <iostream>
#include <list>

using namespace adamcavendish::data_structure;

int main()
{
	stack<int> s;

	for(int i = 0; i < 100; ++i)
		s.push(i);

	while(!s.empty()) {
		std::cout << s.top() << ' ';
		s.pop();
	}//while
	std::cout << std::endl;

	return 0;
}//main

