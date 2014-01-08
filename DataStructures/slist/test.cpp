//#include <ext/slist>
#include "slist"
#include <iostream>
using namespace __gnu_cxx;

int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	const slist<int> sl(arr, arr + sizeof(arr)/sizeof(arr[0]));
	
	for(auto i : sl)
		std::cout << i << ' ';
	std::cout << std::endl;

	auto iter = sl.begin();
	++iter;
	++iter;
	iter = sl.previous(iter);

	std::cout << *iter << std::endl;

	iter._M_node = __slist_reverse(iter._M_node);

	for(auto i : sl)
		std::cout << i << ' ';
	std::cout << std::endl;

	std::cout << *iter << std::endl;

	return 0;
}//main

