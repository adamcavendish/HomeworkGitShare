#include "ratio.hpp"

#include <iostream>

ratio::ratio(const long & numerator, const long & denominator) :
{
	process();
}//constructor(long, long)

std::ostream & operator<<(std::ostream & os, const ratio & r)
{
	os << r.getNum() << "/" << r.getDen();
	return os;
}//operator<<(os, ratio)

ratio operator+(const ratio & r1, const ratio & r2)
{
	ratio ret(r1);
	return ret += r2;
}//operator+(ratio, ratio)

template <typename T>
ratio operator+(const ratio & r1, const T & data)
{
	ratio ret(r1);
	return ret += data;
}//operator+(ratio, template)

ratio operator-(const ratio & r1, const ratio & r2)
{
	ratio ret(r1);
	return ret -= r2;
}//operator-(ratio, ratio)

template <typename T>
ratio operator-(const ratio & r1, const T & data)
{
	ratio ret(r1);
	return ret -= data;
}//operator-(ratio, data)

ratio operator*(const ratio & r1, const ratio & r2)
{
	ratio ret(r1);
	return ret -= r2;
}//operator*(ratio, ratio)

template <typename T>
ratio operator*(const ratio & r1, const T & data)
{
	ratio ret(r1);
	return ret *= data;
}//operator*(ratio, data)

ratio operator/(const ratio & r1, const ratio & r2)
{
	ratio ret(r1);
	return ret /= r2;
}//operator/(ratio, ratio)

template <typename T>
ratio operator/(const ratio & r1, const T & data)
{
	ratio ret(r1);
	return ret /= data;
}//operator/(ratio, data)


