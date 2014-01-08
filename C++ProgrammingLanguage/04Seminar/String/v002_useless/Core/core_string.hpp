#pragma once

class core_string
{
public:
	virtual inline void _reallocate(const size_t & sz);
	virtual inline void _reduce(const size_t & sz);
private:

public:
protected:
	size_t __max_size;
	size_t __len;
	char * __p_string;
private:
};

template <size_t basic_allocate_size>
inline void base_string<basic_allocate_size>::_reallocate(const size_t & sz)
{
	if(sz <= __max_size)
		return;

	size_t n_sz = 1;
	while(n_sz < sz)
		n_sz <<= 1;

	const char *cache =  __p_string;
	__p_string = new char[n_sz];
	__max_size = n_sz;
	memcpy(__p_string, cache, __len);
	delete cache;
}//_reallocate(sz)

template <size_t basic_allocate_size>
inline void base_string<basic_allocate_size>::_reduce(const size_t & sz)
{
	if(sz >= __max_size)
		return;

	const char *cache = __p_string;
	__p_string = new char[sz];
	__max_size = sz;
	memcpy(__p_string, cache, __len);
	delete cache;
}//_reduce(sz)

