/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RandomAccessIterator.hpp                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 12:20:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/11/03 23:45:16 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP

# include <memory>
# include <cstddef>

namespace ft {

	template < typename T, typename Pointer, typename Reference, class Category = std::random_access_iterator_tag >
	class RandomAccessIterator {
	public:
		typedef RandomAccessIterator<T, Pointer, Reference>	this_type;
		typedef RandomAccessIterator<T, T*, T&>				iterator;
		typedef RandomAccessIterator<T, const T*, const T&>	const_iterator;
		typedef T				value_type;
		typedef Pointer			pointer;
		typedef Reference		reference;
		typedef size_t			size_type;
		typedef ptrdiff_t		difference_type;
		typedef	Category		iterator_category;
		template <class T2, class A>					friend class vector;
		template <class T2, class P, class R, class C>	friend class RandomAccessIterator;
	protected:
		pointer	array;
	public:

		RandomAccessIterator() : array(NULL) {}
		RandomAccessIterator(const pointer elem) : array(elem) {}
		RandomAccessIterator(const iterator& x) : array(const_cast<pointer>(x.array)) { }
		virtual ~RandomAccessIterator() {}

		this_type&	operator=(const iterator& x) {
			this->array = x.array;
			return *this;
		}

		this_type	operator++(int) {
			this_type out(*this);
			++this->array;
			return out;
		}
		this_type&	operator++() {
			this->array++;
			return *this;
		}
		this_type	operator+(difference_type n) const {
			this_type out(*this);
			out.array += n;
			return out;
		}
		this_type&	operator+=(difference_type n) {
			this->array += n;
			return *this;
		}
		this_type	operator--(int) {
			this_type out(*this);
			--this->array;
			return out;
		}
		this_type&	operator--() {
			--this->array;
			return *this;
		}
		difference_type	operator-(RandomAccessIterator it) const {
			return this->array - it.array;
		}
		this_type	operator-(difference_type n) const {
			this_type out(*this);
			out -= n;
			return out;
		}
		this_type&	operator-=(difference_type n) {
			this->array -= n;
			return *this;
		}
		reference	operator*() {
			return *this->array;
		}
		pointer		operator->() {
			return *(&(this->array));
		}
		bool	operator==(const const_iterator& rhs) const {
			return (this->array == rhs.array);
		}
		bool	operator!=(const const_iterator& rhs) const {
			return (this->array != rhs.array);
		}
		bool	operator<(const const_iterator& rhs) const {
			return (this->array < rhs.array);
		}
		bool	operator<=(const const_iterator& rhs) const {
			return (this->array <= rhs.array);
		}
		bool	operator>(const const_iterator& rhs) const {
			return (this->array > rhs.array);
		}
		bool	operator>=(const const_iterator& rhs) const {
			return (this->array >= rhs.array);
		}
		reference	operator[](difference_type n) {
			return (*(this->array + n));
		}
		pointer		data() const {
			return this->array;
		}
	};

}

#endif
