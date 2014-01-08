#include <iostream>

// iostream
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	int data1 = 1;
	int data2 = 2;
	int *data3 = new int(4);

	int &data1ref = data1;

	cout << "data1ref: " << data1ref << endl;
	cout << "data1: " << data1 << endl;

	data1ref = 32;

	cout << "data1ref: " << data1ref << endl;
	cout << "data1: " << data1 << endl;
	
	int &data3ref = *data3;
	cout << "data3: " << *data3 << endl;
	cout << "data3ref: " << data3ref << endl;
	data3ref = 64;
	cout << "Assignmen: " << endl;
	cout << "data3: " << *data3 << endl;
	cout << "data3ref after assignment: " << data3ref << endl;

	//int &data4ref = 16;
	//cout << "data4ref: " << data4ref << endl;

	delete data3;

	return 0;
}//main

