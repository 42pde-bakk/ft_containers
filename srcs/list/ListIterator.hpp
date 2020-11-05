/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ListIterator.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 22:22:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/11/05 23:07:22 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTITERATOR_HPP
# define LISTITERATOR_HPP

# include <memory>
# include <cstddef>
# include "ListNode.hpp"

namespace ft {
	
template <typename T, typename Pointer, typename Reference>
struct ListIterator
{
	typedef ListIterator<T, Pointer, Reference>			this_type;
	typedef ListIterator<T, T*, T&>						iterator;
	typedef ListIterator<T, const T*, const T&>			const_iterator;
	typedef size_t										size_type;
	typedef ptrdiff_t									difference_type;
	typedef T											value_type;
	typedef node<T>										node_type;
	typedef node<T>*									node_pointer;
	typedef Pointer										pointer;
	typedef Reference									reference;
	typedef std::bidirectional_iterator_tag				iterator_category;
public:
	node_pointer	ptr;
public:
	ListIterator( ) : ptr(NULL) { }
	ListIterator(const node_pointer elem) : ptr(elem) { }
	ListIterator(const iterator& x) : ptr(const_cast<node_pointer>(x.ptr)) {}
	~ListIterator( ) { }

	this_type&	operator=(const iterator& x) {
		this->ptr = x.ptr;
		return *this;
	}

	reference operator*() const { return ptr->data; }
	pointer   operator->() const { return &(this->ptr->data); }

	this_type& operator++() {
		ptr = ptr->next;
		return *this;
	}
	this_type  operator++(int) {
		this_type	out(*this);
		ptr = ptr->next;
		return out;
	}
	this_type& operator--() {
		ptr = ptr->prev;
		return *this;
	}
	this_type  operator--(int) {
		this_type	out(*this);
		ptr = ptr->prev;
		return out;
	}
	
	bool	operator==(const this_type& rhs) { return (ptr == rhs.ptr);}
	bool	operator!=(const this_type& rhs) { return (ptr != rhs.ptr);}

	node_pointer	getnext() const { return ptr->next; }
	node_pointer	getprev() const { return ptr->prev; }
	node_pointer	getptr() const { return ptr; }
};

template <typename T, typename Pointer, typename Reference>
struct ReverseListIterator : public ListIterator<T, Pointer, Reference>
{
	typedef	ListIterator<T, Pointer, Reference>					Base;
	typedef ReverseListIterator<T, Pointer, Reference>			this_type;
	typedef ReverseListIterator<T, T*, T&>						iterator;
	typedef ReverseListIterator<T, const T*, const T&>			const_iterator;
	using typename Base::size_type;
	using typename Base::difference_type;
	using typename Base::value_type;
	using typename Base::node_type;
	using typename Base::node_pointer;
	typedef Pointer										pointer;
	typedef Reference									reference;
	typedef std::bidirectional_iterator_tag				iterator_category;
public:
	ReverseListIterator( ) : Base() { }
	ReverseListIterator(const node_pointer elem) : Base(elem) { }
	ReverseListIterator(const iterator& x) : Base(x) { }
	this_type&	operator=(const iterator& x) {
		Base::operator=(x);
		return *this;
	}
	~ReverseListIterator( ) { }

	this_type& operator++() {
		Base::operator--();
		return *this;
	}
	this_type  operator++(int n) {
		return Base::operator--(n);
	}
	this_type& operator--() {
		Base::operator++();
		return *this;
	}
	this_type  operator--(int n) {
		return Base::operator++(n);
	}
};

} //ft

#endif
