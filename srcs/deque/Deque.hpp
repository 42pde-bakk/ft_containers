/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Deque.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 18:22:37 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/10/30 22:21:51 by peerdb        ########   odam.nl         */
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
			size_type		_map_size;
			allocator_type	_alloc;

		public:

		/* Constructors, Destructors and assignment operator */
			explicit	deque(const allocator_type& alloc = allocator_type())
				: _size(0), _start(0), _capacity(0), _map(0), _map_size(0), _alloc(alloc) {
//				fill_initialize(2 * ARRAY_SIZE, value_type());
			}
			explicit	deque(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: _size(0), _start(0), _capacity(0), _map(0), _map_size(0), _alloc(alloc) {
				this->assign(n, val);
			}
//			template<class InputIterator>
//			deque(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			deque(const deque& x);
			virtual ~deque() {
				for (size_type i = 0; i < this->_size; ++i)
					delete[] this->_map[this->_start + i];
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
			void	reserve(size_type n) {
				if (n > this->_capacity) {
					
					size_type num_nodes = n / ARRAY_SIZE + 1;

					// double capacity on every new call (i think)
					size_type oldmapsize = this->_map_size;
					this->_map_size = std::max((size_t)8, num_nodes);
					// this->_capacity = cap;

					// allocate a new map pointer
					map_pointer	tmp_map = new pointer[this->_map_size]();

					// Copy the old map* in the new one
					size_type i = 0;
					while (i < oldmapsize) {
						tmp_map[i] = this->_map[i];
						++i;
					}

					// Add an extra empty entry at the end (/beginning)
					while (i < this->_map_size) {
						// std::cerr << "Just added the " << i << ((i <= 1) ? "st" : "rd") << " node.\n";
						tmp_map[i] = new value_type[ARRAY_SIZE]();
						++i;
					}

					// delete old map, set map to be tmp map
					delete this->_map;
					this->_map = tmp_map;
					this->_size = n;
					this->_start = (this->_map_size / 2) - ((this->_map_size - num_nodes) / 2);
				}
			}
//			template <class InputIterator>
//			void	assign(InputIterator first, InputIterator last);
			void	assign(size_type n, const value_type& val) {
				this->clear();
				this->reserve(n);

				// std::cerr << "before centering, _start = " << _start << std::endl;
				// std::cerr << "map size: " << this->_map_size << ", map size - n = " << _map_size - n << ", start = " << ((this->_map_size / 2) - ((this->_map_size - n) / 2)) << std::endl;
				// this->_start = (this->_map_size / 2) - ((this->_map_size - n) / 2);
				// std::cerr << "And after, _start = " << _start << std::endl;
				for (size_type i = 0; i < n; ++i) {
					*this->_map[this->_start + i] = val;
				}
				std::cerr << "after assign(), size = "<< _size << ", map_size = " << this->_map_size << ", _start = " << _start << std::endl;
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
					delete[]	this->_map[this->_start + i];
				this->_size = 0;
				// this->_map_size = 0;
				this->_start = this->_capacity / 2;
			}

		private:

	};

} // ft namespace

#endif
