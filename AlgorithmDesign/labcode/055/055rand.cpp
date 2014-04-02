#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
	srand(time(nullptr));

	for(auto i = 0; i < 10; ++i) {
		auto num = rand() % 8 + 2;
		std::cout << num << '\t';
		for(auto j = 0; j < num + 1; ++j) {
			std::cout << rand() % 99 + 1 << ' ';
		}//for
		std::cout << std::endl;
	}//for

	return 0;
}//main

