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
#  define ARRAY_SIZE 16
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
			iterator		start;
			iterator		finish;
			size_type		_capacity;
			size_type		_size;
			map_pointer 	map;		// pointer to the array of chunks
			size_type		map_size;	// amount of chunks
			allocator_type	_alloc;

		public:

		/* Constructors, Destructors and assignment operator */
			explicit	deque(const allocator_type& alloc = allocator_type())
				: start(0), finish(0), _capacity(0), _size(0), map(0), _alloc(alloc) {
//				fill_initialize(2 * ARRAY_SIZE, value_type());
			}
			explicit	deque(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: start(0), finish(0), _capacity(0), _size(0), map(0), _alloc(alloc) {
				this->assign(n, val);
			}
//			template<class InputIterator>
//			deque(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			deque(const deque& x);
			virtual ~deque() {
				for (map_pointer cur = start.node; cur <= finish.node; ++cur)
					delete *cur;
				delete map;
			}
			deque&	operator=(const deque& x);

		/* Iterator functions */
			iterator begin() { return start; }
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
					if (n >= ARRAY_SIZE * map_size)
					while (n > this->_size)
						push_back(val);
				}
			}
			bool		empty() const { return (this->_size == 0); }

		/* Element access functions */
			reference operator[](size_type n) { //random access, use __deque_iterator operator[]
				return start[n];
			}
			const_reference	operator[](size_type n) const {
				return start[n];
			}
			reference front() { return *start; }
			reference back() {
				iterator tmp = finish; // cant use *finish
				--tmp;
				return *tmp; // return finish's *cur
			}

		/* Modifier functions */
//			template <class InputIterator>
//			void	assign(InputIterator first, InputIterator last);
			void	assign(size_type n, const value_type& val) {
				create_map_and_nodes(n); // allocate memory for map and chunk and initialize pointer

				for (map_pointer cur = start.node; cur < finish.node; ++cur) // initialize value for the chunks
					initialized_fill_n(*cur, ARRAY_SIZE, val);
				// the end chunk may have space node, which don't need to have initialized value
				initialized_fill_n(finish.first, finish.cur - finish.first, val);
			}

			void	push_back(const value_type& val) {

			}
			void	push_front(const value_type& val);
			void	pop_back(void) {
//				start[this->_size] = value_type();
				--this->_size;
			}
			void	pop_front(void);

			iterator	insert(iterator position, const value_type& val); // single element insert
			void		insert(iterator position, size_type n, const value_type& val); // fill insert
//			template <class InputIterator>
//			void		insert(iterator position, InputIterator first, InputIterator last); // range insert

			iterator	erase(iterator position);
			iterator	erase(iterator first, iterator last);
			void		swap(deque& x); // iterators, references and pointers MUST remain valid
			void		clear() {
				for (map_pointer cur = start.node; cur <= finish.node; ++cur)
					delete *cur;
				delete map;
			}

		private:
			void	initialized_fill_n(pointer ccur, size_type n, value_type val) {
				for (size_type i = 0; i < n; i++) {
					ccur[i] = val;
				}
			}

			void	create_map_and_nodes(size_t num_elements) {
				// the needed map node = (elements nums / chunk length) + 1
				size_type num_nodes = num_elements / ARRAY_SIZE + 1;
				// map node num. min num is 8, max num is "needed size + 2"
				map_size = std::max((size_t)8, num_nodes + 2);
				std::cerr << "map_size = " << map_size << ", num_nodes = " << num_nodes << std::endl;
				// allocate map array
				map = new pointer[map_size]();

				// tmp_start, tmp_finish pointers to the center range of map
				map_pointer tmp_start = map + (map_size - num_nodes) / 2;
				map_pointer tmp_finish = tmp_start + num_nodes - 1;

				// allocate memory for the chunk pointered by map node
				for (map_pointer cur = tmp_start; cur <= tmp_finish; ++cur)
					*cur = new value_type[ARRAY_SIZE]();

				// set start and end iterator
				start.set_node(tmp_start);
				start.cur = start.first;

				finish.set_node(tmp_finish);
				finish.cur = finish.first + num_elements % ARRAY_SIZE;
			}
	};

} // ft namespace

#endif
