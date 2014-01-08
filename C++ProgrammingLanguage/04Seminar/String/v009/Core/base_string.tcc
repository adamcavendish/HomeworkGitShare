#pragma once

#include "base_string.hpp"

#include <iostream>

template <size_t init_size, size_t inc_bit>
std::ostream & operator<<(
		std::ostream & os,
		const base_string<init_size, inc_bit> & s)
{
	for(size_t i = 0; i < s.length(); ++i)
		os << s[i];
	return os;
}//operator<<(os, s)

template <size_t init_size, size_t inc_bit>
base_string<init_size, inc_bit> operator+(
		const base_string<init_size, inc_bit> & s1,
		const base_string<init_size, inc_bit> & s2)
{
	base_string<init_size, inc_bit> ret(s1);
	return (ret += s2);
}//operator+(base_string, base_string)

template <size_t init_size, size_t inc_bit>
base_string<init_size, inc_bit> operator+(
		const base_string<init_size, inc_bit> & s1,
		const char * s2)
{
	base_string<init_size, inc_bit> ret(s1);
	return (ret += s2);
}//operator+(base_string, const char *)


