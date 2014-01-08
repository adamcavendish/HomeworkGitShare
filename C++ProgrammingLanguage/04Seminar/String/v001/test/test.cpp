#include "../String"
#include <iostream>
using namespace std;

int main()
{
	String s("What? ");
	String s1(" is it!?");
	cout << "s: " << &s << endl;
	cout << "s1: " << &s1 << endl;

	cout << "1" << endl;
	cout << s << endl;
	cout << endl;

	cout << "2" << endl;
	for(int i = 0; i < 20; ++i)
		s += "Hello World!";
	cout << s << endl;
	cout << endl;

	cout << "3" << endl;
	s += s1;
	cout << s << endl;
	cout << endl;

	cout << "4" << endl;
	s = "What is the String doing?";
	cout << s << endl;
	cout << endl;

	s = "ABC";
	s1 = "abc";
	cout << "s:" << s << endl;
	cout << "s1: " << s1 << endl;
	if(s < s1)
		cout << "s < s1" << endl;
	cout << endl;

	s = "abc";
	s1 = "abc";
	cout << "s:" << s << endl;
	cout << "s1: " << s1 << endl;
	if(s == s1)
		cout << "s == s1" << endl;
	cout << endl;

	return 0;
}//main

