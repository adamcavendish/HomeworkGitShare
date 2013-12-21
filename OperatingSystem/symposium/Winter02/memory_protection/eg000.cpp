#include <iostream>

int main()
{
	char * p = static_cast<char *>(0x0000);

	std::cout << *p << std::endl;

	return 0;
}//main

