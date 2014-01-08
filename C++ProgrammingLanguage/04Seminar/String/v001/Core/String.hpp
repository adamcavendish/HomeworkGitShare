#pragma once

#include "base_string.hpp"

#include <cstdlib>
#include <iostream>

template <size_t basic_allocate_size>
class _string : public base_string<basic_allocate_size>
{
	typedef _string<basic_allocate_size> _Self;
public:
	/// constructors
	inline _string();
	inline _string(const _Self & s);
	inline _string(const char * s);
#ifndef ncpp11
	inline explicit _string(const _Self && s);
#endif//ncpp11

	inline bool operator==(const _Self & s);
	inline bool operator<(const _Self & s);
	inline bool operator>(const _Self & s);

	inline _Self & operator+=(const _Self & s);
	inline _Self & operator+=(const char * s);

private:
};//class _string

template <size_t basic_allocate_size>
_string<basic_allocate_size>::_string():
	base_string<basic_allocate_size>::base_string()
{}//default constructor

template <size_t basic_allocate_size>
_string<basic_allocate_size>::_string(const _Self & s):
	base_string<basic_allocate_size>::base_string(s)
{}//copy constructor

template <size_t basic_allocate_size>
_string<basic_allocate_size>::_string(const char * s):
	base_string<basic_allocate_size>::base_string(s)
{}//constructor(const char *)

#ifndef ncpp11
template <size_t basic_allocate_size>
_string<basic_allocate_size>::_string(const _Self && s):
	base_string<basic_allocate_size>::base_string(std::move(s))
{}//move constructor
#endif//ncpp11

template <size_t basic_allocate_size>
inline bool _string<basic_allocate_size>::operator==(const _Self & s)
{
	if(this->__len != s.size())
		return false;
	for(size_t i = 0; i < this->__len; ++i)
		if(!_eq(this->__p_string[i], s[i]))
			return false;
	return true;
}//operator==(_string)

template <size_t basic_allocate_size>
inline bool _string<basic_allocate_size>::operator<(const _Self & s)
{
	if(this->__len != s.size())
		return false;
	for(size_t i = 0; i < this->__len; ++i)
		if(!_less(this->__p_string[i], s[i]))
			return false;
	return true;
}//operator<(base_string)

template <size_t basic_allocate_size>
inline bool _string<basic_allocate_size>::operator>(const _Self & s)
{
	for(size_t i = 0; i < this->__len; ++i)
		if(!_greater(this->__p_string, s[i]))
			return false;
	return true;
}//operator>(base_string)

template <size_t basic_allocate_size>
inline _string<basic_allocate_size> & _string<basic_allocate_size>::operator+=(const _Self & s)
{
	this->_reallocate(this->__len + s.size());
	for(size_t i = 0; i < s.size(); ++i)
		*(this->__p_string + this->__len++) = s[i];
	return *this;
}//operator+=(_string)

template <size_t basic_allocate_size>
inline _string<basic_allocate_size> & _string<basic_allocate_size>::operator+=(const char * s)
{
	size_t sz = strlen(s);
	this->_reallocate(this->__len + sz);
	for(size_t i = 0; i < sz; ++i)
		*(this->__p_string + this->__len++) = s[i];
	return *this;
}//operator+=(const char *)

