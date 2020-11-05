/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BidirectionalIterator.hpp                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 12:20:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/11/05 22:20:59 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONALITERATOR_HPP
# define BIDIRECTIONALITERATOR_HPP

# include <memory>
# include <cstddef>

namespace ft {

	template < typename T, typename P, typename R, typename N, class Category = std::bidirectional_iterator_tag >
	class BidirectionalIterator {
	public:
		typedef T							value_type;
		typedef P	pointer;
		typedef R	reference;
		// typedef value_type&					reference;
		// typedef const value_type&			const_reference;
		// typedef value_type*					pointer;
		// typedef const value_type*			const_pointer;
		typedef N                           node_pointer;
		typedef size_t						size_type;
		typedef ptrdiff_t					difference_type;
		typedef Category					iterator_category;
		typedef BidirectionalIterator		self_type;
		typedef BidirectionalIterator <T,		T*,		  T&, N >		iterator;
		typedef BidirectionalIterator <T, const T*, const T&, N >	const_iterator;

		BidirectionalIterator() : ptr(NULL) { }
		BidirectionalIterator(node_pointer element) : ptr(element) {}
		BidirectionalIterator(const iterator& other) {
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
	// template < typename T, typename N, class Category = std::bidirectional_iterator_tag >
	// class ConstBidirectionalIterator : public BidirectionalIterator<T, N> {
	// public:
	// 	typedef	BidirectionalIterator<T, N>		Base;
	// 	using typename	Base::value_type;
	// 	using typename	Base::reference;
	// 	using typename	Base::const_reference;
	// 	using typename	Base::pointer;
	// 	using typename	Base::const_pointer;
	// 	using typename	Base::node_pointer;
	// 	using typename	Base::size_type;
	// 	using typename	Base::difference_type;
	// 	typedef Category			iterator_category;
	
	// 	ConstBidirectionalIterator() : BidirectionalIterator<T, N>() {
	// 	}
	// 	ConstBidirectionalIterator(node_pointer element) : BidirectionalIterator<T, N>(element) {
	// 	}
	// 	ConstBidirectionalIterator(const ConstBidirectionalIterator& x) : BidirectionalIterator<T, N>() {
	// 		*this = x;
	// 	}
	// 	ConstBidirectionalIterator(const BidirectionalIterator<T, N>& x) : BidirectionalIterator<T, N>() {
	// 		*this = x;
	// 	}
	// 	virtual ConstBidirectionalIterator&	operator=(const ConstBidirectionalIterator& x) {
	// 		Base::operator=(x);
	// 		return *this;
	// 	}
	// 	virtual ConstBidirectionalIterator&	operator=(const BidirectionalIterator<T, N>& x) {
	// 		Base::operator=(x);
	// 		return *this;
	// 	}
	// 	virtual ~ConstBidirectionalIterator() { }
	// 	const_reference	operator*() {
	// 		return (this->ptr->data);
	// 	}
	// 	const_pointer		operator->() {
	// 		return (&(this->ptr->data));
	// 	}
	// };

	template < typename T, typename P, typename R, typename N, class Category = std::bidirectional_iterator_tag >
	class RevBidirectionalIterator : public BidirectionalIterator<T, P, R, N> {
	public:
		typedef BidirectionalIterator<T, P, R, N>		Base;
		using typename Base::value_type;
		using typename Base::reference;
		using typename Base::const_reference;
		using typename Base::pointer;
		using typename Base::const_pointer;
		using typename Base::node_pointer;
		using typename Base::size_type;
		using typename Base::difference_type;
		typedef RevBidirectionalIterator	self_type;
		typedef Category					iterator_category;

		RevBidirectionalIterator() : Base() { }
		RevBidirectionalIterator(node_pointer element) : Base(element) { }
		RevBidirectionalIterator(const self_type& x) : Base() {
			*this = x;
		}
		RevBidirectionalIterator(const Base& x) : Base() {
			*this = x;
		}
		virtual self_type&	operator=(const self_type& x) {
			Base::operator=(x);
			return *this;
		}
		virtual self_type&	operator=(const Base& x) {
			Base::operator=(x);
			return *this;
		}
		virtual ~RevBidirectionalIterator() { }
		RevBidirectionalIterator	operator++(int n) {
			return Base::operator--(n);
		}
		RevBidirectionalIterator&	operator++() {
			Base::operator--();
			return *this;
		}
		RevBidirectionalIterator	operator--(int n) {
			return Base::operator++(n);
		}
		RevBidirectionalIterator&	operator--() {
			Base::operator++();
			return *this;
		}
		node_pointer	getnext() {
			return this->ptr->next;
		}
		node_pointer	getprev() {
			return this->ptr->prev;
		}
	};
	// template < typename T, typename pointer, typename reference, typename N, class Category = std::bidirectional_iterator_tag >
	// class ConstRevBidirectionalIterator : public RevBidirectionalIterator<T, pointer, reference, N> {
	// public:
	// 	typedef RevBidirectionalIterator<T, pointer, reference, N>		Base;
	// 	using typename Base::value_type;
	// 	using typename Base::reference;
	// 	using typename Base::const_reference;
	// 	using typename Base::pointer;
	// 	using typename Base::const_pointer;
	// 	using typename Base::node_pointer;
	// 	using typename Base::size_type;
	// 	using typename Base::difference_type;
	// 	typedef ConstRevBidirectionalIterator	self_type;
	// 	typedef Category							iterator_category;

	// 	ConstRevBidirectionalIterator() : Base() {
	// 	}
	// 	ConstRevBidirectionalIterator(node_pointer element) : Base(element) {
	// 	}
	// 	ConstRevBidirectionalIterator(const self_type& other) : Base() {
	// 		*this = other;
	// 	}
	// 	ConstRevBidirectionalIterator(const Base& other) : Base() {
	// 		*this = other;
	// 	}
	// 	self_type&	operator=(const self_type& x) {
	// 		Base::operator=(x);
	// 		return *this;
	// 	}
	// 	self_type&	operator=(const Base& x) {
	// 		Base::operator=(x);
	// 		return *this;
	// 	}
	// 	virtual ~ConstRevBidirectionalIterator() { }
	// 	const_reference	operator*() {
	// 		return (this->ptr->data);
	// 	}
	// 	const_pointer		operator->() {
	// 		return (&(this->ptr->data));
	// 	}
	// };
}

#endif
