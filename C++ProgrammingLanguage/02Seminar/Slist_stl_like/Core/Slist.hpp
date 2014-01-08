#pragma once // used for include only once

typedef	DataType * iterator;
typedef const DataType * const_iterator;

struct _slist_node_base
{
	_slist_node_base * _next;
}; // struct _slist_node_base

inline slist_node_base * _slist_make_link(
		_slist_node_base * _prev_node,
		_slist_node_base * _new_node)
{
	_new_node->_next = _prev_node->_next;
	_prev_node->_next = _new_node;
}//_slist_make_link(_prev_node, _new_node)

inline _slist_node_base * _slist_previous(
		_slist_node_base * _head,
		const _slist_node_base * _node)
{
	  while ((_head != NULL) && (_head->_next != _node))
		      _head = _head->_next;
	  return _head;
}//_slist_previous(_head, _node)

// const version of _slist_previous
inline const _slist_node_base * _slist_previous(
		const _slist_node_base * _head,
		const _slist_node_base * _node)
{
	  while ((_head != NULL) && (_head->_next != _node))
		      _head = _head->_next;
	    return _head;
}//_slist_previous(_head, _node)

inline void _slist_splice_after(
		_slist_node_base * _pos,
		_slist_node_base * _before_first,
		_slist_node_base * _before_last)
{
	if (_pos != _before_first && _pos != _before_last) {
		_slist_node_base * _first = _before_first->_next;
		_slist_node_base * _after = _pos->_next;
		_before_first->_next = _before_last->_next;
		_pos->_next = _first;
		_before_last->_next = _after;
	}//if
}//_slist_splice_after(_pos, _before_first, _before_last)

inline void _slist_splice_after(
		_slist_node_base * _pos,
		_slist_node_base * _head)
{
	_slist_node_base * _before_last = _slist_previous(_head, NULL);
	if (_before_last != _head) {
		_slist_node_base * _after = _pos->_next;
		_pos->_next = _head->_next;
		_head->_next = NULL;
		_before_last->_next = _after;
	}//if
}//_slist_splice_after(_pos, _head)

inline _slist_node_base * _slist_reverse(
		_slist_node_base * _node)
{
	_slist_node_base * _result = _node;
	_node = _node->_next;
	_result->_next = NULL;
	while(_node != NULL) {
		_slist_node_base * _next = _node->_next;
		_node->_next = _result;
		_result = _node;
		_node = _next;
	}//while
	return _result;
}//_slist_reverse(_node)

inline size_t _slist_size(_slist_node_base * _node)
{
	size_t _result = 0;
	for(; _node != NULL; _node = _node->_next)
		++_result;
	return _result;
}//_slist_size(_node)

template <typename DataType>
struct _slist_node : public _slist_node_base
{
	DataType _data;
};//struct _slist_node

struct _slist_iterator_base
{
	_slist_iterator_base * _node;

	void inc() { _node = node->next; } // used for increment

	bool operator==(const _slist_iterator_base & _x) const {
		return _node == _x._node;
	}//operator==

	bool operator!=(const _Slist_iterator_base & _x) const {
		return _node != _x._node;
	}//operator!=
};//struct _slist_iterator_base

template <class _Tp, class _Ref, class _Ptr>
struct _slist_iterator : public _slist_iterator_base
{
  typedef _slist_iterator<_Tp, _Tp&, _Tp *>					iterator;
  typedef _slist_iterator<_Tp, const _Tp &, const _Tp *>	const_iterator;
  typedef _slist_iterator<_Tp, _Ref, _Ptr>					_Self;

  typedef _Tp              value_type;
  typedef _Ptr             pointer;
  typedef _Ref             reference;
  typedef _slist_node<_Tp> _Node;

  _slist_iterator(_Node* _x) : _slist_iterator_base(_x) {}
  _slist_iterator() : _slist_iterator_base(NULL) {}
  _slist_iterator(const iterator & _x) : _slist_iterator_base(_x._node) {}

  reference operator*() const { return ((_Node*) _node)->_data; }
  pointer operator->() const { return &(operator*()); }

  _Self& operator++()
  {
    inc();
    return *this;
  }
  _Self operator++(int)
  {
    _Self _tmp = *this;
    inc();
    return _tmp;
  }
};


template <typename DataType>
class SList
{
public:	//functions
	// constructors
	SList();
	SList(List<DataType> &list const); // copy constructor
	SList(DataType arr[]);

	// setters and getters
	iterator begin();
	const_iterator begin() const;

	iterator end();
	const_iterator end() const;

	DataType & front();
	DataType & front() const;

	DataType & back();
	DataType & back() const;

	// Add Node functions
	void push_back(DataType & data const);
	void push_front(DataType & data const);

	void insert(iterator position, DataType & data const);

	// Delete Node functions
	void pop_back();
	void pop_front();

	void erase(iterator position);
	void erase(iterator first, iterator last);

	// sort
	void swap(iterator pos1, iterator pos2);
	void sort(iterator first = begin(), iterator last = end());

	// merge and splice
	void merge(SList<DataType> &list);	// simply merge, no sort
	void splice(iterator position, list<DataType> &list);	// splice 

	// reverse
	void reverse();

	// search
	iterator find(const_iterator start const, DataType & data const);	// if not found return end()
	
	// destructors
	~List();
private: //functions

public: //variables

private: //variables
	_list_node * head;
}; //class List

