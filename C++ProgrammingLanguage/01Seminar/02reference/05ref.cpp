/**
*	@file 05ref.cpp
*	@IMPORTANT!
*		A a{1, 100, 1000} -- This is a new feature in C++11, compile with g++ -std=c++0x
*/

#include <iostream>
using std::cout;
using std::endl;

struct A
{
	int data1;
	int data2;
	int data3;
}; //struct A

void print(const A &a)
{
	cout << a.data1 << endl;
	cout << a.data2 << endl;
	cout << a.data3 << endl;
}//print(A)

int main()
{
	A a{1, 100, 1000};
	
	print(a);
	
	return 0;
}//main
