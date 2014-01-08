#pragma once

namespace adamcavendish {
namespace data_structure {

template <
	typename T,
	std::size_t N,
	typename Allocator>
inline void Array<T, N, Allocator>::_M_construct() {
	try {
		_M_data = _M_allocator.allocate(_M_length);
		std::uninitialized_fill_n(_M_data, _M_length, value_type());
	} catch(...) {
		_M_data = nullptr;
		throw;
	}//try-catch
}//_M_construct()

template <
	typename T,
	std::size_t N,
	typename Allocator>
inline void Array<T, N, Allocator>::_M_construct(const T & val) {
	try {
		_M_data = _M_allocator.allocate(_M_length);
		std::uninitialized_fill_n(_M_data, _M_length, val);
	} catch(...) {
		_M_data = nullptr;
		throw;
	}//try-catch
}//_M_construct(val)

template <
	typename T,
	std::size_t N,
	typename Allocator>
template <typename InputIt>
inline void Array<T, N, Allocator>::_M_construct(
		const InputIt & first,
		const InputIt & last)
{
	/*
	size_type dif = static_cast<size_type>(last - first + 1);
	size_type less_len = (dif < _M_length) ? dif : _M_length;
	InputIt iter = const_cast<InputIt>(first);
	size_type fill_the_rest_len = _M_length - less_len;

	_M_data = _M_allocator.allocate(N);
	iter = std::uninitialized_copy_n(iter, less_len, _M_data);
	if(less_len < _M_length)
		std::uninitialized_fill_n( \
				iter, fill_the_rest_len, value_type());
	*/
	try {
		_M_data = _M_allocator.allocate(_M_length);
		fill(first, last);
	} catch(...) {
		_M_data = nullptr;
		throw;
	}//try-catch
}//_M_construct(first, last)

template <
	typename T,
	std::size_t N,
	typename Allocator>
inline void Array<T, N, Allocator>::_M_destruct() {
	if(_M_data) {
		iterator it = _M_data + _M_length;
		while(it != _M_data)
			_M_allocator.destroy(--it);

		_M_allocator.deallocate(_M_data, _M_length);
		_M_data = nullptr;
	}//if
}//_M_destruct()

template <
	typename T,
	std::size_t N,
	typename Allocator>
inline void Array<T, N, Allocator>::_M_range_check(size_type pos) \
	const throw(std::out_of_range)
{
	if(pos < 0 || pos > N)
		throw std::out_of_range("Array: out_of_range Error!");
}//_M_range_check(pos)

/**
 * --------------------------------------------------
 *  Array Comparisons
 * --------------------------------------------------
 */
template <typename T, std::size_t N>
inline bool operator==(const Array<T, N> & lhs, const Array<T, N> & rhs) {
	return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}//operator==(Array, Array)

template <typename T, std::size_t N>
inline bool operator!=(const Array<T, N> & lhs, const Array<T, N> & rhs) {
	return !(lhs == rhs);
}//operator!=(Array, Array)

template <typename T, std::size_t N>
inline bool operator<(const Array<T, N> & lhs, const Array<T, N> & rhs) {
	return std::lexicographical_compare(lhs.begin(), lhs.end(),
			rhs.begin(), rhs.end());
}//operator<(Array, Array)

template <typename T, std::size_t N>
inline bool operator>(const Array<T, N> & lhs, const Array<T, N> & rhs) {
	return rhs < lhs;
}//operator>(Array, Array)

template <typename T, std::size_t N>
inline bool operator<=(const Array<T, N> & lhs, const Array<T, N> & rhs) {
	return !(lhs > rhs);
}//operator<=(Array, Array)

template <typename T, std::size_t N>
inline bool operator>=(const Array<T, N> & lhs, const Array<T, N> & rhs) {
	return !(lhs < rhs);
}//operator>=(Array, Array)

/**
 * --------------------------------------------------
 *  Array Arithmatics
 * --------------------------------------------------
 */
template <typename T, std::size_t N>
inline Array<T, N> operator+(
		const Array<T, N> & __one, const T & __two) {
	Array<T, N> ret(__one);
	return ret += __two;
}//operator+(Array, T)

template <typename T, std::size_t N>
inline Array<T, N> operator-(
		const Array<T, N> & __one, const T & __two) {
	Array<T, N> ret(__one);
	return ret -= __two;
}//operator-(Array, T)

template <typename T, std::size_t N>
inline Array<T, N> operator*(
		const Array<T, N> & __one, const T & __two) {
	Array<T, N> ret(__one);
	return ret *= __two;
}//operator*(Array, T)

template <typename T, std::size_t N>
inline Array<T, N> operator/(
		const Array<T, N> & __one, const T & __two) {
	Array<T, N> ret(__one);
	return ret /= __two;
}//operator/(Array, T)

template <typename T, std::size_t N>
inline Array<T, N> operator+(
		const Array<T, N> & __one, const Array<T, N> & __two) {
	Array<T, N> ret(__one);
	return ret += __two;
}//operator+(Array, Array)

template <typename T, std::size_t N>
inline Array<T, N> operator-(
		const Array<T, N> & __one, const Array<T, N> & __two) {
	Array<T, N> ret(__one);
	return ret -= __two;
}//operator-(Array, Array)

template <typename T, std::size_t N>
inline Array<T, N> operator*(
		const Array<T, N> & __one, const Array<T, N> & __two) {
	Array<T, N> ret(__one);
	return ret *= __two;
}//operator*(Array, Array)

template <typename T, std::size_t N>
inline Array<T, N> operator/(
		const Array<T, N> & __one, const Array<T, N> & __two) {
	Array<T, N> ret(__one);
	return ret /= __two;
}//operator/(Array, Array)
	
/**
 * --------------------------------------------------
 *  Specialized Algorithms
 * --------------------------------------------------
 */
template <typename T, std::size_t N>
inline void swap(Array<T, N> & lhs, Array<T, N> & rhs) {
	return lhs.swap(rhs);
}//swap(Array, Array)

} //namespace data_structure
} //namespace adamcavendish

