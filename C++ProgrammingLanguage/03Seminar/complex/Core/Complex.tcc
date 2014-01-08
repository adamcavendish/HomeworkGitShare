#pragma once

#include "Complex.hpp"

#include <cmath>

template<typename RealType, typename ImgType>
Complex<RealType, ImgType> Complex<RealType, ImgType>::sqrt()
{
	const RealType & a = this->_real;
	const ImgType & b = this->_img;
	/*
	const RealType c = c.getReal();
	const ImgType d = c.getImg();             
	*/
	this->_real = std::sqrt((a + std::sqrt(a*a + b*b)) >> 1);
	this->_img = std::sqrt((-a + std::sqrt(a*a + b*b)) >> 1);
	if(b < 0)
		this->_img = -this->_img;
	return *this;
}//sqrt()

