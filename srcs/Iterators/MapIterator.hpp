/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MapIterator.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 12:20:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/11/07 20:04:56 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include <memory>
# include <cstddef>

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
		typedef node<T, C>*	node_pointer;
		typedef std::bidirectional_iterator_tag				iterator_category;
		// make map also friend 
		template <class T2, class P, class R, class C2>		friend class MapIterator;
	protected:
		node_pointer	ptr;
	public:
	
		MapIterator() : ptr(NULL) { }
		MapIterator(const node_pointer element) : ptr(element) {}
		MapIterator(const iterator& x) : ptr(const_cast<node_pointer>(x.ptr)) { }

		this_type&	operator=(const const_iterator& x) {
			this->ptr = x.ptr;
			return *this;
		}
		virtual ~MapIterator() {}

		MapIterator	operator++(int) {
			MapIterator	out(*this);
			this->ptr = ptr->getnext();
			return out;
		}
		MapIterator&	operator++() {
			this->ptr = ptr->getnext();
			return *this;
		}
		MapIterator	operator--(int) {
			MapIterator	out(*this);
			this->ptr = ptr->getprevious();
			return out;
		}
		MapIterator&	operator--() {
			this->ptr = ptr->getprevious();
			return *this;
		}
		reference	operator*() {
			return this->ptr->data;
		}
		pointer		operator->() {
			return (&(this->ptr->data));
		}
		bool	operator==(const const_iterator& rhs) const {
			return (this->ptr == rhs.ptr);
		}
		bool	operator!=(const const_iterator& rhs) const {
			return (this->ptr != rhs.ptr);
		}

	protected:
		node_pointer	getptr() const { // make private
			return this->ptr;
		}
		node_pointer	getnext() { // make private
			return this->ptr->getnext();
		}
		node_pointer	getprev() { // make private
			return this->ptr->getprevious();
		}
	};

} // ft

#endif
