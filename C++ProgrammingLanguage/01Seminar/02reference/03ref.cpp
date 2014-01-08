/**
 * @file 03ref.cpp
 *	R-Value reference
 * @IMPORTANT!
 *		This is a new feature in C++11, compile with g++ -std=c++0x
 */

#include <iostream>

// iostream
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	int data1 = 1;
	int data2 = 2;

	int && data12ref = data1 + data2;
	
	cout << "data1: " << data1 << endl;
	cout << "data2: " << data2 << endl;
	cout << "data1 + data2: " << data1 + data2 << endl;
	cout << "data12ref: " << data12ref << endl;
	
	data12ref = 4;

	cout << "data1: " << data1 << endl;
	cout << "data2: " << data2 << endl;
	cout << "data1 + data2: " << data1 + data2 << endl;
	cout << "data12ref: " << data12ref << endl;
	
	return 0;
}//main

