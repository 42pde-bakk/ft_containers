/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BidirectionalIterator.hpp                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 12:20:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/10 00:26:52 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BidirectionalIterator_HPP
# define BidirectionalIterator_HPP

# include <limits>
# include <memory>
# include <iostream>
# include <cstddef>
# include <cstring>
# include "../Traits.hpp"

namespace ft {

	template < typename T, class Category = std::bidirectional_iterator_tag >
	class BidirectionalIterator {
	protected:
		node<T>	*ptr;
	public:
		typedef T							value_type;
		typedef value_type&					reference;
		typedef value_type*					pointer;
		typedef node<value_type>*			node_pointer;
		typedef size_t						size_type;
		typedef ptrdiff_t					difference_type;
		typedef Category					iterator_category;
		typedef BidirectionalIterator		self_type;

		BidirectionalIterator() : ptr(NULL) { }
		BidirectionalIterator(node_pointer element) : ptr(element) {}
		BidirectionalIterator(const BidirectionalIterator& other) {
			*this = other;
		}
		BidirectionalIterator&	operator=(const BidirectionalIterator& other) {
			if (this != &other)
				this->ptr = other.ptr;
			return *this;
		}
		~BidirectionalIterator() {}

		BidirectionalIterator	operator++(int) {
			if (this->ptr)
				this->ptr = this->ptr->next;
			return *this;
		}
		BidirectionalIterator&	operator++() {
			if (this->ptr)
				this->ptr = this->ptr->next;
			return *this;
		}
		BidirectionalIterator	operator--(int) {
			if (this->ptr)
				this->ptr = this->ptr->prev;
			return *this;
		}
		BidirectionalIterator&	operator--() {
			if (this->ptr)
				this->ptr = this->ptr->prev;
			return *this;
		}
		reference	operator*() {
			return this->ptr->data;
		}
		pointer		operator->() {
			return (&(this->ptr->data));
		}
		bool	operator==(const BidirectionalIterator& rhs) const {
			if (this->ptr == rhs.ptr)
				return true;
			return false;
		}
		bool	operator!=(const BidirectionalIterator& rhs) const {
			if (this->ptr == rhs.ptr)
				return false;
			return true;
		}
		node<T>	*getptr() const {
			return this->ptr;
		}
		node<T>	*getnext() {
			return this->ptr->next;
		}
		node<T>	*getprev() {
			return this->ptr->prev;
		}
	};
	template < typename T, class Category = std::bidirectional_iterator_tag >
	class ConstBidirectionalIterator : public BidirectionalIterator<T> {
	public:
		typedef T					value_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef node<value_type>*	node_pointer;
		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;
		typedef Category			iterator_category;
	
		ConstBidirectionalIterator() : BidirectionalIterator<T>() {
		}
		ConstBidirectionalIterator(node_pointer element) : BidirectionalIterator<T>(element) {
		}
		ConstBidirectionalIterator(const ConstBidirectionalIterator& other) : BidirectionalIterator<T>() {
			*this = other;
		}
		ConstBidirectionalIterator(const BidirectionalIterator<T>& other) : BidirectionalIterator<T>() {
			*this = other;
		}
		ConstBidirectionalIterator&	operator=(const ConstBidirectionalIterator& other) {
			this->ptr = other.ptr;
			return *this;
		}
		ConstBidirectionalIterator&	operator=(const BidirectionalIterator<T>& other) {
			this->ptr = other.getptr();
			return *this;
		}
		~ConstBidirectionalIterator() { }

		const_reference	operator*() {
			return (this->ptr->data);
		}
		const_pointer		operator->() {
			return (&(this->ptr->data));
		}
	};

	template < typename T, class Category = std::bidirectional_iterator_tag >
	class RevBidirectionalIterator {
	protected:
		node<T>	*ptr;
	public:
		typedef T					value_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef node<value_type>*	node_pointer;
		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;
		typedef Category			iterator_category;
		// typedef RevBidirectionalIterator self_type;

		RevBidirectionalIterator() : ptr(NULL) { }
		RevBidirectionalIterator(node_pointer element) : ptr(element) { }
		RevBidirectionalIterator(const RevBidirectionalIterator& other) {
			*this = other;
		}
		RevBidirectionalIterator&	operator=(const RevBidirectionalIterator& other) {
			if (this != &other)
				this->ptr = other.ptr;
			return *this;
		}
		~RevBidirectionalIterator() { }
		RevBidirectionalIterator	operator++(int) {
			if (this->ptr)
				this->ptr = this->ptr->prev;
			return *this;
		}
		RevBidirectionalIterator&	operator++() {
			if (this->ptr)
				this->ptr = this->ptr->prev;
			return *this;
		}
		RevBidirectionalIterator	operator--(int) {
			if (this->ptr)
				this->ptr = this->ptr->next;
			return *this;
		}
		RevBidirectionalIterator&	operator--() {
			if (this->ptr)
				this->ptr = this->ptr->next;
			return *this;
		}
		reference	operator*() {
			return this->ptr->data;
		}
		pointer		operator->() {
			return (&(this->ptr->data));
		}
		bool	operator==(const RevBidirectionalIterator& rhs) const {
			if (this->ptr == rhs.ptr)
				return true;
			return false;
		}
		bool	operator!=(const RevBidirectionalIterator& rhs) const {
			if (this->ptr == rhs.ptr)
				return false;
			return true;
		}
		node<T>	*getptr() const {
			return this->ptr;
		}
		node<T>	*getnext() {
			return this->ptr->next;
		}
		node<T>	*getprev() {
			return this->ptr->prev;
		}
	};
	template < typename T, class Category = std::bidirectional_iterator_tag >
	class ConstRevBidirectionalIterator : public RevBidirectionalIterator<T> {
	public:
		typedef T					value_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef node<value_type>*	node_pointer;
		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;
		typedef Category			iterator_category;


		ConstRevBidirectionalIterator() : RevBidirectionalIterator<T>() {
		}
		ConstRevBidirectionalIterator(node_pointer element) : RevBidirectionalIterator<T>(element) {
		}
		ConstRevBidirectionalIterator(const ConstRevBidirectionalIterator& other) : RevBidirectionalIterator<T>() {
			*this = other;
		}
		ConstRevBidirectionalIterator(const RevBidirectionalIterator<T>& other) : RevBidirectionalIterator<T>() {
			*this = other;
		}
		ConstRevBidirectionalIterator&	operator=(const ConstRevBidirectionalIterator& other) {
			this->ptr = other.ptr;
			return *this;
		}
		ConstRevBidirectionalIterator&	operator=(const RevBidirectionalIterator<T> &other) {
			this->ptr = other.getptr();
			return *this;
		}
		~ConstRevBidirectionalIterator() { }

		const_reference	operator*() {
			return (this->ptr->data);
		}
		const_pointer		operator->() {
			return (&(this->ptr->data));
		}
	};
}

#endif
