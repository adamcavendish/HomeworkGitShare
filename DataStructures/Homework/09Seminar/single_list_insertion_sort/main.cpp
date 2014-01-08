#include "forward_list"
#include <iostream>
#include <iomanip>
#include <string>
#include <random>

int main(int argc, char * argv[])
{
	dummy::forward_list<int> ll;

	if(argc == 1) {
		std::cerr << "Usage: " << argv[0] << " numbers to sort"
			<< std::endl;
		return EXIT_FAILURE;
	}//if

	if(argc == 2) {
		if(std::string(argv[1]) == "--random") {
			std::random_device rd;
			std::default_random_engine engine(rd());

			// MAKE 100 RANDOMS FROM 1 to 100000
			std::uniform_int_distribution<int> uniform_dis(1, 100000);
			for(auto i = 0; i < 100; ++i)
				ll.push_front(uniform_dis(engine));
		} else {
			std::cerr << "Usage: " << argv[0] << " --random"
				<< std::endl;
			return EXIT_FAILURE;
		}//if-else
	}//if

	if(argc > 3) {
		for(auto i = argc-1; i >= 1; --i)
			ll.push_front(std::stoi(argv[i]));
	}//if

	std::cout << "Before Sort: " << std::endl;

	int dummy_counter = 0;
	for(auto i : ll) {
		std::cout << std::setw(6) << i << ' ';
		++dummy_counter;
		if(dummy_counter % 10 == 0)
			std::cout << std::endl;
	}//for
	std::cout << std::endl;

	ll.sort();

	std::cout << "After Sort: " << std::endl;

	dummy_counter = 0;
	for(auto i : ll) {
		std::cout << std::setw(6) << i << ' ';
		++dummy_counter;
		if(dummy_counter % 10 == 0)
			std::cout << std::endl;
	}//for
	std::cout << std::endl;

	return 0;
}//main

