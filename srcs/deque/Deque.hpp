/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Deque.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 18:22:37 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/11/03 15:53:58 by peerdb        ########   odam.nl         */
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
			size_type		_num_nodes;	// amount of allocated sub arrays
			size_type		_capacity;	// amount of possible elements in the entire deque
			map_pointer 	_map;		// pointer to the array of chunks
			size_type		_map_size;	// amount of sub-arrays (both allocated and nullptrs)
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
			const_reference front() const { return *start; }
//			reference back() { return this->operator[](this->_size - 1); }
			reference back() {
				iterator tmp = finish;
				--tmp;
				return *tmp; // return finish's *cur
			}
			const_reference back() const {
				iterator tmp = finish;
				--tmp;
				return *tmp;
			}

		/* Modifier functions */
//			template <class InputIterator>
//			void	assign(InputIterator first, InputIterator last);
			void	assign(size_type n, const value_type& val) {
				this->clear();
				this->reserve(n, n / ARRAY_SIZE + 1, std::max((size_t)8, (n / ARRAY_SIZE) + 1) );
				finish.cur = finish.first + (n % ARRAY_SIZE);

				for (iterator it = start; it != finish; ++it) {
					*it = val;
				}
				this->_size = n;
			}
			void	push_back(const value_type& val) {
				if (finish.last - finish.cur == 1 ) { // We need a new array at the back
					if (this->_start + this->_num_nodes == _map_size)
						this->reserve(_size, _num_nodes, _map_size + 2);
					iterator  tmp = finish;
					++tmp;
					if (tmp.first == 0) {
						*(this->_map + this->_start + this->_num_nodes) = new value_type [ARRAY_SIZE]();
						++this->_num_nodes;
					}
				}
				*finish = val;
				++finish;
				++this->_size;
			}
			void	push_front(const value_type& val) {
				if (start.cur == start.first) { // we need a new array at the front
					if (this->_start == 0)
						this->reserve(_size, _num_nodes, _map_size + 2);
					iterator tmp = start;
					--tmp;
					if (tmp.first == 0) {
						*(this->_map + this->_start - 1) = new value_type [ARRAY_SIZE]();
						++this->_num_nodes;
					}
				}
				--start;
				--this->_start;
				*start = val;
				++this->_size;
			}
			void	pop_back(void) {
				if (this->_size) {
					--this->finish;
					--this->_size;
				}
			}
			void	pop_front(void) {
				if (this->_size) {
					std::cerr << "popping front\n";
					++this->start;
					if (this->start.cur == this->start.first)
						++this->_start;
					--this->_size;
				}
			}

			iterator	insert(iterator position, const value_type& val) {
				insert(position, 1, val);
				return position;
			}
			void		insert(iterator position, size_type n, const value_type& val) {
				for (size_type i = 0; i < n; ++i)
					push_back(value_type());
				iterator it(finish);
				--it;
				while (it - n >= position) {
					*it = *(it - n);
					--it;					
				}
				for (size_type i = 0; i < n; i++) {
					*position = val;
					++position;
				}
			}
			template <class InputIterator>
			void		insert(iterator position, InputIterator first, InputIterator last, typename enable_if<is_iterator<typename InputIterator::iterator_category>::value, InputIterator>::type * = 0) {
				while (first != last) {
					--last;
					insert(last, 1, *last);
				}
			}

			iterator	erase(iterator position);
			iterator	erase(iterator first, iterator last);
			void		swap(deque& x); // iterators, references and pointers MUST remain valid
			void		clear() {
				for (size_type i = 0; i < this->_map_size; ++i) {
					delete[] this->_map[i];
				}
				this->_size = 0;
				this->_num_nodes = 0;
				this->_capacity = 0;
				delete[] this->_map;
				this->_map = 0;
				this->_start = 0;
				this->_map_size = 0;
			}
private:
			void	reserve(const size_type& num_elements, const size_type& num_nodes, const size_type& wantedmapsize) {
				if (wantedmapsize > this->_map_size) {
					std::cerr << "reserving for " << num_nodes << std::endl;
					size_type oldmapsize = this->_map_size;		// making backups
					size_type oldoffset = this->_start;
					size_type oldnumnodes = this->_num_nodes;
					this->_num_nodes = num_nodes;
					this->_map_size = wantedmapsize;

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
					size_type diff = start.cur - start.first;
					start.set_node(tmp_start);
					start.cur = start.first;
					while (diff > 0) {
						++start.cur;
						--diff;
					}
					finish = start + num_elements;
					delete this->_map;
					this->_map = tmp_map;
//					for (size_t i = 0; i < this->_map_size; ++i) {
//						std::cerr << _CYAN << "ptr at tmp_map[" << i << "] is: " << this->_map[i] << std::endl << _END;
//					}
				}
			}

	};

	
} // ft namespace

#endif
