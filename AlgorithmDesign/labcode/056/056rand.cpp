#include <iostream>
#include <cstdlib>
#include <ctime>

const int testsz = 20;

int main()
{
	srand(time(nullptr));

	std::cout << testsz << std::endl;
	for(auto i = 0; i < testsz; ++i) {
		auto num = rand() % 50;
		std::cout << num << ' ';
		auto num2 = rand() % 8 + 2;
		std::cout << num2 << std::endl;

		for(auto j = 0; j < num; ++j) {
			std::cout << (char)('a' + rand() % 26) << ' ';
		}//for
		std::cout << std::endl;
		for(auto j = 0; j < num2; ++j) {
			std::cout << (char)('a' + rand() % 26) << ' ';
		}//for
		std::cout << std::endl;
	}//for

	return 0;
}//main

