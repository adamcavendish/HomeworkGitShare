// STL
#include <iostream>
#include <utility>
#include <string>
#include <stdexcept>
// Custom
#include "QuadraticSolver.hpp"

int main(int argc, char * argv[])
{
	while(true) {
		std::cout << "Please input a Quadratic Equation: " << std::endl;

		std::string equ;
		std::getline(std::cin, equ);

		QuadraticSolver s(equ);
		std::pair<double, double> ret;
		bool correct = true;

		try {
			ret = s.solve();
		} catch(std::logic_error & e) {
			correct = false;
			std::cerr << e.what() << std::endl;
		}//try-catch

		if(correct) {
			std::cout << "Result: " << std::endl;
			std::cout << "x1 = " << ret.first << std::endl;
			std::cout << "x2 = " << ret.second << std::endl;
		}//if
		std::cout << std::endl;
	}//while

	return 0;
}//main

