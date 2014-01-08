#include <iostream>
using namespace std;

class A
{
public:
	virtual void foo() { cout << "A::foo" << endl; }
};

class B : public A
{
public:
	void foo() { cout << "B::foo" << endl; }
};

int main()
{
	B b;
	b.foo();

	return 0;
}//main

