#include "Array"

#include <iostream>
#include <algorithm>
#include <ext/bitmap_allocator.h>
using namespace adamcavendish::data_structure;

template <typename T, std::size_t N, typename Allocator>
void print(const Array<T, N, Allocator> rhs)
{
/*
	for(auto i = 0u; i < N; ++i)
		std::cout << rhs[i] << ' ';
*/
	typename Array<T, N, Allocator>::const_iterator ie = rhs.cend();
	for(typename Array<T, N, Allocator>::const_iterator i = rhs.cbegin(); i != ie; ++i)
		std::cout << *i << ' ';
	std::cout << std::endl;
}//print

template <typename T, std::size_t N, typename Allocator>
void rprint(const Array<T, N, Allocator> rhs)
{
	typename Array<T, N, Allocator>::const_reverse_iterator ie = rhs.crend();
	for(typename Array<T, N, Allocator>::const_reverse_iterator i = rhs.crbegin();
			i != ie; ++i)
		std::cout << *i << ' ';
	std::cout << std::endl;
}//rprint

int main()
{
	const static int max_num1 = 10;
	const static int max_num2 = 10;
	const static int max_num3 = 3;
	const static int max_num4 = 10;
	const static int max_num5 = 10;
	const static int max_num6 = 10;
	const static int max_num7 = 10;
	const static int max_num8 = 0;
	const static int max_num9 = 10;
	const static int max_num10 = 10;
	const static int max_num11 = 10;
	const static int max_num12 = 3;

	Array<int, max_num1> a1;
	for(int i = 0; i < max_num1; ++i)
		a1[i] = i + 100;
	const Array<int, max_num2> a2({0,1});
	Array<int, max_num3> a3(a1.begin(), a1.end());

	std::cout << "a1: ";
	print(a1);
	std::cout << "a2: ";
	print(a2);
	std::cout << "a3: ";
	print(a3);

	std::cout << "a1.data(): " << a1.data() << std::endl;

	Array<int, max_num4> a4(std::move(a1));
	std::cout << "a4: ";
	print(a4);
	std::cout << "a4.data(): " << a4.data() << std::endl;

	Array<int, max_num5> a5;
	a5 = a4;
	std::cout << "a5: ";
	print(a5);
	a5 = a5;
	std::cout << "a5: ";
	print(a5);
	std::cout << "a5 == a4? " << (a5 == a4 ? "Yes" : "No") << std::endl;

	Array<int, max_num6> a6;
	a6 = std::move(a4);
	std::cout << "normal  a6: ";
	print(a6);
	std::cout << "reverse a6: ";
	rprint(a6);
	std::cout << "a6.data(): " << a6.data() << std::endl;
	std::cout << "a6.empty(): " << (a6.empty() ? "Yes" : "No") << std::endl;
	std::cout << "a6.size(): " << a6.size() << std::endl;
	std::cout << "a6.max_size(): " << a6.max_size() << std::endl;

	Array<int, max_num7> *a7 = new Array<int, max_num7>();
	std::cout << "a7: ";
	print(*a7);
	a7->fill(1024);
	std::cout << "a7: ";
	print(*a7);
	a7->fill(a6.begin(), a6.end());
	std::cout << "a7: ";
	print(*a7);
	a7->fill({1, 2, 3, 4, 5});
	std::cout << "a7: ";
	print(*a7);
	std::cout << "a7->data(): " << a7->data() << std::endl;
	delete a7;

	std::cout << "a6[1]: " << a6.at(1) << std::endl;
	//std::cout << "a6[100]: " << a6.at(100) << std::endl;
	std::cout << "a6[0], a6.front(): " << a6.front() << std::endl;
	std::cout << "a6[N], a6.back(): " << a6.back() << std::endl;

	Array<int, max_num8> a8;
	std::cout << "a8: ";
	print(a8);
	std::cout << "a8.empty(): " << (a8.empty() ? "Yes" : "No") << std::endl;

	Array<int, max_num9> a9;
	std::cout << "a9: ";
	print(a9);
	std::cout << "a6: ";
	print(a6);
	std::cout << "a9.data(): " << a9.data()
		<< " a6.data(): " << a6.data() << std::endl;
	swap(a6, a9);
	std::cout << "After swap" << std::endl;
	std::cout << "a9: ";
	print(a9);
	std::cout << "a6: ";
	print(a6);
	std::cout << "a9.data(): " << a9.data()
		<< " a6.data(): " << a6.data() << std::endl;

	Array<int, max_num10> a10 = a9;
	std::cout << "a10: ";
	print(a10);
	std::cout << "a10 == a9: " << (a10 == a9 ? "Yes" : "No") << std::endl;
	std::cout << "a10 <= a9: " << (a10 <= a9 ? "Yes" : "No") << std::endl;
	std::cout << "a10 >= a9: " << (a10 >= a9 ? "Yes" : "No") << std::endl;

	a10[1] -= 10;
	std::cout << "a10: ";
	print(a10);
	std::cout << "a10 < a9: " << (a10 < a9 ? "Yes" : "No") << std::endl;
	std::cout << "a10 <= a9: " << (a10 <= a9 ? "Yes" : "No") << std::endl;
	std::cout << "a10 > a9: " << (a10 > a9 ? "Yes" : "No") << std::endl;
	std::cout << "a10 >= a9: " << (a10 >= a9 ? "Yes" : "No") << std::endl;

	a10.fill(1000);
	std::cout << "a10: ";
	print(a10);
	std::cout << "a9: ";
	print(a9);

	std::cout << "a10 + a9: ";
	print(a10 + a9);
	std::cout << "a10 - a9: ";
	print(a10 - a9);
	std::cout << "a10 * a9: ";
	print(a10 * a9);
	std::cout << "a9 / a9: ";
	print(a9 / a9);

	std::cout << "a10 + 111: ";
	print(a10 + 111);

	for(auto i = 0u; i < a10.size(); ++i)
		a10[i] = 100 + i;
	std::cout << "a10: ";
	print(a10);

	auto iter10 = std::find(a10.begin(), a10.end(), 101);
	std::cout << *iter10  << std::endl;

	__gnu_cxx::bitmap_allocator<int> bitalloc;
	Array<int, max_num11, __gnu_cxx::bitmap_allocator<int> > a11(
			a10.begin(), a10.end(), bitalloc);
	std::cout << "a10: ";
	print(a10);
	std::cout << "a11: ";
	print(a11);
	
	std::cout << "a10.data(): " << a10.data() << std::endl;
	std::cout << "a11.data(): " << a11.data() << std::endl;

	Array<int, max_num12, __gnu_cxx::bitmap_allocator<int> > a12(
			{1, 2, 3}, bitalloc);
	std::cout << "a12: ";
	print(a12);

	return 0;
}//main

