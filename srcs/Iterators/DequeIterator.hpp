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
//		if (this != &x) {
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
		return &(*cur);
	}
	this_type& operator++() {
		++cur;
		if (cur == last) {      //if it reach the end of the chunk
			set_node(node + 1); //skip to the next chunk
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

	template <class T, class Pointer, class Reference, size_t buff_size, class Category = std::random_access_iterator_tag >
	class ReverseDequeIterator {
	public:
		typedef ReverseDequeIterator<T, Pointer, Reference, buff_size>	this_type;
		typedef ReverseDequeIterator<T, T*, T&, buff_size>				iterator;
		typedef	ReverseDequeIterator<T, const T*, const T&, buff_size>	const_iterator;
		typedef T**			map_pointer;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef ptrdiff_t	difference_type;
		typedef	size_t		size_type;
		typedef	Category	iterator_category;
		template <class T2, class A> friend class	deque;
		template <class T2, class P, class R, size_t B, class C> friend class ReverseDequeIterator;
//	friend class DequeIterator;
	protected:
		pointer cur;
		pointer first;		// the begin of the chunk
		pointer	last;		// the end of the chunk
		//because the pointer may skip to other chunk
		//so this pointer to the map
		map_pointer	node;	// pointer to the map

	public:
		ReverseDequeIterator() : cur(NULL), first(NULL), last(NULL), node(NULL) {}

		explicit ReverseDequeIterator(map_pointer new_node) : node(new_node) {
			first = *new_node;
			last = first + buff_size;
		}
		ReverseDequeIterator(const iterator& x) {
			*this = x;
		}
		this_type& operator=(const iterator& x) {
//		if (this != &x) {
			this->first = x.first;
			this->cur = x.cur;
			this->last = x.last;
			this->node = x.node;
//		}
			return *this;
		}
		~ReverseDequeIterator() { }

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
			return &(*cur);
		}
		this_type& operator++() {
			if(cur == first) { // if it pointer to the begin of the chunk
				set_node(node - 1);//skip to the prev chunk
				cur = last;
			}
			--cur;
			return *this;
		}

// postfix forms of increment
		this_type operator++(int) {
			this_type tmp = *this;
			--*this;//invoke prefix ++
			return tmp;
		}
		this_type& operator--() {
			++cur;
			if (cur == last) {      //if it reach the end of the chunk
				set_node(node + 1); //skip to the next chunk
				cur = first;
			}
			return *this;
		}

		this_type operator--(int) {
			this_type tmp = *this;
			++*this;
			return tmp;
		}
		this_type& operator+=(difference_type n) { // n can be postive or negative
			n *= -1;
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
			return tmp -= n;
		}

		this_type& operator-=(difference_type n) {
			return *this -= n;
		}

		this_type operator-(difference_type n) const{
			this_type tmp = *this;
			return tmp += n;
		}
		difference_type	operator-(const const_iterator& rhs) {
			return this->cur + rhs.cur;
		}
		reference operator[](difference_type n) {
			return *(*this - n);
		}

		bool	operator==(const const_iterator& rhs) { return (this->cur == rhs.cur); }
		bool	operator!=(const const_iterator& rhs) { return (this->cur != rhs.cur); }
		bool	operator<(const const_iterator& rhs) { return (rhs.cur < this->cur); }
		bool	operator>(const const_iterator& rhs) { return (rhs.cur > this->cur); }
		bool	operator<=(const const_iterator& rhs) { return (rhs.cur <= this->cur); }
		bool	operator>=(const const_iterator& rhs) { return (rhs.cur >= this->cur); }
	};

} // namespace ft

#endif //FT_CONTAINERS_DEQUEITERATOR_HPP
