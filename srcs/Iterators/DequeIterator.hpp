//
// Created by Peer De bakker on 10/26/20.
//

#ifndef FT_CONTAINERS_DEQUEITERATOR_H
#define FT_CONTAINERS_DEQUEITERATOR_H

#include <cstddef>
#include <iostream>
#include "Colours.h"

template <class T, size_t buff_size, class Category = std::random_access_iterator_tag >
class DequeIterator {
public:
	typedef DequeIterator<T, buff_size>			iterator;
	typedef T**									map_pointer;
	typedef T&				reference;
	typedef	DequeIterator	self;
	typedef ptrdiff_t		difference_type;
	typedef	size_t			size_type;
	typedef	Category		iterator_category;
	// pointer to the chunk
	T* cur;
	T* first;		// the begin of the chunk
	T* last;		// the end of the chunk

	//because the pointer may skip to other chunk
	//so this pointer to the map
	map_pointer	node;	// pointer to the map

	DequeIterator() : cur(NULL), first(NULL), last(NULL), node(NULL) {}

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

		if (offset >= 0 && offset < difference_type(buff_size)) { // in the same chunk
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
		return tmp += n; //reuse  operator +=
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
	bool	operator<(const DequeIterator& rhs) { return this->cur < rhs.cur; }
	bool	operator>(const DequeIterator& rhs) { return this->cur > rhs.cur; }
	bool	operator<=(const DequeIterator& rhs) { return this->cur <= rhs.cur; }
	bool	operator>=(const DequeIterator& rhs) { return this->cur >= rhs.cur; }
};



#endif //FT_CONTAINERS_DEQUEITERATOR_H
