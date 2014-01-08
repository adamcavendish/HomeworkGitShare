#include <iostream>
#include <fstream>
#include <utility>
#include <string>

void
bubble_sort(int * array, int array_length) {
	bool swap_flag = true;

	for(int i = 0; i < array_length && swap_flag; i += 2) {
		swap_flag = false;
		for(int j = 0; j < array_length; ++j) {
			if(array[j] > array[j+1]) {
				std::swap(array[j], array[j+1]);
				swap_flag = true;
			}//if
		}//for

		if(swap_flag == false)
			break;

		for(int j = array_length-1; j > 0; --j) {
			if(array[j-1] > array[j]) {
				std::swap(array[j-1], array[j]);
				swap_flag = true;
			}//if
		}//for
	}//for
}//bubble_sort(array, array_length)

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

	bubble_sort(arr, arr_len);

	for(auto i = 0lu; i != arr_len; ++i)
		std::cout << arr[i] << ' ';
	std::cout << std::endl;
 
	delete[] arr;
	in.close();

	return 0;
}//main

