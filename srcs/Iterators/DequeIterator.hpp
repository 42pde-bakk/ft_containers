//
// Created by Peer De bakker on 10/26/20.
//

#ifndef FT_CONTAINERS_DEQUEITERATOR_HPP
#define FT_CONTAINERS_DEQUEITERATOR_HPP

#include <cstddef>
#include <iostream>
#include "Colours.h"

namespace ft {

template <class T, size_t buff_size, class Category = random_access_iterator_tag >
class DequeIterator {
public:
	typedef DequeIterator<T, buff_size>			iterator;
	typedef T**									map_pointer;
	typedef T*									pointer;
	typedef const T*							const_pointer;
	typedef T&									reference;
	typedef const T&							const_reference;
	typedef	DequeIterator						self_type;
	typedef ptrdiff_t							difference_type;
	typedef	size_t								size_type;
	typedef	Category							iterator_category;
	template <class T2, class A> friend class	deque;

protected:
	pointer cur;
	pointer first;		// the begin of the chunk
	pointer	last;		// the end of the chunk
	//because the pointer may skip to other chunk
	//so this pointer to the map
	map_pointer	node;	// pointer to the map

public:
	DequeIterator() : cur(NULL), first(NULL), last(NULL), node(NULL) {}

	explicit DequeIterator(map_pointer new_node) : node(new_node) {
		first = *new_node;
		last = first + buff_size;
	}
	DequeIterator(const self_type& x) {
		*this = x;
	}
	virtual self_type& operator=(const self_type& x) {
		if (this != &x) {
			this->first = x.first;
			this->cur = x.cur;
			this->last = x.last;
			this->node = x.node;
		}
		return *this;
	}
	virtual ~DequeIterator() { }

	void set_node(map_pointer new_node) {
		node = new_node;
		first = *new_node;
		last = first + buff_size;
	}
	reference	operator*() {
		return *cur;
	}
	pointer		operator->() {
		return &(*cur);
	}
	self_type& operator++() {
		++cur;
		if (cur == last) {      //if it reach the end of the chunk
			set_node(node + 1); //skip to the next chunk
			cur = first;
		}
		return *this;
	}

// postfix forms of increment
	self_type operator++(int) {
		self_type tmp = *this;
		++*this;//invoke prefix ++
		return tmp;
	}
	self_type& operator--() {
		if(cur == first) { // if it pointer to the begin of the chunk
			set_node(node - 1);//skip to the prev chunk
			cur = last;
		}
		--cur;
		return *this;
	}

	self_type operator--(int) {
		self_type tmp = *this;
		--*this;
		return tmp;
	}
	self_type& operator+=(difference_type n) { // n can be postive or negative
		difference_type offset = n + (cur - first);

		if (offset >= 0 && offset < difference_type(buff_size)) // in the same chunk
			cur += n;
		else { //not in the same chunk
			difference_type node_offset;
			if (offset > 0) {
				node_offset = offset / difference_type(buff_size);
			}
			else {
				node_offset = -((-offset - 1) / difference_type(buff_size)) - 1 ;
			}
			set_node(node + node_offset); // skip to the new chunk
			cur = first + (offset - node_offset * buff_size);
		}
		return *this;
	}

	// skip n steps
	self_type operator+(difference_type n) const {
		self_type tmp = *this;
		return tmp += n; //reuse  operator +=
	}

	self_type& operator-=(difference_type n) {
		return *this += -n; //reuse operator +=
	}

	self_type operator-(difference_type n) const{
		self_type tmp = *this;
		return tmp -= n; //reuse operator +=
	}

	reference operator[](difference_type n) {
		return *(*this + n);
	}

	virtual bool	operator==(const DequeIterator& rhs) { return (this->cur == rhs.cur); }
	virtual bool	operator!=(const DequeIterator& rhs) { return !(*this == rhs); }
	virtual bool	operator<(const DequeIterator& rhs) { return this->cur < rhs.cur; }
	virtual bool	operator>(const DequeIterator& rhs) { return this->cur > rhs.cur; }
	virtual bool	operator<=(const DequeIterator& rhs) { return this->cur <= rhs.cur; }
	virtual bool	operator>=(const DequeIterator& rhs) { return this->cur >= rhs.cur; }
};

template <class T, size_t buff_size, class Category = random_access_iterator_tag >
class ConstDequeIterator : public DequeIterator<T, buff_size> {
public:
	typedef DequeIterator<T, buff_size>			Base;
	using typename	Base::map_pointer;
	using typename	Base::const_pointer;
	using typename	Base::reference;
	using typename	Base::const_reference;
	using typename	Base::difference_type;
	using typename	Base::size_type;
	typedef ConstDequeIterator					self_type;
	typedef	Category							iterator_category;
	template <class T2, class A> friend class deque;

