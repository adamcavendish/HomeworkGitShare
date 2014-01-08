#include <iostream>
#include "../ICase_String"
using namespace std;

int main()
{
	ICase_String s1("Hello");
	ICase_String s2("heLLo");

	if(s1 == s2)
		cout << "s1 == s2" << endl;
	else
		cout << "s1 != s2" << endl;

	return 0;
}//main

