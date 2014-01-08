#include <iostream>
#include <fstream>
#include <string>
#include <utility>

#include <boost/scope_exit.hpp>

enum FLAG_COLOR: std::size_t {
	RED = 0,
	WHITE,
	BLUE
};

void
make_flag(int * arr, const std::size_t arr_len) {
	std::size_t red_pos = 0lu;
	std::size_t blue_pos = arr_len - 1;
	for(; red_pos < arr_len && arr[red_pos] == FLAG_COLOR::RED; ++red_pos);
	for(; blue_pos > 0 && arr[blue_pos] == FLAG_COLOR::BLUE; --blue_pos);
	for(std::size_t i = red_pos; i <= blue_pos;) {
		if(arr[i] == FLAG_COLOR::RED) {
			if(i != red_pos)
				std::swap(arr[i], arr[red_pos]);
			++red_pos;
			++i;
		} else if(arr[i] == FLAG_COLOR::BLUE) {
			if(i != blue_pos)
				std::swap(arr[i], arr[blue_pos]);
			--blue_pos;
		} else {
			++i;
		}//if-else
	}//for
}//make_flag(arr, arr_len)

int main()
{
	std::fstream in("data.in");

	BOOST_SCOPE_EXIT(&in) {
		in.close();
	} BOOST_SCOPE_EXIT_END
	
	// Get array length
	std::size_t arr_len;
	in >> arr_len;
	// Get array
	int * arr = new int[arr_len];
	for(auto i = 0lu; i < arr_len; ++i) {
		in >> arr[i];
		if(arr[i] < 0 || arr[i] > 2 || !in) {
			std::cerr << "Check data.in!" << std::endl;
			return EXIT_FAILURE;
		}//if
	}//for

	for(auto i = 0lu; i != arr_len; ++i)
		std::cout << arr[i] << ' ';
	std::cout << std::endl;

	make_flag(arr, arr_len);

	for(auto i = 0lu; i != arr_len; ++i)
		std::cout << arr[i] << ' ';
	std::cout << std::endl;

	return 0;
}//main

