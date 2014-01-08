#include <iostream>

// iostream
using std::cout;
using std::endl;

template <class DataType>
void swap1(DataType &a, DataType &b)
{
	DataType temp(a);
	a = b;
	b = temp;
}//swap1(a, b)

template <class DataType>
void swap2(DataType *a, DataType *b)
{
	DataType temp(*a);
	*a = *b;
	*b = temp;
}//swap2(a, b)

int main()
{
	int a = 100, b = 0;
	swap1(a, b);
	cout << "a = " << a << " b = " << b << endl;

	char c = 'a', d = 'b';
	swap2(&c, &d);
	cout << "c = " << c << " d = " << d << endl;

	return 0;
}//main

