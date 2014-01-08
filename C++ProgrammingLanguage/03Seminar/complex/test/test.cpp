#include "../Complex"

#include <iostream>
using namespace std;

int main()
{
	const Complex<int, int> c1(10, -20);
	const Complex<int, double> c2(15, 3.1);
	Complex<double, double> c3(0, 0);
	Complex<int, int> c4(0, 0);

	cout << (c3 += c1) << endl;
	cout << (c3 += c2) << endl;

	cout << (c4 += c1) << endl;
	cout << (c4 += c2) << endl;
	return 0;
}//main

