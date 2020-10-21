/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BidirectionalIterator.hpp                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 12:20:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/20 14:40:10 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BidirectionalIterator_HPP
# define BidirectionalIterator_HPP

# include <memory>
# include <cstddef>

namespace ft {

	template < typename T, typename N, class Category = std::bidirectional_iterator_tag >
	class BidirectionalIterator {
	public:
		typedef T							value_type;
		typedef value_type&					reference;
		typedef value_type*					pointer;
		typedef N                           node_pointer;
		typedef size_t						size_type;
		typedef ptrdiff_t					difference_type;
		typedef Category					iterator_category;
		typedef BidirectionalIterator		self_type;

		BidirectionalIterator() : ptr(NULL) { }
		BidirectionalIterator(node_pointer element) : ptr(element) {}
		BidirectionalIterator(const BidirectionalIterator& other) {
			*this = other;
		}

		virtual BidirectionalIterator&	operator=(const BidirectionalIterator& other) {
			if (this != &other)
				this->ptr = other.ptr;
			return *this;
		}
		virtual ~BidirectionalIterator() {}

		BidirectionalIterator	operator++(int) {
			BidirectionalIterator	out(*this);
			this->ptr = ptr->getnext();
			return out;
		}
		BidirectionalIterator&	operator++() {
			this->ptr = ptr->getnext();
			return *this;
		}
		BidirectionalIterator	operator--(int) {
			BidirectionalIterator	out(*this);
			this->ptr = ptr->getprevious();
			return out;
		}
		BidirectionalIterator&	operator--() {
			this->ptr = ptr->getprevious();
			return *this;
		}
		reference	operator*() {
			return this->ptr->data;
		}
		pointer		operator->() {
			return (&(this->ptr->data));
		}
		bool	operator==(const BidirectionalIterator& rhs) const {
			return (this->ptr == rhs.ptr);
		}
		bool	operator!=(const BidirectionalIterator& rhs) const {
			return (this->ptr != rhs.ptr);
		}
		node_pointer	getptr() const {
			return this->ptr;
		}
		node_pointer	getnext() {
			return this->ptr->getnext();
		}
		node_pointer	getprev() {
			return this->ptr->getprevious();
		}
	protected:
		node_pointer	ptr;
	};
	template < typename T, typename N, class Category = std::bidirectional_iterator_tag >
	class ConstBidirectionalIterator : public BidirectionalIterator<T, N> {
	public:
		typedef T					value_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef N                   node_pointer;
		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;
		typedef Category			iterator_category;
	
		ConstBidirectionalIterator() : BidirectionalIterator<T, N>() {
		}
		ConstBidirectionalIterator(node_pointer element) : BidirectionalIterator<T, N>(element) {
		}
		ConstBidirectionalIterator(const ConstBidirectionalIterator& other) : BidirectionalIterator<T, N>() {
			*this = other;
		}
		ConstBidirectionalIterator(const BidirectionalIterator<T, N>& other) : BidirectionalIterator<T, N>() {
			*this = other;
		}
		ConstBidirectionalIterator&	operator=(const ConstBidirectionalIterator& other) {
			this->ptr = other.ptr;
			return *this;
		}
		ConstBidirectionalIterator&	operator=(const BidirectionalIterator<T, N>& other) {
			this->ptr = other.getptr();
			return *this;
		}
		virtual ~ConstBidirectionalIterator() { }
		const_reference	operator*() {
			return (this->ptr->data);
		}
		const_pointer		operator->() {
			return (&(this->ptr->data));
		}
	};

	template < typename T, typename N, class Category = std::bidirectional_iterator_tag >
	class RevBidirectionalIterator {
	public:
		typedef T					value_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef N					node_pointer;
		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;
		typedef Category			iterator_category;

		RevBidirectionalIterator() : ptr(NULL) { }
		RevBidirectionalIterator(node_pointer element) : ptr(element) { }
		RevBidirectionalIterator(const RevBidirectionalIterator& other) {
			*this = other;
		}

		virtual RevBidirectionalIterator&	operator=(const RevBidirectionalIterator& other) {
			if (this != &other)
				this->ptr = other.ptr;
			return *this;
		}
		virtual ~RevBidirectionalIterator() { }
		RevBidirectionalIterator	operator++(int) {
			RevBidirectionalIterator	out(*this);
			this->ptr = this->ptr->getprevious();
			return out;
		}
		RevBidirectionalIterator&	operator++() {
			this->ptr = this->ptr->getprevious();
			return *this;
		}
		RevBidirectionalIterator	operator--(int) {
			RevBidirectionalIterator	out(*this);
			this->ptr = this->ptr->getnext();
			return out;
		}
		RevBidirectionalIterator&	operator--() {
			this->ptr = this->ptr->getnext();
			return *this;
		}
		reference	operator*() {
			return this->ptr->data;
		}
		pointer		operator->() {
			return (&(this->ptr->data));
		}
		bool	operator==(const RevBidirectionalIterator& rhs) const {
			return (this->ptr == rhs.ptr);
		}
		bool	operator!=(const RevBidirectionalIterator& rhs) const {
			return (this->ptr != rhs.ptr);
		}
		node_pointer	getptr() const {
			return this->ptr;
		}
		node_pointer	getnext() {
			return this->ptr->next;
		}
		node_pointer	getprev() {
			return this->ptr->prev;
		}
	protected:
		node_pointer	ptr;
	};
	template < typename T, typename N, class Category = std::bidirectional_iterator_tag >
	class ConstRevBidirectionalIterator : public RevBidirectionalIterator<T, N> {
	public:
		typedef T					value_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef N					node_pointer;
		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;
		typedef Category			iterator_category;

		ConstRevBidirectionalIterator() : RevBidirectionalIterator<T, N>() {
		}
		ConstRevBidirectionalIterator(node_pointer element) : RevBidirectionalIterator<T, N>(element) {
		}
		ConstRevBidirectionalIterator(const ConstRevBidirectionalIterator& other) : RevBidirectionalIterator<T, N>() {
			*this = other;
		}
		ConstRevBidirectionalIterator(const RevBidirectionalIterator<T, N>& other) : RevBidirectionalIterator<T, N>() {
			*this = other;
		}
		ConstRevBidirectionalIterator&	operator=(const ConstRevBidirectionalIterator& other) {
			this->ptr = other.ptr;
			return *this;
		}
		ConstRevBidirectionalIterator&	operator=(const RevBidirectionalIterator<T, N> &other) {
			this->ptr = other.getptr();
			return *this;
		}
		virtual ~ConstRevBidirectionalIterator() { }
		const_reference	operator*() {
			return (this->ptr->data);
		}
		const_pointer		operator->() {
			return (&(this->ptr->data));
		}
	};
}

#endif
