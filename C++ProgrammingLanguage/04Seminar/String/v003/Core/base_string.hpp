#pragma once

#include "core_string.hpp"

#include <cstdlib>
#include <utility>

template <size_t init_size, size_t inc_bit>
class base_string : protected core_string<init_size, inc_bit>
{
	typedef base_string<init_size, inc_bit> _Self;
protected: // constructors
	inline base_string();
	inline base_string(const _Self & s);
#ifndef ncpp11
	inline base_string(const _Self && s);
#endif //ncpp11
	inline base_string(const char *s);

public:
	virtual inline char & operator[](const size_t & pos) const;
	virtual inline _Self & operator+=(const _Self & s);
	virtual inline _Self & operator+=(const char * s);

	virtual inline const size_t max_size() const;
	virtual inline const size_t length() const;
	virtual inline const char * c_str() const;
	
	virtual inline void shrink();
protected:
	virtual inline bool _eq(const char & a, const char & b) const;
	virtual inline bool _less(const char & a, const char & b) const;
	virtual inline bool _greater(const char & a, const char & b) const;	
private:

public:
protected:
private:
};//class base_string

template <size_t init_size, size_t inc_bit>
inline base_string<init_size, inc_bit>::base_string()
	: core_string<init_size, inc_bit>::core_string()
{}//default constructor

template <size_t init_size, size_t inc_bit>
inline base_string<init_size, inc_bit>::base_string(const _Self & s)
	: core_string<init_size, inc_bit>::core_string(s)
{}//copy constructor

#ifndef ncpp11
template <size_t init_size, size_t inc_bit>
inline base_string<init_size, inc_bit>::base_string(const _Self && s)
	: core_string<init_size, inc_bit>::core_string(std::move(s))
{}//move constructor
#endif //ncpp11

template <size_t init_size, size_t inc_bit>
inline base_string<init_size, inc_bit>::base_string(const char *s)
	: core_string<init_size, inc_bit>::core_string(s)
{}//constructor(const char *)

template <size_t init_size, size_t inc_bit>
inline char & base_string<init_size, inc_bit>::operator[](
		const size_t & pos) const
{
	return this->__p_string[pos];
}//operator[](pos)

template <size_t init_size, size_t inc_bit>
inline const size_t base_string<init_size, inc_bit>::max_size() const
{
	return this->__max_size;
}//max_size()

template <size_t init_size, size_t inc_bit>
inline const size_t base_string<init_size, inc_bit>::length() const
{
	return this->__len;
}//length()

template <size_t init_size, size_t inc_bit>
inline const char * base_string<init_size, inc_bit>::c_str() const
{
	this->__p_string[this->__len] = '\0';
	return this->__p_string;
}//c_str()

template <size_t init_size, size_t inc_bit>
inline void base_string<init_size, inc_bit>::shrink()
{
	this->_reduce(this->__len);
}//_shrink()

template <size_t init_size, size_t inc_bit>
inline bool base_string<init_size, inc_bit>::_eq(
		const char & a,
		const char & b) const
{
	return (a == b);
}//_eq(char, char)

template <size_t init_size, size_t inc_bit>
inline bool base_string<init_size, inc_bit>::_less(
		const char & a,
		const char & b) const
{
	return (a < b);
}//_less(char, char)

template <size_t init_size, size_t inc_bit>
inline bool base_string<init_size, inc_bit>::_greater(
		const char & a,
		const char & b) const
{
	return (a > b);
}//_greater(char, char)

template <size_t init_size, size_t inc_bit>
inline base_string<init_size, inc_bit> &
	base_string<init_size, inc_bit>::operator+=(const _Self & s)
{
	this->_reallocate(this->__len + s.__len);
	for(size_t i = 0; i < s.__len; ++i)
		*(this->__p_string + this->__len++) = s[i];
	return *this;
}//operator+=(_string)

template <size_t init_size, size_t inc_bit>
inline base_string<init_size, inc_bit> &
	base_string<init_size, inc_bit>::operator+=(const char * s)
{
	size_t sz = strlen(s);
	this->_reallocate(this->__len + sz);
	for(size_t i = 0; i < sz; ++i)
		*(this->__p_string + this->__len++) = s[i];
	return *this;
}//operator+=(const char *)

