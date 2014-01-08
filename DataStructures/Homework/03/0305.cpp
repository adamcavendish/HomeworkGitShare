#include "../List/List"
#include <cstring>
#include <iostream>
using namespace adamcavendish::data_structure;

int main(int argc, char * argv[])
{
	if(argc != 3)
		return 1;

	List<char> t1(&argv[1][0], &argv[1][strlen(argv[1])]);
	List<char> t2(&argv[2][0], &argv[2][strlen(argv[2])]);

	auto bgn1 = t1.begin();
	auto bgn2 = t2.begin();
	auto end1 = t1.cend();
	auto end2 = t2.cend();

	while(bgn1 != end1 && bgn2 != end2)
	{
		if(*bgn1 == *bgn2) {
			bgn1 = t1.erase(bgn1);
			bgn2 = t2.erase(bgn2);
		} else {
			++bgn1;
			++bgn2;
			break;
		}//if-else
	}//while

	std::cout << "testA: " << std::endl;
	for(auto i : t1)
		std::cout << i << ' ';
	std::cout << std::endl;

	std::cout << "testB: " << std::endl;
	for(auto i : t2)
		std::cout << i << ' ';
	std::cout << std::endl;
			
	return 0;
}//main

