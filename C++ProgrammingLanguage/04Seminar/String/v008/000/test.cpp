#include <iostream>
#include <string>
#include <vector>

class Base
{
public:
	virtual void eq() { std::cout << x << " Base::eq()" << std::endl; }
	int x;
};//class Base

class Extend : public Base
{
public:
	virtual void eq() { std::cout << y << " Extend::eq()" << std::endl; }
private:
	int y;
};

int main()
{
	Base b;

	std::cout << sizeof(b) << std::endl;

	Extend e;

	std::cout << sizeof(e) << std::endl;

	std::cout << e.x << std::endl;

	return 0;
}//main

