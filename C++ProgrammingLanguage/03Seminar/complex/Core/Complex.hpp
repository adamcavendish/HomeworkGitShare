#pragma once

#include <iostream>

template <typename RealType, typename ImgType>
class Complex
{
	typedef Complex<RealType, ImgType> _Self;
public:
	Complex() : _real(0), _img(0) {}
	Complex(const _Self & c) : _real(c.getReal()), _img(c.getImg()) {}

	template <typename Re, typename Im>
	Complex(const Complex<Re, Im> & c) :
		_real((RealType)c.getReal()),
		_img((ImgType)c.getImg())
	{}

	Complex(RealType real, ImgType img) : _real(real), _img(img) {}

	_Self operator+=(const _Self & c1) {
		this->_real += c1.getReal();
		this->_img += c1.getImg();
		return *this;
	}//operator+=

	_Self operator+(const _Self & c1) const {
		_Self temp(*this);
		return temp += c1;
	}//operator+

	_Self operator-=(const _Self & c1) {
		this->_real += c1.getReal();
		this->_img += c1.getImg();
		return *this;
	}//opeartor-=

	_Self operator-(const _Self & c1) const {
		_Self temp(*this);
		return temp -= c1;
	}//operator-

	_Self operator*=(const _Self & c1) {
		const RealType & a = this->_real;
		const ImgType & b = this->_img;
		const RealType c = c1.getReal();
		const ImgType d = c1.getImg();
		
		this->_real = a*c -b*d;
		this->_img = b*c + a*d;
		return *this;
	}//operator*=

	_Self operator*(const _Self & c1) {
		_Self temp(*this);
		return temp *= c1;
	}//operator*

	_Self operator/=(const _Self & c1) {
		const RealType & a = this->_real;
		const ImgType & b = this->_img;
		const RealType c = c1.getReal();
		const ImgType d = c1.getImg();

		this->_real = (a*c + b*d)/(c*c + d*d);
		this->_img = (b*c - a*d)/(c*c + d*d);
		return *this;
	}//operator/=

	_Self operator/(const _Self & c1) {
		_Self temp(*this);
		return temp /= c1;
	}//operator/

	_Self sqrt();

	friend std::ostream & operator<<(
			std::ostream & os,
			const _Self & c)
	{
		os << c.getReal();
		if(c.getImg() > 0) {
			os << '+' << c.getImg() << 'i';
		} else if(c.getImg() < 0) {
			os << c.getImg() << 'i';
		}//if-else
		return os;
	}//opeartor<<(os, c)

	RealType getReal() const { return _real; }
	ImgType getImg() const { return _img; }
private:

public:
	
private:
	RealType _real;
	ImgType _img;
};//class Complex

