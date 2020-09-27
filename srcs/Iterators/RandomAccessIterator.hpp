/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RandomAccessIterator.hpp                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 12:20:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/09/27 15:07:52 by peerdb        ########   odam.nl         */
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

	template < typename T, class Category = random_access_iterator_tag >
	class RandomAccessIterator;
	template < typename T, class Category = random_access_iterator_tag >
	class ConstRandomAccessIterator;
	template < typename T, class Category = random_access_iterator_tag >
	class RevRandomAccessIterator;
	template < typename T, class Category = random_access_iterator_tag >
	class ConstRevRandomAccessIterator;

	template < typename T, class Category >
	class RandomAccessIterator {
	public:
		typedef T							value_type;
		typedef T&							reference;
		typedef T*							pointer;
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
			if (this != &other)
				this->array = other.array;
			return *this;
		}
		~RandomAccessIterator() {}

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
		pointer		operator->() {
			return *(&(this->array));
		}
		bool	operator==(const RandomAccessIterator& rhs) const {
			return (this->array == rhs.array);
		}
		bool	operator==(const ConstRandomAccessIterator<T>& rhs) const {
			return (this->array == rhs.data());
		}
		bool	operator!=(const RandomAccessIterator& rhs) const {
			return (this->array != rhs.array);
		}
		bool	operator!=(const ConstRandomAccessIterator<T>& rhs) const {
			return (this->array != rhs.data());
		}
		bool	operator<(const RandomAccessIterator& rhs) const {
			return (this->array < rhs.array);
		}
		bool	operator<(const ConstRandomAccessIterator<T>& rhs) const {
			return (this->array < rhs.data());
		}
		bool	operator<=(const RandomAccessIterator& rhs) const {
			return (this->array <= rhs.array);
		}
		bool	operator<=(const ConstRandomAccessIterator<T>& rhs) const {
			return (this->array <= rhs.data());
		}
		bool	operator>(const RandomAccessIterator& rhs) const {
			return (this->array > rhs.array);
		}
		bool	operator>(const ConstRandomAccessIterator<T>& rhs) const {
			return (this->array > rhs.data());
		}
		bool	operator>=(const RandomAccessIterator& rhs) const {
			return (this->array >= rhs.array);
		}
		bool	operator>=(const ConstRandomAccessIterator<T>& rhs) const {
			return (this->array >= rhs.data());
		}
		reference	operator[](difference_type n) const {
			return (*(this->array + n));
		}
		pointer		data() const {
			return this->array;
		}
	private:
		pointer	array;
	};
	template < typename T, class Category >
	class ConstRandomAccessIterator {
	public:
		typedef const T							value_type;
		typedef const T&					reference;
		typedef const T*					pointer;
		typedef size_t						size_type;
		typedef ptrdiff_t					difference_type;
		typedef random_access_iterator_tag	iterator_category;
		typedef	ConstRandomAccessIterator	self_type;

		ConstRandomAccessIterator() : array(0) { }
		ConstRandomAccessIterator(pointer elem) : array(elem) {}
		ConstRandomAccessIterator(const ConstRandomAccessIterator& other) {
			*this = other;
		}
		ConstRandomAccessIterator(const RandomAccessIterator<T> &other) {
			*this = other;
		}
		ConstRandomAccessIterator&	operator=(const ConstRandomAccessIterator& other) {
			this->array = other.array;
			return *this;
		}
		ConstRandomAccessIterator&	operator=(const RandomAccessIterator<T>& other) {
			this->array = other.data();
			return *this;
		}
		~ConstRandomAccessIterator() { }

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
		pointer		operator->() {
			return *(&(this->array));
		}
		bool	operator==(const ConstRandomAccessIterator& rhs) const {
			return (this->array == rhs.array);
		}
		bool	operator==(const RandomAccessIterator<T>& rhs) const {
			return (this->array == rhs.data());
		}
		bool	operator!=(const ConstRandomAccessIterator& rhs) const {
			return (this->array != rhs.array);
		}
		bool	operator!=(const RandomAccessIterator<T>& rhs) const {
			return (this->array != rhs.data());
		}
		bool	operator<(const ConstRandomAccessIterator& rhs) const {
			return (this->array < rhs.array);
		}
		bool	operator<(const RandomAccessIterator<T>& rhs) const {
			return (this->array < rhs.data());
		}
		bool	operator<=(const ConstRandomAccessIterator& rhs) const {
			return (this->array <= rhs.array);
		}
		bool	operator<=(const RandomAccessIterator<T>& rhs) const {
			return (this->array <= rhs.data());
		}
		bool	operator>(const ConstRandomAccessIterator& rhs) const {
			return (this->array > rhs.array);
		}
		bool	operator>(const RandomAccessIterator<T>& rhs) const {
			return (this->array > rhs.data());
		}
		bool	operator>=(const ConstRandomAccessIterator& rhs) const {
			return (this->array >= rhs.array);
		}
		bool	operator>=(const RandomAccessIterator<T>& rhs) const {
			return (this->array >= rhs.data());
		}
		reference	operator[](difference_type n) const {
			return (*(this->array + n));
		}
		pointer		data() const {
			return this->array;
		}
	private:
		pointer	array;
	};

	template < typename T, class Category >
	class RevRandomAccessIterator{
	public:
		typedef T							value_type;
		typedef T&							reference;
		typedef T*							pointer;
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
		bool	operator==(const RevRandomAccessIterator& rhs) const {
			return (this->array == rhs.array);
		}
		bool	operator==(const ConstRevRandomAccessIterator<T>& rhs) const {
			return (this->array == rhs.data());
		}
		bool	operator!=(const RevRandomAccessIterator& rhs) const {
			return (this->array != rhs.array);
		}
		bool	operator!=(const ConstRevRandomAccessIterator<T>& rhs) const {
			return (this->array != rhs.data());
		}
		bool	operator<(const RevRandomAccessIterator& rhs) const {
			return (this->array >= rhs.array);
		}
		bool	operator<(const ConstRevRandomAccessIterator<T>& rhs) const {
			return (this->array >= rhs.data());
		}
		bool	operator<=(const RevRandomAccessIterator& rhs) const {
			return (this->array > rhs.array);
		}
		bool	operator<=(const ConstRevRandomAccessIterator<T>& rhs) const {
			return (this->array > rhs.data());
		}
		bool	operator>(const RevRandomAccessIterator& rhs) const {
			return (this->array <= rhs.array);
		}
		bool	operator>(const ConstRevRandomAccessIterator<T>& rhs) const {
			return (this->array <= rhs.data());
		}
		bool	operator>=(const RevRandomAccessIterator& rhs) const {
			return (this->array < rhs.array);
		}
		bool	operator>=(const ConstRevRandomAccessIterator<T>& rhs) const {
			return (this->array < rhs.data());
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
	template < typename T, class Category >
	class ConstRevRandomAccessIterator {
	public:
		typedef const T							value_type;
		typedef const T&						reference;
		typedef const T*						pointer;
		typedef size_t							size_type;
		typedef ptrdiff_t						difference_type;
		typedef random_access_iterator_tag		iterator_category;
		typedef	ConstRevRandomAccessIterator	self_type;

		ConstRevRandomAccessIterator() : array(0) { }
		ConstRevRandomAccessIterator(pointer elem) : array(elem) {}
		ConstRevRandomAccessIterator(const ConstRevRandomAccessIterator& other) {
			*this = other;
		}
		ConstRevRandomAccessIterator(const RevRandomAccessIterator<T> &other) {
			*this = other;
		}
		ConstRevRandomAccessIterator&	operator=(const ConstRevRandomAccessIterator& other) {
			this->array = other.array;
			return *this;
		}
		ConstRevRandomAccessIterator&	operator=(const RevRandomAccessIterator<T>& other) {
			this->array = other.data();
			return *this;
		}
		~ConstRevRandomAccessIterator() { }

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
		bool	operator==(const ConstRevRandomAccessIterator& rhs) const {
			return (this->array == rhs.array);
		}
		bool	operator==(const RevRandomAccessIterator<T>& rhs) const {
			return (this->array == rhs.data());
		}
		bool	operator!=(const ConstRevRandomAccessIterator& rhs) const {
			return (this->array != rhs.array);
		}
		bool	operator!=(const RevRandomAccessIterator<T>& rhs) const {
			return (this->array != rhs.data());
		}
		bool	operator<(const ConstRevRandomAccessIterator& rhs) const {
			return (this->array >= rhs.array);
		}
		bool	operator<(const RevRandomAccessIterator<T>& rhs) const {
			return (this->array >= rhs.data());
		}
		bool	operator<=(const ConstRevRandomAccessIterator& rhs) const {
			return (this->array > rhs.array);
		}
		bool	operator<=(const RevRandomAccessIterator<T>& rhs) const {
			return (this->array > rhs.data());
		}
		bool	operator>(const ConstRevRandomAccessIterator& rhs) const {
			return (this->array <= rhs.array);
		}
		bool	operator>(const RevRandomAccessIterator<T>& rhs) const {
			return (this->array <= rhs.data());
		}
		bool	operator>=(const ConstRevRandomAccessIterator& rhs) const {
			return (this->array < rhs.array);
		}
		bool	operator>=(const RevRandomAccessIterator<T>& rhs) const {
			return (this->array < rhs.data());
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