	ConstDequeIterator() : Base() { }
	ConstDequeIterator(map_pointer new_node) : Base(new_node) { }
	ConstDequeIterator(const Base& x) : Base() {
		*this = x;
	}
	ConstDequeIterator(const self_type& x) : Base() {
		*this = x;
	}
	virtual self_type& operator=(const Base& x) {
		Base::operator=(x);
		return *this;
	}
	virtual self_type&	operator=(const self_type& x) {
		Base::operator=(x);
		return *this;
	}
	virtual ~ConstDequeIterator() { }

	const_reference	operator*() const {
		return *this->cur;
	}
	const_pointer	operator->() const {
		return *(&this->cur);
	}
	const_reference	operator[](size_type n) const {
		return *(*this + n);
	}
};

template <class T, size_t buff_size, class Category = std::random_access_iterator_tag >
class RevDequeIterator : public DequeIterator<T, buff_size> {
public:
	typedef DequeIterator<T, buff_size>			Base;
	using typename	Base::map_pointer;
	using typename	Base::const_pointer;
	using typename	Base::reference;
	using typename	Base::const_reference;
	using typename	Base::difference_type;
	using typename	Base::size_type;
	typedef RevDequeIterator					self_type;
	typedef	Category							iterator_category;
	template <class T2, class A> friend class deque;

	RevDequeIterator() : Base() { }
	explicit RevDequeIterator(map_pointer new_node) : Base(new_node) { }
	RevDequeIterator(const self_type& x) : Base() {
		*this = x;
	}
	RevDequeIterator(const Base& x) : Base() {
		*this = x;
	}
	virtual self_type& operator=(const self_type& x) {
		Base::operator=(x);
		return *this;
	}
	virtual self_type& operator=(const Base& x) {
		Base::operator=(x);
		return *this;
	}
	virtual ~RevDequeIterator() { }

	self_type&	operator++() {
		Base::operator--();
		return *this;
	}
	self_type	operator++(int n) {
		return Base::operator--(n);
	}
	self_type&	operator--() {
		Base::operator++();
		return *this;
	}
	self_type	operator--(int n) {
		return Base::operator++(n);
	}
	self_type&	operator+=(difference_type n) {
		Base::operator-=(n);
		return *this;
	}
	self_type	operator+(difference_type n) const {
		return Base::operator-(n);
	}
	self_type&	operator-=(difference_type n) {
		Base::operator+=(n);
		return *this;
	}
	self_type	operator-(difference_type n) const {
		return Base::operator+(n);
	}
	reference	operator[](difference_type n) {
		return Base::operator[](-n);
	}
	virtual bool	operator<(const self_type& rhs) { return Base::operator>=(rhs); }
	virtual bool	operator>(const self_type& rhs) { return Base::operator<(rhs); }
	virtual bool	operator<=(const self_type& rhs) { return Base::operator>(rhs); }
	virtual bool	operator>=(const self_type& rhs) { return Base::operator<(rhs); }
};


template <class T, size_t buff_size, class Category = std::random_access_iterator_tag >
class ConstRevDequeIterator : public RevDequeIterator<T, buff_size> {
public:
	typedef RevDequeIterator<T, buff_size>			Base;
	using typename	Base::map_pointer;
	using typename	Base::const_pointer;
	using typename	Base::reference;
	using typename	Base::const_reference;
	using typename	Base::difference_type;
	using typename	Base::size_type;
	typedef ConstRevDequeIterator					self_type;
	typedef	Category							iterator_category;
	template <class T2, class A> friend class	deque;

	ConstRevDequeIterator() : Base() { }
	ConstRevDequeIterator(map_pointer new_node) : Base(new_node) { }
	ConstRevDequeIterator(const Base& x) : Base(x) { }
	ConstRevDequeIterator(const self_type& x) : Base(x) { }
	virtual self_type&	operator=(const Base& x) {
		Base::operator=(x);
		return *this;
	}
	virtual	self_type&	operator=(const self_type& x) {
		Base::operator=(x);
		return *this;
	}
	virtual ~ConstRevDequeIterator() { }
	const_reference	operator*() const {
		return *this->cur;
	}
	const_pointer	operator->() const {
		return *(&this->cur);
	}
	const_reference	operator[](difference_type n) const {
		return *(*this - n);
	}

};

} // namespace ft

#endif //FT_CONTAINERS_DEQUEITERATOR_HPP
