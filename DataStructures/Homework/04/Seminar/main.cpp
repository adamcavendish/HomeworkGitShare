#include "stkque/stkque"

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <stdexcept>

using adamcavendish::data_structure::stkque;

// in-file global stack queue and counter
static stkque<int> que;
static std::size_t counter = 0;

void helper(std::ostream & os, const int argc, char * const argv[])
{
	if(argc > 0) {
		if(argc != 2) {
			os << "Use " << argv[0] << " $push_pop_sequence to test"
				<< " the stack queue" << std::endl;
			os << "Use 'i' for push, 'o' for pop" << std::endl;
			os << "Example: " << argv[0] << " iiooiiiioo" << std::endl;
			exit(EXIT_FAILURE);
		}//if
	} else {
		throw std::runtime_error("argc is not correctly set!");
	}//if-else
}//helper

void ranged_test(const char * __first, const char * __last)
{
	for(; __first != __last; ++__first) {
		if(*__first == 'i') {
			std::cout << "in : " << counter << std::endl;
			que.push_in(counter++);
		} else if(*__first == 'o') {
			if(que.empty()) {
				std::cerr << "out: " << "queue empty!" << std::endl;
			} else {
				std::cout << "out: " << que.pop_out() << std::endl;
			}//if-else
		} else {
			std::cerr
				<< "Error operation type: '"
				<< *__first
				<< "'"
				<< std::endl;
		}
	}//for
	std::cout << std::endl;
}//ranged_test(range_first, range_end)

void pause()
{
	std::cout << "Press Enter to continue ... " << std::endl;
	std::cin.get();
}//pause()

int main(int argc, char * argv[])
{
	helper(std::cout, argc, argv);

	const char * iter_bgn = std::addressof(argv[1][0]);
	const char * iter_end = std::addressof(argv[1][strlen(argv[1])]);

	ranged_test(iter_bgn, iter_end);
	
	pause();
	return EXIT_SUCCESS;
}//main

