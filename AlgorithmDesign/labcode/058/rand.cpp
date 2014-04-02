#include <iostream>
#include <cstdlib>
#include <ctime>

const int testsz = 20;

int main()
{
	srand(time(nullptr));

	std::cout << testsz << std::endl;
	for(auto i = 0; i < testsz; ++i) {
		auto num = rand() % 50 + 1;
		std::cout << num << std::endl;

		for(auto j = 0; j < num; ++j) {
			std::cout << rand() % 50 + 1 << ' ';
		}//for
		std::cout << std::endl;
	}//for

	return 0;
}//main

