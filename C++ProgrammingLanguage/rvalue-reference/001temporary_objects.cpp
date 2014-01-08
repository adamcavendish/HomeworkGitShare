#include <iostream>
#include <vector>

std::vector<int> doubleValues(const std::vector<int> & v)
{
	std::vector<int> ret;
	for(auto i : v)
		ret.push_back(2 * i);
	return ret;
}//doubleValues(vector)

int main()
{
	std::vector<int> v;
	for(int i = 0; i < 100; ++i)
		v.push_back(i);
	
	v = doubleValues(v);

	for(auto i : v)
		std::cout << i << ' '; 

	return 0;
}//main

