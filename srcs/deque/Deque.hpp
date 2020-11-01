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
# include "Colours.h"
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
			typedef DequeIterator<T, ARRAY_SIZE>				iterator;
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
			size_type		_size;		// amount of elements in the deque
			size_type		_start;		// offset to the start of the elements
			size_type		_num_nodes;
			size_type		_capacity;	// amount of possible elements in the entire deque
			map_pointer 	_map;		// pointer to the array of chunks
			size_type		_map_size;	// amount of sub-arrays
			allocator_type	_alloc;
			iterator		start;		// iterator to the start
			iterator		finish;		// iterator to the past-the-end element

		public:

		/* Constructors, Destructors and assignment operator */
			explicit	deque(const allocator_type& alloc = allocator_type())
				: _size(0), _start(0), _num_nodes(0), _capacity(0), _map(0), _map_size(0), _alloc(alloc) {
				start();
				finish();
//				fill_initialize(2 * ARRAY_SIZE, value_type());
			}
			explicit	deque(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: _size(0), _start(0), _num_nodes(0), _capacity(0), _map(0), _map_size(0), _alloc(alloc), start(), finish() {
				this->assign(n, val);
			}
//			template<class InputIterator>
//			deque(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			deque(const deque& x) : _size(0), _start(0), _num_nodes(0), _capacity(0), _map(0), _map_size(0), _alloc(x.alloc), start(), finish() {
				*this = x;
			}
			virtual ~deque() {
				for (size_type i = 0; i < this->_map_size; ++i) {
					delete[] this->_map[i];
				}
				this->_size = 0;
				delete[] this->_map;
				std::cerr << "end of ~deque( )\n";
			}
			deque&	operator=(const deque& x) {
				if (this != &x) {
					this->assign(x.begin(), x.end());
				}
			}

		/* Iterator functions */
//			iterator begin() { return iterator(this->_map + this->_start); }
			iterator begin() { return start; }
//			iterator end() { return iterator(this->_map + this->_start + this->_size); }
			iterator end() { return finish; }

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
			reference		operator[](size_type n) { //random access, use __deque_iterator operator[]
				return start[n];
//				return *this->_map[this->_start + n];
			}
			const_reference	operator[](size_type n) const {
				return start[n];
//				return *this->_map[this->_start + n];
			}
			reference		at(size_type n) {
				if (n >= this->_size)
					throw std::out_of_range("Deque index out of range");
				return start[n];
			}
			const_reference		at(size_type n) const {
				if (n >= this->_size)
					throw std::out_of_range("Deque index out of range");
				return start[n];
			}
//			reference front() { return this->operator[](0); }
			reference front() { return *start; }
//			const_reference front() const { return this->operator[](0); }
//			reference back() { return this->operator[](this->_size - 1); }
			reference back() {
				iterator tmp = finish;
				--tmp;
				return *tmp; // return finish's *cur
			}
//			const_reference back() const { return this->operator[](this->_size - 1); }

		/* Modifier functions */
			void	reserve(const size_type& num_elements, const size_type& nodes_needed) {
				if (nodes_needed > this->_map_size) {
					size_type oldmapsize = this->_map_size;
					size_type oldoffset = this->_start;
					size_type oldnumnodes = this->_num_nodes;
					this->_num_nodes = nodes_needed;
					this->_map_size = std::max((size_t)8, this->_num_nodes + 2);

					// allocate a new map pointer
					map_pointer	tmp_map = new pointer[this->_map_size]();
					this->_start = (this->_map_size - this->_num_nodes) / 2;
					map_pointer tmp_start = tmp_map + this->_start;
					map_pointer tmp_finish = tmp_start + this->_num_nodes - 1;

					if (oldmapsize) {
						map_pointer oldc = this->_map + oldoffset;
						map_pointer oldfinish = this->_map + oldoffset + oldnumnodes - 1;
						for (map_pointer c = tmp_start; oldc <= oldfinish; ++c) {
							*c = *oldc;
//							std::cerr << "copied [" << *c << "] over in new array.\n";
							++oldc;
						}
					}
					else  {
						for (map_pointer c = tmp_start; c <= tmp_finish; ++c) {
							*c = new value_type [ARRAY_SIZE]();
//							std::cerr << _PURPLE << "new subarray at " << *c << std::endl << _END;
						}
					}
					// set start and end iterator
					start.set_node(tmp_start);
					start.cur = start.first;

					finish.set_node(tmp_finish);
					finish.cur = finish.first + (num_elements % ARRAY_SIZE);
					delete this->_map;
					this->_map = tmp_map;
					for (size_t i = 0; i < this->_map_size; ++i) {
						std::cerr << _CYAN << "ptr at tmp_map[" << i << "] is: " <<this->_map[i] << std::endl << _END;
					}
				}
			}
//			template <class InputIterator>
//			void	assign(InputIterator first, InputIterator last);
			void	assign(size_type n, const value_type& val) {
				this->clear();
				this->reserve(n, n / ARRAY_SIZE + 1);

				for (iterator it = start; it != finish; ++it) {
					*it = val;
				}
				this->_size = n;
			}
			void	push_back(const value_type& val) {
//				std::cerr << "starting push_back( val )" << std::endl;
				if (finish.last - finish.cur == 1 ) { // We need a new array at the back
					std::cerr << "its time to push back a new array. _start + _num_nodes = " << _start + _num_nodes << std::endl;
					if (this->_start + this->_num_nodes == _map_size) {
						std::cerr << "we need to realloc our parent array\n";
						this->reserve(_size, _map_size);
					}
					*(this->_map + this->_start + this->_num_nodes) = new value_type [ARRAY_SIZE]();
					++this->_num_nodes;
//					for (size_t i = 0; i < this->_map_size; ++i) {
//						std::cerr << _CYAN << "ptr at tmp_map[" << i << "] is: " <<this->_map[i] << std::endl << _END;
//					}
				}
				*finish = val;
				++finish;
				++this->_size;
			}
			void	push_front(const value_type& val) {
				if (start.cur == start.first) { // we need a new array at the front
					if (this->_start == 0)
						this->reserve(_size, _map_size);
					*(this->_map + this->_start - 1) = new value_type [ARRAY_SIZE]();
					++this->_num_nodes;
					for (size_t i = 0; i < this->_map_size; ++i) {
						std::cerr << _CYAN << "ptr at tmp_map[" << i << "] is: " <<this->_map[i] << std::endl << _END;
					}
				}
				--start;
				--this->_start;
//				std::cerr << "decremented start, start.first: " << start.first << ", .cur: " << start.cur << ", .last: " << start.last << std::endl;
				*start = val;
				++this->_size;
			}
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
				for (size_type i = 0; i < this->_map_size; ++i) {
//					std::cerr << "trying to delete subarray _map["<<i<<"] at " << _map[i] << std::endl;
					delete[] this->_map[i];
//					this->_map[i] = 0;
				}
				this->_size = 0;
				this->_num_nodes = 0;
				this->_capacity = 0;
//				std::cerr << "trying to delete map at " << _map << std::endl;
				delete[] this->_map;
				this->_map = 0;
				this->_start = 0;
				this->_map_size = 0;
			}

		private:

	};

} // ft namespace

#endif
