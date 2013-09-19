#pragma once

template <typename T>
class matrix {
public://functions
	explicit matrix(const std::size_t row, const std::size_t col) :
		row_(row),
		col_(col),
		data_(new T[row * col])
	{}

	T operator()(const std::size_t row, const std::size_t col) const
	{ return this->data_[row * this->col_ + col]; }

	std::size_t row() const { return this->row_; }

	std::size_t col() const { return this->col_; }

public://members
	std::size_t row_;
	std::size_t col_;
	T * data_;
};//class matrix

