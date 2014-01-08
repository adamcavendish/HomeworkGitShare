#include <iostream>
#include <string>
#include <vector>
#include <utility>

struct Small
{
	int _x;
	int _y;
};//struct Small

class Big
{
public:
	explicit Big(std::string name):
		_s(new Small{0, 0}),
		_name(name)
	{
		std::cout << _name << " 被构造了" << std::endl;
	}//default constructor
	
	// Copy Constructor
	Big(const Big & rhs):
		_s(new Small{rhs._s->_x, rhs._s->_y}),
		_name(rhs._name)
	{
		std::cout << _name << " 被拷贝了" << std::endl;
	}//copy constructor
	
	// Big(const Big && rhs) // ok, 但很少有能够说的通的

	// Move Constructor
	Big(Big && rhs):
		_s(rhs._s),
		_name(std::move(rhs._name))
	{
		std::cout << _name << " 被Move构造了" << std::endl;
		rhs._s = nullptr;
	}//move constructor

	// Copy Assignment
	Big & operator=(const Big & rhs) {
		std::cout << rhs._name << " 被拷贝赋值了" << std::endl;

		if(this == &rhs)
			return *this;
		delete _s;
		_s = new Small;
		_s->_x = rhs._s->_x;
		_s->_y = rhs._s->_y;
		_name = rhs._name;
		return *this;
	}//copy assignment

	// Move Assignment
	Big & operator=(Big && rhs) {
		std::cout << rhs._name << " 被Move赋值了" << std::endl;

		if(this == &rhs)
			return *this;
		delete _s;
		_s = rhs._s;
		_name = std::move(rhs._name);
		rhs._s = nullptr;
		return *this;
	}//move assignment
	
	~Big() {
		std::cout << this->_name << " 死了！" << std::endl;
		delete _s;
	}//destructor

	int getX() const { return _s->_x; }
	int getY() const { return _s->_y; }
	const std::string & getName() const { return _name; }

	void setX(const int & x) { _s->_x = std::move(x); }
	void setY(const int & y) { _s->_y = std::move(y); }
	void setName(const std::string & name) {
		_name = name;
		std::cout << "给 " << name << " 起名" << std::endl;
	}//setName(name)
private:
	Small *_s;
	std::string _name;
};//class Big

Big operator+(const Big & lhs, const int & rhs)
{
	std::cout << "*****在operator+里*****" << std::endl;
	Big b(lhs);
	b.setX(lhs.getX() + rhs);
	b.setY(lhs.getY() + rhs);
	std::cout << "*****operator+完成*****" << std::endl;

	return b;
}//operator+(Big, int)

Big makeBig(int new_x, int new_y, std::string new_name)
{
	Big b("makeBig临时变量");
	b.setX(new_x);
	b.setY(new_y);
	b.setName(new_name);

	return b;
}//makeBig(new_x, new_y, new_name)

void print(const Big & b)
{
	std::cout << "x=" << b.getX() << std::endl
		<< "y=" << b.getY() << std::endl
		<< "name=" << b.getName() << std::endl << std::endl;
}//print(Big)

int main()
{
	Big b0("b0");

	Big b1(b0);
	b1.setName("b1");
	std::cout << std::endl << "现在b1:" << std::endl;
	print(b1);

	Big b2(std::move(makeBig(1, 2, "临时b2") + 4));
	b2.setName("b2");
	std::cout << std::endl << "现在b2:" << std::endl;
	print(b2);

	Big b3("b3");
	b3 = b0;
	b3.setName("变量b3=b0");
	std::cout << std::endl << "现在b3:" << std::endl;
	print(b3);

	Big b4("b4");
	b4 = b0 + 8;
	b4.setName("变量b4=b0+8");
	std::cout << std::endl << "现在b4:" << std::endl;
	print(b4);

	std::cout << "-----------------------" << std::endl;

	std::vector<Big> *v = new std::vector<Big>;
	v->push_back(b0 + 16);
	std::cout << "1st push_back" << std::endl;

	v->push_back(makeBig(32, 64, "临时b5"));
	std::cout << "2nd push_back" << std::endl;

	v->push_back(makeBig(128, 256, "临时b6") + 512);
	std::cout << "3rd push_back" << std::endl;

	std::cout << std::endl << "释放vector<Big>内所有的资源:" << std::endl;
	delete v;

	std::cout << "-----------------------" << std::endl;
	
	std::cout << "程序到达终点，操作系统释放剩余的资源!" << std::endl;
	return 0;
}//main

