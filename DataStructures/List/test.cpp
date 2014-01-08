#include "List"
#include <list>
#include <string>
#include <iostream>

using namespace adamcavendish::data_structure;

template <typename T>
void print(const List<T> & ll) {
	for(auto i:ll)
		std::cout << i << ' ';
	std:: cout << "||||| ";
	for(typename List<T>::const_reverse_iterator i = ll.rbegin();
			i != ll.rend();
			++i)
		std::cout << *i << ' ';
	std::cout << std::endl;
}//print(List)

int main()
{
	List<int> l1;
	print(l1);
	for(int i = 0; i < 10; ++i) {
		l1.push_front(i);
	}//for
	for(int i = 1024; i < 1035; ++i) {
		l1.push_back(i);
	}//for
	print(l1);
	
	List<int> l2({2, 4, 6, 8, 10});
	print(l2);

	List<int> l3(l1.begin(), l1.end());
	print(l3);

	l3 = l2;
	print(l3);

	l3.insert(l3.end(), {11, 12, 13, 14, 15});
	print(l3);

	std::cout << "--------" << std::endl;

	l3.pop_front();
	l3.pop_back();
	print(l3);

	while(!l3.empty())
		l3.pop_front();
	print(l3);

	return 0;
}//main

