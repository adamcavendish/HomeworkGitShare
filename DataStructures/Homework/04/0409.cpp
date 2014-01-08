#include <cstdio>
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T = int, std::size_t _arr_size = 1024>
struct array_queue
{
	typedef T				value_type;
	typedef T *				pointer;
	typedef const T *		const_pointer;
	typedef T &				reference;
	typedef const T &		const_reference;
	typedef std::size_t		size_type;

	value_type	_M_array_queue[_arr_size];
	pointer		_M_front;
	size_type	_M_length;

	explicit array_queue() :
		_M_front(std::addressof(_M_array_queue[0]) - 1),
		_M_length(0)
	{}//default constructor

	constexpr const_pointer arrbegin() {
		return std::addressof(_M_array_queue[0]);
	}//begin()

	constexpr const_pointer arrend() {
		return std::addressof(_M_array_queue[_arr_size]);
	}//end()

	reference front() {
		return *_M_front;
	}//front()
	const_reference front() const {
		return *_M_front;
	}//front() const

	reference back() {
		return *((_M_front - _M_length + 1) % _arr_size);
	}//back()
	const_reference back() const {
		return *((_M_front - _M_length + 1) % _arr_size);
	}//back() const

	bool empty() const {
		return (_M_length == 0);
	}//empty()

	bool full() const {
		return _M_length >= _arr_size;
	}//full()

	size_type length() const {
		return _M_length;
	}//lengt()

	void push(const value_type & __x) {
		if(full())
			throw std::runtime_error("queue full!");
		++_M_front;
		if(_M_front == arrend())
			_M_front = pointer(arrbegin());
		*_M_front = __x;
		++_M_length;
	}//push()

	void pop() {
		if(empty())
			throw std::runtime_error("queue empty!");
		--_M_length;
	}//pop()
};//struct array_queue

template <typename T, std::size_t _arr_size>
void print(const array_queue<T, _arr_size> & que)
{
	unsigned long cnt = 0u;
	for(auto iter = que._M_front; cnt < que.length(); ++cnt) {
		std::cout << *iter << ' ';
		--iter;
		if(iter == que.arrbegin()-1)
			iter = decltype(iter)(que.arrend()-1);
	}//for
	std::cout << std::endl;
}//print(que)

int main()
{
	std::cout << "construct array_queue with size of 5 integers"
		<< std::endl;
	array_queue<int, 5> que;
	for(int i = 0; i < 5; ++i) {
		que.push(i);
		print(que);
	}//for

	std::cout << "Is it full? " << (que.full() ? "true" : "false")
		<< std::endl;

	std::cout << "pop out two elements on the top" << std::endl;
	que.pop();
	que.pop();
	print(que);

	std::cout << "push in 5" << std::endl;
	que.push(5);
	print(que);

	std::cout << "pop" << std::endl;
	que.pop();
	print(que);

	std::cout << "push in 6" << std::endl;
	que.push(6);
	print(que);

	return 0;
}//main

