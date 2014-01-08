#include <string>

std::string getName()
{
	std::string s("Mary");
	return s;
}//getName()

std::string name = getName();
// 一个临时对象，但想找到它？没门儿！



// 如果你想要程序的执行效率更好一点？那试试引用吧！
const std::string & name = getName();	// Ok
// 但是你不能这样：
std::string & name = getName();	//NOT ok
// Hey, 别对快死的人动武！！！


// R-Value Reference 右值引用
const std::string && name = getName();	// Ok
std::string && name = getName();	// Also Ok! 别惊讶，编译器开始支持了！

// A DOOR!
std::string me("Adam");
void ref(const std::string & s);
void ref(std::string && s);

