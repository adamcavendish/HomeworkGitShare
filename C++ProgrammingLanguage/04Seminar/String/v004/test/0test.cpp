#include "../Core/base_string.hpp"
#include <iostream>
using namespace std;

int main()
{
	base_string<64> s("Hello");
	
	s[4] = '!';
	cout << "s0:" << s[0] << endl;

	s = "World!";
	for(size_t i = 0; i < s.size(); ++i)
		cout << s[i];
	cout << endl;

	return 0;
}//main

