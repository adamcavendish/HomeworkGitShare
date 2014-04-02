#include <iostream>

int main() 
{
	int a = 0x12345678;
	char* b = (char*)&a;

	if(*b == 0x78) {
		std::cout << "Little Endian" << std::endl;
	} else {
		std::cout << "Big Endian" << std::endl;
	}//if-else

	for(int i = 0; i < 4; ++i, ++b)
		std::cout << std::hex << (int)(*b) << ' ';
	std::cout << std::endl;


	return 0;
}//main

