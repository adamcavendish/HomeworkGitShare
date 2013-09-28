#pragma once

#include <algorithm>

template <typename T>
class matrix {
public://functions
	explicit matrix(const std::size_t row, const std::size_t col) :
		row_(row),
		col_(col),
		data_(new T[row * col])
	{}

	explicit matrix(const matrix & rhs) :
		row_(rhs.row_),
		col_(rhs.col_),
		data_(new T[rhs.row_ * rhs.col_])
	{ std::copy(rhs->data_, rhs->data_ + rhs.row_ * rhs.col_, this->data_); }

	matrix & operator=(const matrix & rhs) = delete;

	matrix & operator=(matrix && rhs) {
		if(this == &rhs)
			return (*this);

		delete[] this->data;
		this->row_ = rhs.row_;
		this->col_ = rhs.col_;
		this->data_ = new T[this->row_ * this->col_];
	}//move assignment

	matrix clone() const { return (*this); }

	const matrix clone() const { return (*this); }

	T & operator()(const std::size_t row, const std::size_t col)
	{ return this->data_[row * this->col_ + col]; }

	const T & operator()(const std::size_t row, const std::size_t col) const
	{ return this->data_[row * this->col_ + col]; }

	T * data() { return this->data_; }

	const T * data() const { return this->data_; }

	std::size_t row() const { return this->row_; }

	std::size_t col() const { return this->col_; }

public://members
	std::size_t row_;
	std::size_t col_;
	T * data_;
};//class matrix

