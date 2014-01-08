#include <iostream>
#include <utility>

class Foo
{
public:
	Foo(): _x(0) { std::cout << this << ": df cons" << std::endl; }
	Foo(const Foo & rhs):
		_x(rhs._x)
	{ std::cout << this << ": copy cons" << std::endl; }
	Foo(Foo && rhs):
		_x(rhs._x)
	{ std::cout << this << ": move cons" << std::endl; }

	~Foo() { std::cout << this << ": des" << std::endl; }

	int getX() const { return _x; }
	void setX(int x) { this->_x = x; }

private:
	int _x;
}; //class Foo

Foo operator+(const Foo & lhs, const int & rhs)
{
	Foo f(lhs);
	f.setX(lhs.getX() + rhs);

	return f;
}//+(lhs, rhs)

int main()
{
	Foo f1;

	Foo f2(f1 + 1);

	return 0;
}//main

