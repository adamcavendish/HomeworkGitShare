#include "kmp"

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstddef>

using adamcavendish::algorithm::kmp;

int main(int argc, char * argv[])
{
	if(argc != 3) {
		std::cerr << "Usage: " << argv[0]
			<< " target_string pattern" << std::endl;
		exit(1);
	}//if

	std::cout << kmp(argv[1], argv[2]) << std::endl;

	return 0;
}//main

