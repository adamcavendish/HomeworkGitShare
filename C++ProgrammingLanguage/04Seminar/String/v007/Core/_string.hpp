#pragma once

#include "base_string.hpp"

#include <cstdlib>
#include <utility>
// #include <iostream>

template <size_t init_size, size_t inc_bit>
class _string : public base_string<init_size, inc_bit>
{
	typedef _string<init_size, inc_bit> _Self;
public:
	/// constructors
	inline _string();
	inline _string(const _Self & s);
	inline _string(const base_string<init_size, inc_bit> & s);
	inline _string(const char * s);
#ifndef ncpp11
	inline _string(_Self && s);
#endif//ncpp11

	inline bool operator==(const _Self & s) const;
	inline bool operator<(const _Self & s) const;
	inline bool operator>(const _Self & s) const;
private:
};//class _string

template <size_t init_size, size_t inc_bit>
inline _string<init_size, inc_bit>::_string():
	base_string<init_size, inc_bit>::base_string()
{}//default constructor

template <size_t init_size, size_t inc_bit>
inline _string<init_size, inc_bit>::_string(const _Self & s):
	base_string<init_size, inc_bit>::base_string(s)
{}//copy constructor

template <size_t init_size, size_t inc_bit>
inline _string<init_size, inc_bit>::_string(const char * s) :
	base_string<init_size, inc_bit>::base_string(s)
{}//constructor(const char *)

template <size_t init_size, size_t inc_bit>
inline _string<init_size, inc_bit>::
_string(const base_string<init_size, inc_bit> & s) :
	base_string<init_size, inc_bit>::base_string(s)
{}//constructor(base_string)

#ifndef ncpp11
template <size_t init_size, size_t inc_bit>
_string<init_size, inc_bit>::_string(_Self && s):
	base_string<init_size, inc_bit>::base_string(std::move(s))
{}//move constructor
#endif//ncpp11

template <size_t init_size, size_t inc_bit>
inline bool _string<init_size, inc_bit>::operator==(const _Self & s) const
{
	if(this->__len != s.length())
		return false;
	for(size_t i = 0; i < this->__len; ++i)
		if(!_eq(this->__p_string[i], s[i]))
			return false;
	return true;
}//operator==(_string)

template <size_t init_size, size_t inc_bit>
inline bool _string<init_size, inc_bit>::operator<(const _Self & s) const
{
	size_t cmp_sz = (this->__len > s.length()) ? this->__len : s.length();

	for(size_t i = 0; i < cmp_sz; ++i)
		if(!_less(this->__p_string[i], s[i]))
			return false;
	return true;
}//operator<(base_string)

template <size_t init_size, size_t inc_bit>
inline bool _string<init_size, inc_bit>::operator>(const _Self & s) const
{
	size_t cmp_sz = (this->__len > s.length()) ? this->__len : s.length();

	for(size_t i = 0; i < cmp_sz; ++i)
		if(!_greater(this->__p_string[i], s[i]))
			return false;
	return true;
}//operator>(base_string)

