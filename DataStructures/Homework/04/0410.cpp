#include "../../slist/slist"

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>

template <typename T>
struct slist_queue : public __gnu_cxx::slist<T>
{
	typedef typename __gnu_cxx::slist<T>::value_type		value_type;
	typedef typename __gnu_cxx::slist<T>::reference			reference;
	typedef typename __gnu_cxx::slist<T>::const_reference	const_reference;

	reference back() {
		return this->front();
	}
	const_reference back() const {
		return this->front();
	}

	void push(const value_type & __x) {
		this->insert(this->end(), __x);
	}//push(__x)

	void pop() {
		this->pop_front();
	}//pop()

	void print() {
		for(auto i : *this)
			std::cout << i << ' ';
		std::cout << std::endl;
	}//print()
};//struct slist_queue

int main()
{
	std::cout << "construct slist_que" << std::endl;
	slist_queue<int> que;

	for(auto i = 0; i < 10; ++i) {
		que.push(i);
		que.print();
	}//for

	std::cout << "pop out one" << std::endl;
	que.pop();
	que.print();
	
	return 0;
}//main

