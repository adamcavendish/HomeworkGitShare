// STL
#include <iostream>
#include <iomanip>
// numerical
#include <cube_root/cube_root.hpp>

int main()
{
	long double est;
	long double x;
	long double result;
	while(true) {
		std::cout << "Estimation: ";
		std::cin >> est;
		std::cout << "x: ";
		std::cin >> x;
		if(!std::cin)
			break;

		result = numerical::cube_root<long double>(x, est, 1e-10);

		std::cout << "cube_root(" << x << "): ";
		std::cout << std::setprecision(std::numeric_limits<long double>::digits10) << result << std::endl;
	}//while
}//main

