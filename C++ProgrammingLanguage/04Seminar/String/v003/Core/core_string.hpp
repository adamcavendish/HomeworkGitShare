#pragma once

#ifndef ncpp11
#define cppnull nullptr
#else
#define cppnull 0
#endif //ncpp11

#include <cstdlib>
#include <cstring>

#ifdef DEBUG
#include <iostream>
#endif //DEBUG

template <size_t init_size, size_t inc_bit>
class core_string
{
	typedef core_string<init_size, inc_bit> _Self;
protected:
	friend class Debug;
protected: //constructors and destructors
	inline core_string();
	inline core_string(const _Self & s);
#ifndef ncpp11
	inline core_string(const _Self && s);
#endif //ncpp11
	inline core_string(const char * s);
	
	inline ~core_string();

public:
protected:
	inline _Self & operator=(const _Self & s);
	inline _Self & operator=(const char * s);
#ifndef ncpp11
	inline _Self & operator=(const _Self && s);
#endif //ncpp11

	virtual inline void _reallocate(const size_t & sz);
	virtual inline void _reduce(const size_t & sz);
private:

public:
protected:
	size_t __max_size;
	size_t __len;
	char * __p_string;
private:
};//class core_string

template <size_t init_size, size_t inc_bit>
inline core_string<init_size, inc_bit>::core_string():
	__max_size(init_size),
	__len(0),
	__p_string(new char[init_size])
{}//default constructor

template <size_t init_size, size_t inc_bit>
inline core_string<init_size, inc_bit>::core_string(const _Self & s)
{
	if(this == &s)
		return;
	__max_size = (s.__len > init_size) ? s.__len : init_size;
	__len = s.__len;
	__p_string = new char[__max_size];
	memcpy(__p_string, s.__p_string, s.__len);
}//copy constructor

#ifndef ncpp11
template <size_t init_size, size_t inc_bit>
inline core_string<init_size, inc_bit>::core_string(const _Self && s):
	__max_size(s.__max_size),
	__len(s.__len),
	__p_string(s.__p_string)
{
	s.__max_size = 0;
	s.__len = 0;
	s.__p_string = cppnull;
}//move constructor
#endif//ncpp11

template <size_t init_size, size_t inc_bit>
inline core_string<init_size, inc_bit>::core_string(const char * s)
{
	__len = strlen(s);
	__max_size = (__len > init_size) ? __len : init_size;
	__p_string = new char[__max_size];
	memcpy(__p_string, s, __len);
}//core_string(const char *)

template <size_t init_size, size_t inc_bit>
inline core_string<init_size, inc_bit> &
	core_string<init_size, inc_bit>::operator=(const _Self & s)
{
	if(this == &s)
		return *this;
	__max_size = (s.__len > init_size) ? s.__len : init_size;
	__len = s.__len;
	if(__p_string != cppnull)
		delete[] __p_string;
	__p_string = new char[__max_size];
	memcpy(__p_string, s.__p_string, __len);
	return *this;
}//assign operator

#ifndef ncpp11
template <size_t init_size, size_t inc_bit>
inline core_string<init_size, inc_bit> &
	core_string<init_size, inc_bit>::operator=(const _Self && s)
{
#ifdef DEBUG
	std::cout << "move assign func" << std::endl;
#endif //DEBUG
	if(this == &s)
		return *this;
	
	__max_size = s.__max_size;
	__len = s.__len;
	if(__p_string != cppnull)
		delete[] __p_string;
	__p_string = s.__p_string;

	s.__max_size = 0;
	s.__len = 0;
	s.__p_string = cppnull;
}//move assign operator
#endif //ncpp11

template <size_t init_size, size_t inc_bit>
inline core_string<init_size, inc_bit> & core_string<init_size, inc_bit>::operator=(const char *s)
{
	size_t __len = strlen(s);
	__max_size = (__len > init_size) ? __len : init_size;
	if(__p_string != cppnull)
		delete[] __p_string;
	__p_string = new char[__max_size];
	memcpy(__p_string, s, __len);
	return *this;
}//operator(const char *)

template <size_t init_size, size_t inc_bit>
inline core_string<init_size, inc_bit>::~core_string<init_size, inc_bit>()
{
#ifdef DEBUG
	std::cerr << "~core_string: " << this << std::endl;
#endif//DEBUG
	if(__p_string != cppnull)
		delete[] __p_string;
	__p_string = cppnull;
}//~core_string()

template <size_t init_size, size_t inc_bit>
inline void core_string<init_size, inc_bit>::_reallocate(const size_t & sz)
{
	if(sz <= __max_size)
		return;

	size_t n_sz = 1;
	while(n_sz < sz)
		n_sz <<= 1;

	const char *cache =  __p_string;
	__p_string = new char[n_sz];
	__max_size = n_sz;
	memcpy(__p_string, cache, __len);
	delete cache;
}//_reallocate(sz)

template <size_t init_size, size_t inc_bit>
inline void core_string<init_size, inc_bit>::_reduce(const size_t & sz)
{
	if(sz >= __max_size)
		return;

	const char *cache = __p_string;
	__p_string = new char[sz];
	__max_size = sz;
	memcpy(__p_string, cache, __len);
	delete cache;
}//_reduce(sz)

