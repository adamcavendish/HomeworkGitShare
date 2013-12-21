#include <iostream>

int main()
{
	char right = 'a';
	std::cout << (int *)(&right) << std::endl;

	char * a = (char *)(0x7fffb7b29ac0);

	char c = *a;
	std::cout << c << std::endl;

	return 0;
}//main
