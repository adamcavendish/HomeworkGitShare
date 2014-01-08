#pragma once // used for include only once

class Slist_iterator;
class Slist_node;
class Slist;

template <typename DataType, typename ReferenceType, typename PointerType>
class Slist_iterator
{
private:
	// only insert_next() has access to private functions and variables
	//friend void Slist::insert_next(iterator position, const DataType & data);
	friend class Slist;
	
	typedef ReferenceType	reference;
	typedef PointerType		pointer;

	typedef Slist_iterator<DataType, DataType &, DataType *>				iterator;
	typedef Slist_iterator<DataType, const DataType &, const DataType *>	const_iterator;
	typedef Slist_iterator<DataType, ReferenceType, PointerType>			self;

	typedef Slist_node<DataType> node;

public: //functions
	Slist_iterator(node * nd, self * next) : _node(nd), _next(next) {}

	self & operator++() { this = this->_next; } // prefix++: ++i

	self operator++(int) { // suffix++: i++
		iterator cp(*this);
		this = this->_next;
		return cp;
	}//operator++(int)

	bool operator==(iterator & iter) const { return _node == iter->_node; }

	bool operator!=(iterator & iter) const { return _node != iter->_node; }

	reference operator*() const { return _node->getData(); }

	pointer operator->() const { return &(operator*()); }
	
	~Slist_iterator() { delete _node; delete _next; }
private: // functions
	Slist_iterator() {}	// default constructor

private: //variables
	node * _node;
	self * _next;
};//class Slist_iterator

template <typename DataType>
class Slist_node
{
public:
	Slist_node(DataType data) { _data = data; }
	inline DataType & getData() const { return _data; }
private:
	DataType _data;
};//class Slist_node

template <typename DataType>
class Slist
{
public:	//functions
	typedef Slist_iterator<DataType, DataType &, DataType *>				iterator;
	typedef Slist_iterator<DataType, const DataType &, const DataType *>	const_iterator;

	typedef Slist_node<DataType> node;

	// constructors
	Slist();
	Slist(const Slist<DataType> & list); // copy constructor
	Slist(size_t arr_size, DataType arr[]);	// initiated from an array

	iterator begin() { return (iterator)_begin; }
	const_iterator begin() const { return (const_iterator *)_begin; }

	iterator end() { return (iterator *)NULL; }
	const_iterator end() const { return (const_iterator *)NULL; }

	DataType & front() { return _begin->_node->getData(); }
	DataType & front() const { return _begin->_node->getData(); }

	// Add Node functions
	inline void push_front(const DataType & data);

	inline void insert_next(iterator position, const DataType & data);

	// Delete Node functions
	inline void pop_front();

	void erase_next(iterator position);
	void erase(iterator position);
	void erase(iterator first, iterator last);

	// sort
	void swap(iterator pos1, iterator pos2);
	void sort(iterator first = begin(), iterator last = end());

	// merge and splice
	void merge(SList<DataType> &list);	// simply merge, no sort
	void splice(iterator position, SList<DataType> &list);	// splice 

	// reverse
	void reverse();

	// search
	iterator find(const_iterator start, const DataType & data) const;	// if not found return NULL
	
	// destructors
	~List();
private: //functions

public: //variables

private: //variables
	iterator _begin;
}; //class List

