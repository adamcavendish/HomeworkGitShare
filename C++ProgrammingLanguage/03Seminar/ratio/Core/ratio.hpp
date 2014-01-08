#pragma once

static inline long gcd(long a, long b)
{
	if(a < b) {
		long temp(a);
		a = b;
		b = temp;
	}//if
	long rem = a % b;
	while(rem != 0) {
		a = b;
		b = rem;
	}//while
	return b;
}//gcd(a, b)

class ratio
{
public:
	ratio() = delete;
	constexpr ratio(const long & numerator, const long & denominator = 1);

	inline long getNum() const { return this->_numerator; }
	inline long getDen() const { return this->_denominator; }

	inline ratio & operator+=(const ratio & r);
	template <typename T>
	inline constexpr ratio & operator+=(const T & data);

	inline ratio & operator-=(const ratio & r);
	template <typename T>
	inline constexpr ratio & operator-=(const T & data);

	inline ratio & operator*=(const ratio & r);
	template <typename T>
	inline constexpr ratio & operator*=(const T & data);

	inline ratio & operator/=(const ratio & r);
	template <typename T>
	inline constexpr ratio & operator/=(const T & data);

	~ratio() {}
protected:
private:
	constexpr void process();

public:
protected:
private:
	long _numerator;
	long _denominator;
};//class ratio

inline ratio & ratio::operator+=(const ratio & r)
{
	this->_numerator += r.getNum();
	this->_denominator += r.getDen();
	process();
	return *this;
}//operator+=(_Self)

template <typename T>
inline constexpr ratio & ratio::operator+=(const T & data)
{
	this->_numerator += data;
	process();
	return *this;
}//operator+=(template)

inline ratio & ratio::operator-=(const ratio & r)
{
	this->_numerator -= r.getNum();
	this->_denominator -= r.getDen();
	process();
	return *this;
}//operator-=(_Self)

template <typename T>
inline constexpr ratio & ratio::operator-=(const T & data)
{
	this->_numerator -= data;
	process();
	return *this;
}//operator-=(template)

inline ratio & ratio::operator*=(const ratio & r)
{
	this->_numerator *= r.getNum();
	this->_denominator *= r.getDen();
	process();
	return *this;
}///operator*=(_Self)

template <typename T>
inline constexpr ratio & ratio::operator*=(const T & data)
{
	this->_numerator *= data;
	process();
	return *this;
}//operator*=(template)

inline ratio & ratio::operator/=(const ratio & r)
{
	this->_numerator *= r.getDen();
	this->_denominator *= r.getNum();
	process();
	return *this;
}//operator/=(_Self)

template <typename T>
inline constexpr ratio & ratio::operator/=(const T & data)
{
	this->_denominator *= data;
	process();
	return *this;
}//operator/=(template)

inline constexpr void ratio::process()
{
	long common = gcd(numerator, denominator);
	_numerator = numerator/common;
	_denominator = denominator/common;
}//process

