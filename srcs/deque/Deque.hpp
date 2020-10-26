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

	template<typename T>
	class	chunk {
	public:
		explicit chunk(size_t cap = ARRAY_SIZE) : _size(0), _capacity(cap) {
			_vec = ft::vector<T>();
			_vec.reserve(this->_capacity);
		}
		~chunk() {}
		T&		operator[](size_t n) {
			return this->_vec[n];
		}
		ft::vector<T>	_vec;
		size_t			_size;
		size_t			_capacity;
	};

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
			map_pointer 	map;
			size_type		map_size;
			allocator_type	_alloc;

		public:

			explicit	deque(const allocator_type& alloc = allocator_type());
			explicit	deque(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc){
				fill_initialize(n, val);
			}
//			template<class InputIterator>
//			deque(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			deque(const deque& x);
			~deque() {
				for (map_pointer cur = start.node; cur <= finish.node; ++cur)
					delete *cur;
				delete map;
			}
			deque&	operator=(const deque& x);

			iterator begin() { return start; }
			iterator end() { return finish; }
			reference front() {
				return *start;
			}
			reference back() {
				// cant use *finish
				iterator tmp = finish;
				--tmp;
				return *tmp; // return finish's *cur
			}
			reference operator[](size_type n) {
				//random access, use __deque_iterator operator[]
				return start[n];
			}

		private:
			void	fill_initialize(size_type n, const value_type& val) {
				// allocate memory for map and chunk
				// initialize pointer
				create_map_and_nodes(n);

				// initialize value for the chunks
				for (map_pointer cur = start.node; cur < finish.node; ++cur) {
					initialized_fill_n(*cur, ARRAY_SIZE, val);
				}
				// the end chunk may have space node, which don't need to have initialized value
				initialized_fill_n(finish.first, finish.cur - finish.first, val);
			}

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
