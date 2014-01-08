#pragma once

#include <memory>
#include <iterator>
#include <initializer_list>
#include <utility>
#include <stdexcept>
#include <cstdlib>

namespace adamcavendish {
namespace data_structure {

template <
	typename T,
	std::size_t N,
	typename Allocator = std::allocator<T>
> class Array
{
public: // Member types
	typedef T									value_type;
	typedef std::size_t							size_type;
	typedef std::ptrdiff_t						difference_type;
	typedef T &									reference;
	typedef const T &							const_reference;
	typedef T *									pointer;
	typedef const T *							const_pointer;
	typedef T *									iterator;
	typedef const T *							const_iterator;
	typedef std::reverse_iterator<T *>			reverse_iterator;
	typedef std::reverse_iterator<const T *>	const_reverse_iterator;
	typedef Allocator							allocator_type;

public:	// functions
	/**
	 * Default Constructor
	 * -- Build an array of N, initialized with T()
	 */
	explicit Array(const Allocator & alloc = Allocator()) :
		_M_allocator(alloc),
		_M_data(nullptr)
	{
		_M_construct();
	}//Default Constructor
	/**
	 * Constructor with a default value
	 * -- Build an array of N, initialized with T(val)
	 */
	explicit Array(const T & value,
			const Allocator & alloc = Allocator()) :
		_M_allocator(alloc),
		_M_data(nullptr)
	{
		_M_construct();
	}//Constructor(value, alloc)
	/**
	 * Constructor with a ranged elements
	 * -- Build an array of N with the contents of the range [first, last)
	 *Important!
	 *	InputIt must meet the requirements of InputIterator.
	 */
	template <typename InputIt>
	explicit Array(const InputIt & first, const InputIt & last,
			const Allocator & alloc = Allocator()) :
		_M_allocator(alloc),
		_M_data(nullptr)
	{
		_M_construct(first, last);
	}//Construct(first, last)
	/**
	 * Copy Constructor
	 * -- Build an array as a copy of rhs
	 * -- Allocator is copied.
	 */
	Array(const Array & rhs) : 
		_M_allocator(rhs._M_allocator),
		_M_data(nullptr)
	{
		_M_construct(rhs.cbegin(), rhs.cend());
	}//Copy Constructor
	/**
	 * Copy Constructor with a new Allocator
	 * -- Build an array as a copy of rhs
	 * -- Allocator is provided
	 */
	Array(const Array & rhs, const Allocator & alloc) :
		_M_allocator(alloc),
		_M_data(nullptr)
	{
		_M_construct(rhs.cbegin(), rhs.cend());
	}//Copy Constructor(alloc)
	/**
	 * Move Constructor
	 * -- Build an array using move sematics.
	 * -- Allocator is moved.
	 */
	Array(Array && rhs) :
		_M_allocator(std::move(rhs._M_allocator)),
		_M_data(std::move(rhs._M_data))
	{
		rhs._M_data = nullptr;
	}
	/**
	 * Initializer_list Constructor
	 * -- Build an array with the contents of the initializer list
	 */
	Array(std::initializer_list<T> init,
			const Allocator & alloc = Allocator()) :
		_M_allocator(alloc),
		_M_data(nullptr)
	{
		_M_construct(init.begin(), init.end());
	}//Initializer_list Constructor

	/**
	 * Destructor
	 * -- Destructs the Array, free all memory.
	 */
	~Array() {
		_M_destruct();
	}//~Array()

	/**
	 * operator=
	 * -- overwrites every element of the array
	 */
	Array & operator=(const Array & rhs) {
		if(this == &rhs)
			return (*this);
		_M_destruct();
		_M_construct(rhs.cbegin(), rhs.cend());
		return (*this);
	}//operator=(rhs)
	Array & operator=(Array && rhs) {
		if(this == &rhs)
			return (*this);
		_M_destruct();
		_M_allocator = std::move(rhs._M_allocator);
		_M_data = std::move(rhs._M_data);
		rhs._M_data = nullptr;
		return (*this);
	}//move operator=(rhs)

	/**
	 * returns the associated allocator
	 */
	allocator_type get_allocator() const noexcept {
		return _M_allocator;
	}//get_allocator()

	/**
	 *	--------------------------------------------------	
	 *	Element Access
	 *	--------------------------------------------------
	 */

	/**
	 * access specified element with bounds checking
	 */
	reference at(size_type pos) {
		_M_range_check(pos);
		return _M_data[pos];
	}//at(pos)
	const_reference	at(size_type pos) const {
		_M_range_check(pos);
		return _M_data[pos];
	}//at(pos) const

	/**
	 * access apecified element without bounds checking
	 */
	reference operator[](size_type pos) {
		return _M_data[pos];
	}//operator[](pos)
	const_reference operator[](size_type pos) const {
		return _M_data[pos];
	}//operator[](pos) const

	/**
	 * access the first element
	 */
	reference front() {
		return _M_data[0];
	}//front()
	const_reference front() const {
		return _M_data[0];
	}//front() const

	/**
	 * access the last element
	 */
	reference back() {
		return _M_data[_M_length - 1];
	}//back()
	const_reference back() const {
		return _M_data[_M_length - 1];
	}//back()

	/**
	 * direct access to the underlying array
	 * --
	 *  Returns pointer to the underlying array
	 *  serving as element storage. The pointer
	 *  is such that range [data(); data() + size())
	 *  is always a valid range, even if the container is empty.
	 */
	T * data() {
		return std::addressof(_M_data[0]);
	}//data()
	const T * data() const {
		return std::addressof(_M_data[0]);
	}//data() const

	/**
	 * --------------------------------------------------
	 *  Iterators
	 * --------------------------------------------------
	 */

	/**
	 * return an iterator to the beginning
	 */
	iterator begin() noexcept {
		return iterator(_M_data);
	}//begin()
	const_iterator begin() const noexcept {
		return const_iterator(_M_data);
	}//begin() const
	const_iterator cbegin() const noexcept {
		return const_iterator(_M_data);
	}//cbegin()
	/**
	 * return an iterator to the end
	 */
	iterator end() noexcept {
		return iterator(_M_data + _M_length);
	}//end()
	const_iterator end() const noexcept {
		return const_iterator(_M_data + _M_length);
	}//end() const
	const_iterator cend() const noexcept {
		return const_iterator(_M_data + _M_length);
	}//cend()
	/**
	 * return a reverse iterator to the beginning
	 */
	reverse_iterator rbegin() noexcept {
		return reverse_iterator(_M_data + _M_length);
	}//rbegin()
	const_reverse_iterator rbegin() const noexcept {
		return const_reverse_iterator(_M_data + _M_length);
	}//rbegin() const
	const_reverse_iterator crbegin() const noexcept {
		return const_reverse_iterator(_M_data + _M_length);
	}//crbegin()
	/**
	 * return a reverse iterator to the end
	 */
	reverse_iterator rend() noexcept {
		return reverse_iterator(_M_data);
	}//rend()
	const_reverse_iterator rend() const noexcept {
		return const_reverse_iterator(_M_data);
	}//rend() const
	const_reverse_iterator crend() const noexcept {
		return const_reverse_iterator(_M_data);
	}//crend()

	/**
	 * --------------------------------------------------
	 *  Capacity
	 * --------------------------------------------------
	 */

	/**
	 * checks whether the container is empty 
	 */
	constexpr bool empty() const noexcept {
		return (_M_length == 0);
	}//empty()
	/**
	 * returns the number of elements
	 */
	constexpr size_type size() const noexcept {
		return _M_length;
	}//size()
	/**
	 * returns the maximum possible number of elements
	 */
	constexpr size_type max_size() const noexcept {
		return _M_length;
	}//max_size()

	/**
	 * --------------------------------------------------
	 *  Operations
	 * --------------------------------------------------
	 */

	/**
	 * fill the container with specified value
	 */
	void fill(const T & value) {
		try {
			for(size_type pos = 0; pos < _M_length; ++pos)
				_M_data[pos] = value;
		} catch(...) {
			_M_destruct();
			throw;
		}//try-catch
	}//fill(value)
	/**
	 * fill the container with [first, last)
	 *Important!
	 *	InputIt must meet the requirements of InputIterator.
	 */
	template <typename InputIt>
	void fill(const InputIt & first, const InputIt & last) {
		size_type pos = 0;
		InputIt iter = first;
		value_type default_value = value_type();

		try {
			for(; pos < _M_length && iter != last; ++pos, ++iter)
				_M_data[pos] = *iter;
			for(; pos < _M_length; ++pos)
				_M_data[pos] = default_value;
		} catch(...) {
			_M_destruct();
			throw;
		}//try-catch
	}//fill(first, last)
	/**
	 * fill the container with the contents of initializer_list
	 */
	void fill(std::initializer_list<T> init) {
		fill(init.begin(), init.end());
	}//fill(initializer_list)
	/**
	 * swap the contents
	 * --
	 *  Exchanges the contents of the container with those of other.
	 *  Does not cause iterators and references to associate
	 *  with the other container.
	 */
	void swap(Array & other) {
		std::swap(_M_allocator, other._M_allocator);
		std::swap(_M_data, other._M_data);
	}//swap(other)

	/**
	 * --------------------------------------------------
	 * Array Arithmatics
	 * --------------------------------------------------
	 */
	
	/**
	 * add value
	 * --
	 *  All of the contents of the Array is increased by val
	 */
	Array & operator+=(const T & val) {
		for(size_type pos = 0; pos < _M_length; ++pos)
			_M_data[pos] += val;
		return (*this);
	}//operator+=
	/**
	 * subtract value
	 * --
	 *  All of the contents of the Array is decreased by val
	 */
	Array & operator-=(const T & val) {
		for(size_type pos = 0; pos < _M_length; ++pos)
			_M_data[pos] -= val;
		return (*this);
	}//operator-=
	/**
	 * Multiply by value
	 * --
	 *  All of the contents of the Array is mulitplied by val
	 */
	Array & operator*=(const T & val) {
		for(size_type pos = 0; pos < _M_length; ++pos)
			_M_data[pos] *= val;
		return (*this);
	}//operator*=
	/**
	 * Divided by value
	 * --
	 *  All of the contents of the Array is divided by val
	 */
	Array & operator/=(const T & val) {
		for(size_type pos = 0; pos < _M_length; ++pos)
			_M_data[pos] /= val;
		return (*this);
	}//operator/=

	/**
	 * add Array
	 * --
	 *  this[0] += rhs[0];
	 *  this[1] += rhs[1];
	 *  ...
	 *  this[_M_length - 1] += rhs[_M_length - 1];
	 */
	Array & operator+=(const Array & rhs) {
		for(size_type pos = 0; pos < _M_length; ++pos)
			_M_data[pos] += rhs[pos];
		return (*this);
	}//operator+=
	/**
	 * subtract Array
	 */
	Array & operator-=(const Array & rhs) {
		for(size_type pos = 0; pos < _M_length; ++pos)
			_M_data[pos] -= rhs[pos];
		return (*this);
	}//operator-=
	/**
	 * Multiply by Array
	 */
	Array & operator*=(const Array & rhs) {
		for(size_type pos = 0; pos < _M_length; ++pos)
			_M_data[pos] *= rhs[pos];
		return (*this);
	}//operator*=
	/**
	 * Divided by Array
	 */
	Array & operator/=(const Array & rhs) {
		for(size_type pos = 0; pos < _M_length; ++pos)
			_M_data[pos] /= rhs[pos];
		return (*this);
	}//operator/=

protected:	// member functions
	void _M_construct();
	void _M_construct(const T & val);
	template <typename InputIt>
	void _M_construct(const InputIt & first, const InputIt & last);
	
	void _M_destruct();

	void _M_range_check(size_type pos) const throw(std::out_of_range);

protected:	// member variables
	allocator_type _M_allocator;
	pointer _M_data;
	static const size_type _M_length = N;

};// class Array

} // namespace data_structrure
} // namespace adamcavendish

