/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Vector.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 15:19:02 by peerdb        #+#    #+#                 */
/*   Updated: 2020/09/25 21:10:08 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <limits>
# include <memory>
# include <iostream>
# include <cstddef>
# include <cstring>
# include <climits>
# include "../Iterators/RandomAccessIterator.hpp"

namespace ft {

	template<class T, class Alloc = std::allocator<T> >
	class vector {
	public:
		typedef T		value_type;
		typedef	Alloc	allocator_type;
		// typedef reference	allocator_type::reference;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef RandomAccessIterator<T>					iterator;
		typedef ConstRandomAccessIterator<const T>		const_iterator;
		typedef RevRandomAccessIterator<T> 				reverse_iterator;
		typedef ConstRevRandomAccessIterator<const T>	const_reverse_iterator;
		typedef ptrdiff_t								difference_type;
		typedef size_t									size_type;

		explicit vector (const allocator_type& alloc = allocator_type()) {
			this->array = 0;
			this->size = 0;
			this->capacity = 0;
		}
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
			this->array = new value_type[n];
			this->size = n;
			for (size_type i = 0; i < n; i++)
				this->array[i] = val;
			this->capacity = n;
		}
		~vector() {
			delete[] this->array;
		}

	private:
		pointer		array;
		size_type	size;
		size_type	capacity;
	};
}


#endif
