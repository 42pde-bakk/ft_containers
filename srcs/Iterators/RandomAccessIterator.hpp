/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RandomAccessIterator.hpp                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 12:20:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/07 22:54:24 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP

# include <limits>
# include <memory>
# include <iostream>
# include <cstddef>
# include <cstring>
# include "../Traits.hpp"

namespace ft {

	template < typename T, class Category = std::random_access_iterator_tag >
	class RandomAccessIterator {
	public:
		typedef T							value_type;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef value_type*					pointer;
		typedef const value_type*			const_pointer;
		typedef size_t						size_type;
		typedef ptrdiff_t					difference_type;
		typedef random_access_iterator_tag	iterator_category;
		typedef RandomAccessIterator 		self_type;

		RandomAccessIterator() : array(0) { }
		RandomAccessIterator(pointer elem) : array(elem) {}
		RandomAccessIterator(const RandomAccessIterator& other) {
			*this = other;
		}
		RandomAccessIterator&	operator=(const RandomAccessIterator& other) {
			this->array = other.array;
			return *this;
		}
		virtual ~RandomAccessIterator() {}

		self_type	operator++(int) {
			self_type out(*this);
			this->array++;
			return out;
		}
		self_type&	operator++() {
			this->array++;
			return *this;
		}
		self_type	operator+(difference_type n) {
			self_type out(*this);
			out.array += n;
			return out;
		}
		self_type	operator+=(difference_type n) {
			this->array += n;
			return *this;
		}
		self_type	operator--(int) {
			self_type out(*this);
			this->array--;
			return out;
		}
		self_type&	operator--() {
			this->array--;
			return *this;
		}
		self_type	operator-(difference_type n) {
			self_type out(*this);
			out -= n;
			return out;
		}
		self_type	operator-=(difference_type n) {
			this->array -= n;
			return *this;
		}
		reference	operator*() {
			return *this->array;
		}
		// const_reference operator*() const {
		// 	return *this->array;
		// }
		pointer		operator->() {
			return *(&(this->array));
		}
		// const_pointer		operator->() const {
		// 	return *(&(this->array));
		// }
		bool	operator==(const RandomAccessIterator& rhs) const {
			return (this->array == rhs.array);
		}
		bool	operator!=(const RandomAccessIterator& rhs) const {
			return (this->array != rhs.array);
		}
		bool	operator<(const RandomAccessIterator& rhs) const {
			return (this->array < rhs.array);
		}
		bool	operator<=(const RandomAccessIterator& rhs) const {
			return (this->array <= rhs.array);
		}
		bool	operator>(const RandomAccessIterator& rhs) const {
			return (this->array > rhs.array);
		}
		bool	operator>=(const RandomAccessIterator& rhs) const {
			return (this->array >= rhs.array);
		}
		reference	operator[](difference_type n) const {
			return (*(this->array + n));
		}
		pointer		data() const {
			return this->array;
		}
	protected:
		pointer	array;
	};
	template < typename T, class Category = std::random_access_iterator_tag >
	class ConstRandomAccessIterator : public RandomAccessIterator<T> {
	public:
		typedef T							value_type;
		typedef value_type&					reference;
		// typedef const value_type&			const_reference;
		typedef value_type*					pointer;
		// typedef const value_type*			const_pointer;
		typedef size_t						size_type;
		typedef ptrdiff_t					difference_type;
		typedef random_access_iterator_tag	iterator_category;
		typedef ConstRandomAccessIterator 	self_type;

		ConstRandomAccessIterator() : array(0) { }
		ConstRandomAccessIterator(pointer elem) : array(elem) {}
		// ConstRandomAccessIterator(const RandomAccessIterator<T>& other) {
		// 	*this = other;
		// }
		ConstRandomAccessIterator(const ConstRandomAccessIterator& other) {
			*this = other;
		}
		self_type&	operator=(const ConstRandomAccessIterator& other) {
			this->array = other.array;
			return *this;
		}
		// self_type&	operator=(const RandomAccessIterator<T>& other) {
		// 	if (this != &other)
		// 		this->array = other.data();
		// 	return *this;
		// }
		virtual ~ConstRandomAccessIterator() {}		
	
		const value_type&		operator*() {
			return *this->array;
		}
		// const pointer		operator->() const {
		// 	return *(&(this->array));
		// }
		const value_type&		operator[](int n) const {
			return (*(this + n));
		}
	};

	template < typename T, class Category = std::random_access_iterator_tag >
	class RevRandomAccessIterator{
	public:
		typedef T							value_type;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef value_type*					pointer;
		typedef const value_type*			const_pointer;
		typedef size_t						size_type;
		typedef ptrdiff_t					difference_type;
		typedef random_access_iterator_tag	iterator_category;
		typedef RevRandomAccessIterator 	self_type;

		RevRandomAccessIterator() : array(0) { }
		RevRandomAccessIterator(pointer elem) : array(elem) {}
		RevRandomAccessIterator(const RevRandomAccessIterator& other) {
			*this = other;
		}
		RevRandomAccessIterator&	operator=(const RevRandomAccessIterator& other) {
			if (this != &other)
				this->array = other.array;
			return *this;
		}
		~RevRandomAccessIterator() {}

		self_type	operator++(int) {
			self_type out(*this);
			this->array--;
			return out;
		}
		self_type&	operator++() {
			this->array--;
			return *this;
		}
		self_type	operator+(difference_type n) {
			self_type out(*this);
			out.array -= n;
			return out;
		}
		self_type	operator+=(difference_type n) {
			this->array -= n;
			return *this;
		}
		self_type	operator--(int) {
			self_type out(*this);
			this->array++;
			return out;
		}
		self_type&	operator--() {
			this->array++;
			return *this;
		}
		self_type	operator-(difference_type n) {
			self_type out(*this);
			this += n;
			return out;
		}
		self_type	operator-=(difference_type n) {
			this->array += n;
			return *this;
		}
		reference	operator*() {
			return *this->array;
		}
		pointer		operator->() {
			return *(&(this->array));
		}
		const_reference	operator*() const {
			return *this->array;
		}
		const_pointer		operator->() const {
			return *(&(this->array));
		}
		bool	operator==(const RevRandomAccessIterator& rhs) const {
			return (this->array == rhs.array);
		}
		bool	operator!=(const RevRandomAccessIterator& rhs) const {
			return (this->array != rhs.array);
		}
		bool	operator<(const RevRandomAccessIterator& rhs) const {
			return (this->array >= rhs.array);
		}
		bool	operator<=(const RevRandomAccessIterator& rhs) const {
			return (this->array > rhs.array);
		}
		bool	operator>(const RevRandomAccessIterator& rhs) const {
			return (this->array <= rhs.array);
		}
		bool	operator>=(const RevRandomAccessIterator& rhs) const {
			return (this->array < rhs.array);
		}
		reference	operator[](difference_type n) const {
			return (*(this->array - n));
		}
		pointer		data() const {
			return this->array;
		}
	private:
		pointer	array;
	};
}

#endif
