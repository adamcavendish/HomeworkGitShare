#include "../String"

#include <iostream>
using namespace std;

int main()
{
	String s("What? ");
	String s1(s);
	s1 += s;
	cout << "s: " << &s << endl;
	cout << "s1: " << &s1 << endl;

	cout << "1 ostream" << endl;
	cout << "s: " << s << endl;
	cout << "s1: " << s1 << endl;
	cout << endl;

	cout << "2 operator+=char *" << endl;
	for(int i = 0; i < 20; ++i)
		s += "Hello World!";
	cout << "s: " << s << endl;
	cout << endl;

	cout << "3 operator+=String" << endl;
	s += s1;
	cout << s << endl;
	cout << endl;

	cout << "4 operator=char *" << endl;
	s = "What is the String doing?";
	cout << "s: " << s << endl;
	cout << endl;

	cout << "5 operator=String" << endl;
	s = s1;
	cout << "s: " << s << endl;
	cout << endl;

	cout << "6 compare" << endl;
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
	s = "abcd";
	s1 = "abc";
	cout << "s: " << s << endl;
	cout << "s1: " << s1 << endl;
	if(s > s1)
		cout << "s > s1" << endl;
	cout << endl;

	cout << "7 move constructor" << endl;
	String s2(s + s1);
	cout << "s: " << s << endl;
	cout << "s1: " << s1 << endl;
	cout << "s + s1: " << s2 << endl;
	cout << endl;

	cout << "8 move assign" << endl;
	s = s1 + " Hey Guy!" + s1;
	cout << s << endl;
	cout << endl;

	return 0;
}//main

