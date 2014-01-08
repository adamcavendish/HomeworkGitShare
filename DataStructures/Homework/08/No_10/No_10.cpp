#include <list>
#include <iostream>
#include <utility>
#include <string>
#include <fstream>
#include <iterator>

typedef std::list<int>::const_iterator iter;

iter
search(const std::list<int> & li, const int num) {
	static iter sp = li.cbegin();	// last time found
	const static iter iter_end = li.cend();

	if(sp == iter_end)
		sp = li.cbegin();

	while(*sp != num && sp != iter_end) {
		if(*sp > num) {
			--sp;
			if(*sp < num)
				sp = iter_end;
		} else {
			++sp;
			if(*sp > num)
				sp = iter_end;
		}//if-else
	}//while

	return sp;
}//search

int main()
{
	std::ifstream in("No_10.in");

	std::list<int> ll(
			(std::istream_iterator<int>(in)),
			std::istream_iterator<int>());
	ll.sort();

	std::cout << "LIST: ";
	for(auto i : ll) std::cout << i << ' ';
	std::cout << std::endl;

	int num_to_find;
	while(1) {
		if(!(std::cin >> num_to_find))
			break;
		
		auto ret  = search(ll, num_to_find);
		if(ret == ll.cend()) {
			std::cout << "Not found!" << std::endl;
		} else {
			std::cout << "Pos: " << std::distance(ll.cbegin(), ret)
				<< std::endl;
		}//if-else
	}//while

	in.close();
	return 0;
}//main

