/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Deque.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 18:22:37 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/10/25 18:22:37 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_HPP
# define DEQUE_HPP

# include <memory>
# include <cstddef>
# include "RandomAccessIterator.hpp"
# include "DequeIterator.hpp"
# include "Traits.hpp"
# include "Extra.hpp"
# include <iostream>
# include <algorithm>
# include "../vector/Vector.hpp"
# ifndef ARRAY_SIZE
#  define ARRAY_SIZE 8
# endif

namespace ft {

	template < class T, class Alloc = std::allocator<T> >
	class deque {
		public:
			typedef T				value_type;
			typedef Alloc			allocator_type;
			typedef T&				reference;
			typedef const T&		const_reference;
			typedef T*				pointer;
			typedef const T*		const_pointer;
			typedef DequeIterator<T>				iterator;
//			typedef ConstRandomAccessIterator<T>		const_iterator;
//			typedef RevRandomAccessIterator<T>			reverse_iterator;
//			typedef ConstRevRandomAccessIterator<T>		const_reverse_iterator;
			typedef ptrdiff_t		difference_type;
			typedef	size_t			size_type;
		protected:
			typedef pointer*					map_pointer;
			// Allocate memory for the chunk
			typedef std::allocator<value_type>	dataAllocator;
			// Allocate memory for map
			typedef std::allocator<pointer>		mapAllocator;
		private:
//			iterator		start;
//			iterator		finish;
			size_type		_size;
			size_type		_start;
			size_type		_capacity;
			map_pointer 	_map;		// pointer to the array of chunks
			allocator_type	_alloc;

		public:

		/* Constructors, Destructors and assignment operator */
			explicit	deque(const allocator_type& alloc = allocator_type())
				: _size(0), _start(0), _capacity(0), _map(0), _alloc(alloc) {
//				fill_initialize(2 * ARRAY_SIZE, value_type());
			}
			explicit	deque(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: _size(0), _start(0), _capacity(0), _map(0), _alloc(alloc) {
				this->assign(n, val);
			}
//			template<class InputIterator>
//			deque(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			deque(const deque& x);
			virtual ~deque() {
				for (size_type i = 0; i < this->_size; ++i)
					delete	this->_map[this->_start + i];
				this->_size = 0;
			}
			deque&	operator=(const deque& x);

		/* Iterator functions */
			iterator begin() { return iterator(this->_map + this->_start); }
			iterator end() { return iterator(this->_map + this->_start + this->_size); }

		/* Capacity functions */
			size_type	size() const { return this->_size; }
			size_type	max_size() const;
			void		resize(size_type n, value_type val = value_type()) {
				if (n < this->_size) {
					while (n < this->_size)
						pop_back();
				}
				else if (n > this->_size) {
					while (n > this->_size)
						push_back(val);
				}
			}
			bool		empty() const { return (this->_size == 0); }

		/* Element access functions */
			reference operator[](size_type n) { //random access, use __deque_iterator operator[]
				return *this->_map[this->_start + n];
			}
			const_reference	operator[](size_type n) const {
				return *this->_map[this->_start + n];
			}
			reference front() { return this->operator[](0); }
			const_reference front() const { return this->operator[](0); }
			reference back() { return this->operator[](this->_size - 1); }
			const_reference back() const { return this->operator[](this->_size - 1); }

		/* Modifier functions */
			void	reserve(size_type cap) {
				if (cap > this->_capacity) {
					size_t	real_cap = ARRAY_SIZE; // TODO: double capacity on every new allocation

					// Allocate an array of chunks
					map_pointer tmp = new pointer[real_cap]();
					// Offset to center the old blocks - 2 center, 1 back, 0 front
					size_type	offset = (real_cap / 2) - (this->_size / 2);
					std::cerr << "real cap: " << real_cap << ", this size: " << this->_size << ", offset = " << offset << std::endl;
					// Move old blocks
					size_t i = offset, j = this->_start;
					while(j < this->_start + this->_size) {
						tmp[i] = this->_map[j];
						i++;
						j++;
					}
					delete this->_map;
					this->_map = tmp;
					this->_capacity = real_cap;
					this->_start = offset;
				}
			}
//			template <class InputIterator>
//			void	assign(InputIterator first, InputIterator last);
			void	assign(size_type n, const value_type& val) {
				this->clear();
				this->reserve(n);

				std::cerr << "before centering, _start = " << _start << std::endl;
				this->_start = (this->_capacity / 2) - ((this->_capacity - n) / 2);
				std::cerr << "And after, _start = " << _start << std::endl;

				while (this->_size < n) {
					std::cerr << "allocating new fixed-size array, start = " << _start << ", _size = " << _size << std::endl;
					this->_map[this->_start + this->_size] = new value_type[this->_capacity];
					(void)val;
					++this->_size;
				}
				std::cerr << "after assign(), size = "<< _size << ", cap = " << this->_capacity << ", _start = " << _start << std::endl;
			}

			void	push_back(const value_type& val);
			void	push_front(const value_type& val);
			void	pop_back(void);
			void	pop_front(void);

			iterator	insert(iterator position, const value_type& val); // single element insert
			void		insert(iterator position, size_type n, const value_type& val); // fill insert
//			template <class InputIterator>
//			void		insert(iterator position, InputIterator first, InputIterator last); // range insert

			iterator	erase(iterator position);
			iterator	erase(iterator first, iterator last);
			void		swap(deque& x); // iterators, references and pointers MUST remain valid
			void		clear() {
				for (size_type i = 0; i < this->_size; ++i)
					delete	this->_map[this->_start + i];
				this->_size = 0;
				this->_start = this->_capacity / 2;
			}

		private:

	};

} // ft namespace

#endif
