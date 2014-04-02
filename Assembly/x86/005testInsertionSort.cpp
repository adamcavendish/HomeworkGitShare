#include <iostream>

typedef int T;

/*
int comp_int(const void * a, const void * b)
{
	T * ia = (T *)(a);
	T * ib = (T *)(b);
	return (*ia) - (*ib);
}
*/

int main()
{
	T arr[50];
	std::size_t arr_len = 0;
	
	std::cout << "Please input integers: " << std::endl;
	for(arr_len = 0; std::cin >> arr[arr_len] && arr_len < 50; ++arr_len);
	std::cin.clear();
	std::cout << "Arr_len: " << arr_len << std::endl;

	std::size_t int_sz = sizeof(T);
	asm(
		"movl	$F_compare_int, %%eax\n"
		"pushl	%%eax\n"
		"pushl	%[int_sz]\n"
		"pushl	%[arr_len]\n"
		"pushl	%[arr]\n"
		"call	F_insertion_sort32\n"
		:
		:[int_sz] "b" (int_sz), [arr_len] "c" (arr_len), [arr] "d" (arr));

	for(std::size_t i = 0; i < arr_len; ++i)
		std::cout << arr[i] << ',';
	std::cout << "\b " << std::endl;

	return 0;
}//main

