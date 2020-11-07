/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   DequeIterator.hpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/07 16:36:12 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/11/07 16:36:12 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_DEQUEITERATOR_HPP
#define FT_CONTAINERS_DEQUEITERATOR_HPP

#include <cstddef>
#include <iostream>
#include "Colours.h"

namespace ft {

template <class T, class Pointer, class Reference, size_t buff_size, class Category = std::random_access_iterator_tag >
class DequeIterator {
public:
	typedef DequeIterator<T, Pointer, Reference, buff_size>	this_type;
	typedef DequeIterator<T, T*, T&, buff_size>				iterator;
	typedef	DequeIterator<T, const T*, const T&, buff_size>	const_iterator;
	typedef T**			map_pointer;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef ptrdiff_t	difference_type;
	typedef	size_t		size_type;
	typedef	Category	iterator_category;
	template <class T2, class A> friend class	deque;
	template <class T2, class P, class R, size_t B, class C> friend class DequeIterator;
//	template <class Iterator> friend class ReverseDequeIterator;

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
	DequeIterator(const iterator& x) {
		*this = x;
	}
	this_type& operator=(const iterator& x) {
//		if (this != static_cast<this_type*>(&x)) {
			this->first = x.first;
			this->cur = x.cur;
			this->last = x.last;
			this->node = x.node;
//		}
		return *this;
	}
	~DequeIterator() { }

protected:
	void set_node(map_pointer new_node) {
		node = new_node;
		first = *new_node;
		last = first + buff_size;
	}
public:
	reference	operator*() {
		return *cur;
	}
	pointer		operator->() {
		return &operator*();
	}
	this_type& operator++() {
		++cur;
		if (cur == last) {      // if it reach the end of the chunk
			set_node(node + 1); // skip to the next chunk
			cur = first;
		}
		return *this;
	}

// postfix forms of increment
	this_type operator++(int) {
		this_type tmp = *this;
		++*this;//invoke prefix ++
		return tmp;
	}
	this_type& operator--() {
		if(cur == first) { // if it pointer to the begin of the chunk
			set_node(node - 1);//skip to the prev chunk
			cur = last;
		}
		--cur;
		return *this;
	}

	this_type operator--(int) {
		this_type tmp = *this;
		--*this;
		return tmp;
	}
	this_type& operator+=(difference_type n) { // n can be postive or negative
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

	this_type operator+(difference_type n) const {
		this_type tmp = *this;
		return tmp += n;
	}

	this_type& operator-=(difference_type n) {
		return *this += -n;
	}

	this_type operator-(difference_type n) const{
		this_type tmp = *this;
		return tmp -= n;
	}
	difference_type	operator-(const const_iterator& rhs) {
		return this->cur - rhs.cur;
	}
	reference operator[](difference_type n) {
		return *(*this + n);
	}

	bool	operator==(const const_iterator& rhs) { return (this->cur == rhs.cur); }
	bool	operator!=(const const_iterator& rhs) { return (this->cur != rhs.cur); }
	bool	operator<(const const_iterator& rhs) { return (this->cur < rhs.cur); }
	bool	operator>(const const_iterator& rhs) { return (this->cur > rhs.cur); }
	bool	operator<=(const const_iterator& rhs) { return (this->cur <= rhs.cur); }
	bool	operator>=(const const_iterator& rhs) { return (this->cur >= rhs.cur); }
};

	template <class Iterator >
	class ReverseDequeIterator {
	protected:
		Iterator	current;
	public:
		typedef Iterator	iterator_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::size_type size_type;
		typedef typename Iterator::difference_type difference_type;
		template <class T2, class A> friend class	deque;
//		template <class T2, class P, class R, size_t B, class C> friend class ReverseDequeIterator;

		ReverseDequeIterator() : current() { }
		ReverseDequeIterator(const iterator_type& x) : current(x) { }
		ReverseDequeIterator(const ReverseDequeIterator& x) : current(x.current) { }
		template<typename _Iter>
		ReverseDequeIterator(const ReverseDequeIterator<_Iter>& x) : current(x.base()) { } //.base() returns the underlying iterator
		~ReverseDequeIterator() { }
		ReverseDequeIterator&	operator=(const ReverseDequeIterator& x) {
			Iterator::operator=(x);
			return *this;
		}
		iterator_type	base() const { return this->current; }

		reference	operator*() {
			return *current;
		}
		pointer		operator->() {
			return &operator*();
		}
		ReverseDequeIterator&	operator++() {
			--current;
			return *this;
		}
		ReverseDequeIterator	operator++(int) {
			ReverseDequeIterator	tmp(*this);
			--current;
			return tmp;
		}
		ReverseDequeIterator&	operator--() {
			++current;
			return *this;
		}
		ReverseDequeIterator	operator--(int) {
			ReverseDequeIterator	tmp(*this);
			++current;
			return *this;
		}
		ReverseDequeIterator	operator+(difference_type n) const {
			return ReverseDequeIterator(current - n);
		}
		ReverseDequeIterator&	operator+=(difference_type n) {
			current -= n;
			return *this;
		}
		ReverseDequeIterator	operator-(difference_type n) const {
			return ReverseDequeIterator(current + n);
		}
		ReverseDequeIterator&	operator-=(difference_type n) {
			current += n;
			return *this;
		}
		reference				operator[](difference_type n) {
			return *(*this - n);
		}
		inline bool operator==(const ReverseDequeIterator& rhs) {
			return (this->base() == rhs.base());
		}
		inline bool operator!=(const ReverseDequeIterator& rhs) {
			return (this->base() != rhs.base());
		}
		inline bool operator<(const ReverseDequeIterator& rhs) {
			return (this->base() < rhs.base());
		}
		inline bool operator>(const ReverseDequeIterator& rhs) {
			return (this->base() > rhs.base());
		}
		inline bool operator<=(const ReverseDequeIterator& rhs) {
			return (this->base() <= rhs.base());
		}
		inline bool operator>=(const ReverseDequeIterator& rhs) {
			return (this->base() >= rhs.base());
		}

	};

} // namespace ft

#endif //FT_CONTAINERS_DEQUEITERATOR_HPP
