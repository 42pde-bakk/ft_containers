/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RandomAccessIterator.hpp                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 12:20:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/09/25 21:39:18 by peerdb        ########   odam.nl         */
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
	private:
		pointer	array;
	public:
		typedef T							value_type;
		typedef T&							reference;
		typedef T*							pointer;
		typedef size_t						size_type;
		typedef arraydiff_t					difference_type;
		typedef random_access_iterator_tag	iterator_category;
		// typedef RandomAccessIterator self_type;

		RandomAccessIterator() : array(0) { }
		RandomAccessIterator(pointer array) : array(array) {}
		RandomAccessIterator(const RandomAccessIterator& other) {
			*this = other;
		}
		RandomAccessIterator&	operator=(const RandomAccessIterator& other) {
			if (this != &other)
				this->array = other.array;
			return *this;
		}
		~RandomAccessIterator() {}

		RandomAccessIterator	operator++(int) {
			RandomAccessIterator out(*this);
			this->array++;
			return out;
		}
		RandomAccessIterator&	operator++() {
			this->array++;
			return *this;
		}
		RandomAccessIterator	operator+(difference_type n) {
			RandomAccessIterator out(*this);
			out.array += n;
			return out;
		}
		RandomAccessIterator	operator+=(difference_type n) {
			this->array += n;
			return *this;
		}
		RandomAccessIterator	operator--(int) {
			RandomAccessIterator out = *this--;
			return *out;
		}
		RandomAccessIterator&	operator--() {
			this->array--;
			return *this;
		}
		RandomAccessIterator	operator-(difference_type n) {
			RandomAccessIterator out = *this - n;
			return *out;
		}
		RandomAccessIterator	operator-=(difference_type n) {
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
			if (this->array == rhs.array)
				return true;
			return false;
		}
		bool	operator!=(const RandomAccessIterator& rhs) const {
			if (this->array == rhs.array) {
				return false;
			}
			return true;
		}
		bool	operator<(const RandomAccessIterator& rhs) const {
			if (this->array < rhs.array)
				return true;
			return false;
		}
		bool	operator<=(const RandomAccessIterator& rhs) const {
			if (this->array <= rhs.array)
				return true;
			return false;
		}
		bool	operator>(const RandomAccessIterator& rhs) const {
			if (this->array > rhs.array)
				return true;
			return false;
		}
		bool	operator>=(const RandomAccessIterator& rhs) const {
			if (this->array >= rhs.array)
				return true;
			return false;
		}
		RandomAccessIterator	operator[](difference_type n) const {
			RandomAccessIterator out = *this + n;
			return out;
		}
	};
	template < typename T, class Category = std::bidirectional_iterator_tag >
	class ConstRandomAccessIterator {
	private:
		node<T>	*array;
	public:
		typedef T			value_type;
		typedef const T&	reference;
		typedef const T*	pointer;
		typedef node<T>*	node_pointer;
		typedef size_t		size_type;
		typedef arraydiff_t	difference_type;
		typedef bidirectional_iterator_tag iterator_category;
		ConstRandomAccessIterator() : array(NULL) { }
		ConstRandomAccessIterator(node_pointer element) : array(element) {}
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
			this->array = other.getarray();
			return *this;
		}
		~ConstRandomAccessIterator() { }

		ConstRandomAccessIterator	operator++(int) {
			if (this->array)
				this->array = this->array->next;
			return *this;
		}
		ConstRandomAccessIterator&	operator++() {
			if (this->array)
				this->array = this->array->next;
			return *this;
		}
		ConstRandomAccessIterator	operator--(int) {
			if (this->array)
				this->array = this->array->prev;
			return *this;
		}
		ConstRandomAccessIterator&	operator--() {
			if (this->array)
				this->array = this->array->prev;
			return *this;
		}
		bool	operator==(const ConstRandomAccessIterator& rhs) const {
			if (this->array == rhs.array)
				return true;
			return false;
		}
		bool	operator!=(const ConstRandomAccessIterator& rhs) const {
			if (this->array == rhs.array)
				return false;
			return true;
		}
		reference	operator*() {
			return (this->array->data);
		}
	};

	template < typename T, class Category = std::bidirectional_iterator_tag >
	class RevRandomAccessIterator{
	private:
		node<T>	*array;
	public:
		typedef T			value_type;
		typedef T&			reference;
		typedef T*			pointer;
		typedef node<T>*	node_pointer;
		typedef size_t		size_type;
		typedef arraydiff_t	difference_type;
		typedef bidirectional_iterator_tag iterator_category;
		// typedef RevRandomAccessIterator self_type;

		RevRandomAccessIterator() : array(NULL) { }
		RevRandomAccessIterator(node_pointer element) : array(element) { }
		RevRandomAccessIterator(const RevRandomAccessIterator& other) {
			*this = other;
		}
		RevRandomAccessIterator&	operator=(const RevRandomAccessIterator& other) {
			if (this != &other)
				this->array = other.array;
			return *this;
		}
		~RevRandomAccessIterator() { }
		RevRandomAccessIterator	operator++(int) {
			if (this->array)
				this->array = this->array->prev;
			return *this;
		}
		RevRandomAccessIterator&	operator++() {
			if (this->array)
				this->array = this->array->prev;
			return *this;
		}
		RevRandomAccessIterator	operator--(int) {
			if (this->array)
				this->array = this->array->next;
			return *this;
		}
		RevRandomAccessIterator&	operator--() {
			if (this->array)
				this->array = this->array->next;
			return *this;
		}
		reference	operator*() {
			return this->array->data;
		}
		pointer		operator->() {
			return (&(this->array->data));
		}
		bool	operator==(const RevRandomAccessIterator& rhs) const {
			if (this->array == rhs.array)
				return true;
			return false;
		}
		bool	operator!=(const RevRandomAccessIterator& rhs) const {
			if (this->array == rhs.array) {
				return false;
			}
			return true;
		}
		node<T>	*getarray() const {
			return this->array;
		}
		node<T>	*getnext() {
			return this->array->next;
		}
		node<T>	*getprev() {
			return this->array->prev;
		}
	};
	template < typename T, class Category = std::bidirectional_iterator_tag >
	class ConstRevRandomAccessIterator {
	private:
		node<T>	*array;
	public:
		typedef T			value_type;
		typedef const T&	reference;
		typedef const T*	pointer;
		typedef node<T>*	node_pointer;
		typedef size_t		size_type;
		typedef arraydiff_t	difference_type;
		typedef bidirectional_iterator_tag iterator_category;
		ConstRevRandomAccessIterator() : array(NULL) { }
		ConstRevRandomAccessIterator(node_pointer element) : array(element) {}
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
		ConstRevRandomAccessIterator&	operator=(const RevRandomAccessIterator<T> &other) {
			this->array = other.getarray();
			return *this;
		}
		~ConstRevRandomAccessIterator() { }

		ConstRevRandomAccessIterator	operator++(int) {
			if (this->array)
				this->array = this->array->prev;
			return *this;
		}
		ConstRevRandomAccessIterator&	operator++() {
			if (this->array)
				this->array = this->array->prev;
			return *this;
		}
		ConstRevRandomAccessIterator	operator--(int) {
			if (this->array)
				this->array = this->array->next;
			return *this;
		}
		ConstRevRandomAccessIterator&	operator--() {
			if (this->array)
				this->array = this->array->next;
			return *this;
		}
		bool	operator==(const ConstRevRandomAccessIterator& rhs) const {
			if (this->array == rhs.array)
				return true;
			return false;
		}
		bool	operator!=(const ConstRevRandomAccessIterator& rhs) const {
			if (this->array == rhs.array)
				return false;
			return true;
		}
		reference	operator*() {
			return (this->array->data);
		}
	};
}

#endif
