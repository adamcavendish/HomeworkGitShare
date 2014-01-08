#include <iostream>
#include <string>
#include <fstream>
#include <utility>

/*
 * Max swap times: N-1
 * @Example: 0 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1
 */

void
split_negative(int * arr, const std::size_t arr_len) {
	for(std::size_t i = 0lu, neg_pos_next = 0lu; i != arr_len; ++i) {
		if(arr[i] < 0) {
			if(i != neg_pos_next)
				std::swap(arr[i], arr[neg_pos_next]);
			++neg_pos_next;
		}//if
	}//for
}//split_negative

int main()
{
	std::ifstream in("data.in");
	// Get array length
	std::size_t arr_len;
	in >> arr_len;
	// Get array
	int * arr = new int[arr_len];
	for(auto i = 0lu; i < arr_len; ++i)
		in >> arr[i];
	if(!in) {
		std::cerr << "Check data.in!" << std::endl;
		in.close();
		return EXIT_FAILURE;
	}//if

	for(auto i = 0lu; i != arr_len; ++i)
		std::cout << arr[i] << ' ';
	std::cout << std::endl;

	split_negative(arr, arr_len);

	for(auto i = 0lu; i != arr_len; ++i)
		std::cout << arr[i] << ' ';
	std::cout << std::endl;
 
	delete[] arr;
	in.close();

	return 0;
}//main

