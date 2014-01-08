/**
 * @file 04ref.cpp
 */

#include <iostream>

// iostream
using std::cout;
using std::endl;

void swap2(int &a, int &b)
{
	int temp(a);
	a = b;
	b = temp;
}//swap2(int, int)

int main(int argc, char *argv[])
{
	int m = 100;
	int n = 0;
	
	cout << "Before swap: " << m << n << endl;
	swap2(m, n);
	cout << "After swap: " << m << n << endl;
	
	return 0;
}//main

