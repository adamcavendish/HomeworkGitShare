#include <iostream>
#include <string>

void ref(const std::string & s)
{
	std::cout << s << "是通过普通引用的门进来的！" << std::endl;
}//ref(s)

void ref(std::string && s)
{
	std::cout << s << "是通过右值引用的大门进来的～！是在临时对象里面 - =!" << std::endl;
}//ref(s)

std::string getName()
{
	std::string s("Mary");
	return s;
}//getName()

int main()
{
	std::string me("Adam");

	std::cout << "ref(me):" << std::endl;
	ref(me);

	std::cout << "ref(getName()):" << std::endl;
	ref(getName());

	return 0;
}//main

