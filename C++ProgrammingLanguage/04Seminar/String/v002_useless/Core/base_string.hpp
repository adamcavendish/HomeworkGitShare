#pragma once

#ifndef ncpp11
#define cppnull nullptr
#else
#define cppnull 0
#endif //ncpp11

#include <cstdlib>
#include <cstring>
//#include <iostream>

template <size_t basic_allocate_size>
class base_string
{
	typedef base_string<basic_allocate_size> _Self;
public:
	virtual inline char & operator[](const size_t & pos) const;

	virtual inline const size_t max_size() const;
	virtual inline const size_t size() const;
	virtual inline const char * c_str() const;
	
	virtual inline void shrink();
protected:
	inline base_string();
	inline base_string(const _Self & s);
#ifndef ncpp11
	inline base_string(const _Self && s);
#endif //ncpp11
	inline base_string(const char * s);

	inline _Self & operator=(const _Self & s);
	inline _Self & operator=(const char * s);

	inline ~base_string();
	
	virtual inline bool _eq(const char & a, const char & b) const;
	virtual inline bool _less(const char & a, const char & b) const;
	virtual inline bool _greater(const char & a, const char & b) const;
private:

public:
protected:
private:
};//class base_string

template <size_t basic_allocate_size>
inline base_string<basic_allocate_size>::base_string():
	__max_size(basic_allocate_size),
	__len(0),
	__p_string(new char[basic_allocate_size])
{}//default constructor

template <size_t basic_allocate_size>
inline base_string<basic_allocate_size>::base_string(const _Self & s)
{
	if(this == &s)
		return;
	__max_size = (s.size() > basic_allocate_size) ? s.size() : basic_allocate_size;
	__len = s.size();
	__p_string = new char[__max_size];
	memcpy(__p_string, s.c_str(), s.size());
}//copy constructor

#ifndef ncpp11
template <size_t basic_allocate_size>
inline base_string<basic_allocate_size>::base_string(const _Self && s)
{
	*this = s;
}//move constructor
#endif//ncpp11

template <size_t basic_allocate_size>
inline base_string<basic_allocate_size>::base_string(const char * s)
{
	__len = strlen(s);
	__max_size = (__len > basic_allocate_size) ? __len : basic_allocate_size;
	__p_string = new char[__max_size];
	memcpy(__p_string, s, __len);
}//base_string(const char *)

template <size_t basic_allocate_size>
inline base_string<basic_allocate_size> & base_string<basic_allocate_size>::operator=(const _Self & s)
{
	if(this == &s)
		return *this;
	__max_size = (s.size() > basic_allocate_size) ? s.size() : basic_allocate_size;
	__len = s.size();
	if(__p_string != cppnull)
		delete[] __p_string;
	__p_string = new char[__max_size];
	memcpy(__p_string, s.c_str(), __len);
	return *this;
}//operator=(base_string)

template <size_t basic_allocate_size>
inline base_string<basic_allocate_size> & base_string<basic_allocate_size>::operator=(const char * s)
{
	size_t __len = strlen(s);
	__max_size = (__len > basic_allocate_size) ? __len : basic_allocate_size;
	if(__p_string != cppnull)
		delete[] __p_string;
	__p_string = new char[__max_size];
	memcpy(__p_string, s, __len);
	return *this;
}//operator(const char *)

template <size_t basic_allocate_size>
inline char & base_string<basic_allocate_size>::operator[](const size_t & pos) const
{
	return __p_string[pos];
}//operator[](pos)

template <size_t basic_allocate_size>
inline const size_t base_string<basic_allocate_size>::max_size() const
{
	return __max_size;
}//max_size()

template <size_t basic_allocate_size>
inline const size_t base_string<basic_allocate_size>::size() const
{
	return __len;
}//size()

template <size_t basic_allocate_size>
inline const char * base_string<basic_allocate_size>::c_str() const
{
	__p_string[__len] = '\0';
	return __p_string;
}//c_str()

template <size_t basic_allocate_size>
inline void base_string<basic_allocate_size>::shrink()
{
	_reduce(__len);
}//_shrink()

template <size_t basic_allocate_size>
inline base_string<basic_allocate_size>::~base_string<basic_allocate_size>()
{
	//std::cerr << "~base_string: " << this << std::endl;
	if(__p_string != cppnull)
		delete[] __p_string;
	__p_string = cppnull;
}//~base_string()

template <size_t basic_allocate_size>
inline bool base_string<basic_allocate_size>::_eq(const char & a, const char & b) const
{
	return (a == b);
}//_eq(char, char)

template <size_t basic_allocate_size>
inline bool base_string<basic_allocate_size>::_less(const char & a, const char & b) const
{
	return (a < b);
}//_less(char, char)

template <size_t basic_allocate_size>
inline bool base_string<basic_allocate_size>::_greater(const char & a, const char & b) const
{
	return (a > b);
}//_greater(char, char)

