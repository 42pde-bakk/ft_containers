/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BidirectionalIterator.hpp                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 12:20:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/11/06 14:41:11 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONALITERATOR_HPP
# define BIDIRECTIONALITERATOR_HPP

# include <memory>
# include <cstddef>
# include "MapNode.hpp"

namespace ft {

	template < typename T, typename Pointer, typename Reference, class C >
	class MapIterator {
	public:
		typedef MapIterator<T, Pointer, Reference, C >	this_type;
		typedef MapIterator<T,		 T*,	   T&, C >	iterator;
		typedef MapIterator<T, const T*, const T&, C >	const_iterator;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
		typedef T			value_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		// typedef C			key_compare;
		typedef node<T, C>*	node_pointer;
		typedef std::bidirectional_iterator_tag				iterator_category;
		template <class T2, class P, class R, class C2>		friend class MapIterator;
	protected:
		node_pointer	ptr;
	public:

		MapIterator() : ptr(NULL) { }
		MapIterator(node_pointer element) : ptr(element) {}
		MapIterator(const iterator& other) {
			*this = other;
		}

		this_type&	operator=(const iterator& other) {
			// if (this != &other)
			this->ptr = other.ptr;
			return *this;
		}
		virtual ~MapIterator() {}

		this_type	operator++(int) {
			this_type	out(*this);
			this->ptr = ptr->getnext();
			return out;
		}
		this_type&	operator++() {
			this->ptr = ptr->getnext();
			return *this;
		}
		this_type	operator--(int) {
			this_type	out(*this);
			this->ptr = ptr->getprevious();
			return out;
		}
		this_type&	operator--() {
			this->ptr = ptr->getprevious();
			return *this;
		}
		reference	operator*() {
			return this->ptr->data;
		}
		pointer		operator->() {
			return (&(this->ptr->data));
		}
		bool	operator==(this_type& rhs) {
			return (this->ptr == rhs.ptr);
		}
		bool	operator!=(this_type& rhs) {
			return (this->ptr != rhs.ptr);
		}
		bool	operator==(const const_iterator& rhs) const {
			return (this->ptr == rhs.ptr);
		}
		bool	operator!=(const const_iterator& rhs) const {
			return (this->ptr != rhs.ptr);
		}
		node_pointer	getptr() const {
			return this->ptr;
		}
	protected:
		node_pointer	getnext() {
			return this->ptr->getnext();
		}
		node_pointer	getprev() {
			return this->ptr->getprevious();
		}
	};

	template < typename T, typename P, typename R, typename Comp, class Category = std::bidirectional_iterator_tag >
	class ReverseMapIterator : public MapIterator<T, P, R, Comp> {
	public:
		typedef MapIterator<T, P, R, Comp>		Base;
		// using typename Base::key_compare;
		using typename Base::value_type;
		using typename Base::reference;
		using typename Base::pointer;
		// using typename Base::const_reference;
		// using typename Base::const_pointer;
		using typename Base::node_pointer;
		using typename Base::size_type;
		using typename Base::difference_type;
		typedef ReverseMapIterator	self_type;
		typedef Category					iterator_category;
		typedef ReverseMapIterator<T,  P,  R,  Comp>					this_type;
		typedef ReverseMapIterator <T, T*, T&, Comp >				iterator;
		typedef ReverseMapIterator <T, const T*, const T&, Comp >	const_iterator;

		ReverseMapIterator() : Base() { }
		ReverseMapIterator(node_pointer element) : Base(element) { }
		ReverseMapIterator(const iterator& x) : Base() {
			*this = x;
		}
		virtual this_type&	operator=(const iterator& x) {
			Base::operator=(x);
			return *this;
		}
		virtual ~ReverseMapIterator() { }
		this_type	operator++(int) {
			this_type	out(*this);
			this->ptr = this->ptr->getprevious();
			return out;
		}
		this_type&	operator++() {
			Base::operator--();
			return *this;
		}
		this_type	operator--(int n) {
			Base::operator++(n);
			return *this;
		}
		this_type&	operator--() {
			Base::operator++();
			return *this;
		}
	};

}

#endif
