#include <iostream>
#include <string>
#include <utility>

/*
 * Just use the Code on Page 301
 * Only changes are made to branch the quicksort recursion
 */
void
quicksort_impl(int * array, const int low, const int high, const int k) {
	int i = low, j = high;
	int temp = array[low];
	if(i < j) {
		while(i < j) {
			while(i < j && temp < array[j])
				--j;
			if(i < j) {
				array[i] = array[j];
				++i;
			}//if
			while(i < j && temp >= array[i])
				++i;
			if(i < j) {
				array[j] = array[i];
				--j;
			}//if
		}//while
		array[i] = temp;

		// only changes are made here. Take a look
		if(i < k) {
			quicksort_impl(array, i+1, high, k);
		} else if(i > k) {
			quicksort_impl(array, low, i-1, k);
		}//if-else
	}//if
}//quicksort_impl(array, low, high, k)


int main()
{
	// Variables
	const int max_num = 1024;
	int array[max_num];
	int k;
	int counter = 0;

	// Get array input
	std::cout << "Input An Integer Array, Ctrl+Z to end: " << std::endl;
	while(std::cin >> array[counter++] && counter < max_num);
	std::cin.clear();
	--counter;

	std::cout << "The array is: " << std::endl;
	for(int i = 0; i < counter; ++i)
		std::cout << array[i] << ' ';
	std::cout << std::endl;
	
	while(true) {
		// Get k for kth element
		std::cout << "You inputed " << counter << " integers." << std::endl;
		std::cout << "Input k to find the kth element (k starts from 0): ";
		std::cin >> k;
		if(k < counter) {
			break;
		} else {
			std::cout << "Invalid k, please try again." << std::endl;
		}//if-else
	}//while
		
	// sort [0, k] elements in array
	quicksort_impl(array, 0, counter-1, k);

	for(int i = 0; i < counter; ++i)
		std::cout << array[i] << ' ';
	std::cout << std::endl;

	return 0;
}//main

