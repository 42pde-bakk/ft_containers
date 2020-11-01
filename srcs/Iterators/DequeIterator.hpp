//
// Created by Peer De bakker on 10/26/20.
//

#ifndef FT_CONTAINERS_DEQUEITERATOR_H
#define FT_CONTAINERS_DEQUEITERATOR_H

#include <cstddef>
#include <iostream>
#include "Colours.h"

template <class T, size_t buff_size>
class DequeIterator {
public:
	typedef DequeIterator<T, buff_size>			iterator;
	typedef T**									map_pointer;
	typedef T&				reference;
	typedef	DequeIterator	self;
	typedef ptrdiff_t		difference_type;
	typedef	size_t			size_type;

	// pointer to the chunk
	T* cur;
	T* first;		// the begin of the chunk
	T* last;		// the end of the chunk

	//because the pointer may skip to other chunk
	//so this pointer to the map
	map_pointer	node;	// pointer to the map

	DequeIterator() {}

	explicit DequeIterator(map_pointer new_node) : node(new_node) {
		first = *new_node;
		last = first + buff_size;
	}
	void set_node(map_pointer new_node) {
		node = new_node;
		first = *new_node;
		last = first + buff_size;
	}
	reference operator*() const {
		return *cur;
	}
	self& operator++() {
		++cur;
		if (cur == last) {      //if it reach the end of the chunk
			set_node(node + 1); //skip to the next chunk
			cur = first;
		}
		return *this;
	}

// postfix forms of increment
	self operator++(int) {
		self tmp = *this;
		++*this;//invoke prefix ++
		return tmp;
	}
	self& operator--() {
		if(cur == first) { // if it pointer to the begin of the chunk
			set_node(node - 1);//skip to the prev chunk
			cur = last;
		}
		--cur;
		return *this;
	}

	self operator--(int) {
		self tmp = *this;
		--*this;
		return tmp;
	}
	self& operator+=(difference_type n) { // n can be postive or negative
		difference_type offset = n + (cur - first);

		if (offset >=0 && offset < difference_type(buff_size)) { // in the same chunk
			cur += n;
		}
		else {//not in the same chunk
			difference_type node_offset;
			if (offset > 0) {
				node_offset = offset / difference_type(buff_size);
			}
			else {
				node_offset = -((-offset - 1) / difference_type(buff_size)) - 1 ;
			}
			// skip to the new chunk
			set_node(node + node_offset);
			// set new cur
			cur = first + (offset - node_offset * buff_size);
		}
		return *this;
	}

	// skip n steps
	self operator+(difference_type n) const {
		self tmp = *this;
		return tmp+= n; //reuse  operator +=
	}

	self& operator-=(difference_type n) {
		return *this += -n; //reuse operator +=
	}

	self operator-(difference_type n) const{
		self tmp = *this;
		return tmp -= n; //reuse operator +=
	}

	// random access (iterator can skip n steps)
	// invoke operator + ,operator *
	reference operator[](difference_type n) const{
		return *(*this + n);
	}

	bool	operator==(const DequeIterator& rhs) { return (this->cur == rhs.cur); }
	bool	operator!=(const DequeIterator& rhs) { return !(*this == rhs); }
};

//template <class T>
//class	DequeIterator {
//public:
//	typedef DequeIterator<T>	iterator;
//	typedef T					value_type;
//	typedef	size_t				size_type;
//	typedef ptrdiff_t			difference_type;
//	typedef T*					pointer;
//	typedef const T*			const_pointer;
//	typedef T&					reference;
//	typedef const T&			const_reference;
//	typedef T**					map_pointer;
//protected:
//	const pointer* p;
//public:
//	DequeIterator() : p(0) {}
//	DequeIterator(const DequeIterator& x) : p(x.p) {}
//	DequeIterator(const pointer *p) : p(p) {}
//	virtual ~DequeIterator() {}
//	reference		operator*() { return (**this->p); }
//	const_reference	operator*() const { return (**this->p); }
//	pointer			operator->() { return (*this->p); }
//	const_pointer	operator->() const { return (*this->p); }
//	reference			operator[](int n) { return (**(this->p + n)); }
//	const_reference		operator[](int n) const { return (**(this->p + n)); }
//
//	DequeIterator operator++(int) {
//		DequeIterator tmp(*this);
//		++this->p;
//		return (tmp);
//	}
//	DequeIterator &operator++() {
//		++this->p;
//		return (*this);
//	}
//	DequeIterator operator--(int) {
//		DequeIterator tmp(*this);
//		--this->p;
//		return (tmp);
//	}
//	DequeIterator &operator--() {
//		--this->p;
//		return (*this);
//	}
//
//	DequeIterator &operator+=(int value) {
//		this->p += value;
//		return (*this);
//	}
//	DequeIterator operator+(int value) const {
//		DequeIterator tmp(*this);
//		return (tmp += value);
//	}
//	DequeIterator &operator-=(int value) {
//		this->p -= value;
//		return (*this);
//	}
//	DequeIterator operator-(int value) const {
//		DequeIterator tmp(*this);
//		return (tmp -= value);
//	}
//	difference_type operator-(DequeIterator const &other) const {
//		return (this->p - other.p);
//	}
//
//	bool operator==(DequeIterator const &other) const {
//		return (this->p == other.p);
//	}
//	bool operator!=(DequeIterator const &other) const {
//		return (this->p != other.p);
//	}
//	bool operator<(DequeIterator const &other) const {
//		return (this->p < other.p);
//	}
//	bool operator<=(DequeIterator const &other) const {
//		return (this->p <= other.p);
//	}
//	bool operator>(DequeIterator const &other) const {
//		return (this->p > other.p);
//	}
//	bool operator>=(DequeIterator const &other) const {
//		return (this->p >= other.p);
//	}
//};

#endif //FT_CONTAINERS_DEQUEITERATOR_H
