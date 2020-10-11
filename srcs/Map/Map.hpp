/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Map.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/27 23:49:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/11 21:08:24 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <limits>
// # include <memory>
# include <iostream>
# include <cstddef>
# include <cstdlib>
# include <cstring>
# include <climits>
# include <string>
# include "MapNode.hpp"
 # include "../Iterators/BidirectionalIterator.hpp"
# include "../Traits.hpp"
# include "../Extra.hpp"

# if defined(unix) || defined(__unix__) || defined(__unix)
#  define PEER_MAX SSIZE_MAX
# else
#  define PEER_MAX SIZE_T_MAX
# endif

namespace ft {

template <class T>
struct less : std::binary_function<T,T,bool> {
	bool operator() (const T& x, const T& y) const { return (x < y); }
};

template <	class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
	class map {
	public:
		typedef Key							key_type;
		typedef T							mapped_type;
		typedef std::pair<const Key, T>		value_type;
		typedef	Compare						key_compare;
		typedef	Compare						value_compare;
		typedef Alloc						allocator_type;
		typedef	value_type&					reference;
		typedef	const value_type&			const_reference;
		typedef	value_type*					pointer;
		typedef	const value_type*			const_pointer;
		typedef node<value_type, key_compare>	mapnode;
		typedef BidirectionalIterator<value_type, mapnode* >		iterator;
		typedef ConstBidirectionalIterator<value_type, mapnode*>	const_iterator;
		typedef RevBidirectionalIterator<value_type, mapnode*>		reverse_iterator;
		typedef ConstRevBidirectionalIterator<value_type, mapnode*>	const_reverse_iterator;
		typedef	ptrdiff_t					difference_type;
		typedef	size_t						size_type;

	// Constructors, destructors and operator=
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _comp(comp) {
			this->_size = 0;
			this->initmap();
		}
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		map (const map& x);
		~map() {
			this->clear();
			delete this->_top;
			delete this->_first;
			delete this->_last;
		}
		map& operator= (const map& x) {
			if (this != &x) {
				this->clear();
				(void)x; //this fnction is bs
				this->_root->left = this->_first;
				this->_root->right = this->_last;
				this->_first->parent = this->_root;
				this->_last->parent = this->_root;				
			}
			return (*this);
		}
	// Iterator functions
		iterator				begin() {
			return iterator(this->_first->parent);
		}
		const_iterator			begin() const {
			return const_iterator(this->_first->parent);
		}
		iterator				end() {
			return iterator(this->_last);
		}
		const_iterator			end() const {
			return const_iterator(this->_last);
		}
		reverse_iterator		rbegin() {
			return reverse_iterator(this->_last->parent);
		}
		const_reverse_iterator	rbegin() const {
			return const_reverse_iterator(this->_last->parent);
		}
		reverse_iterator		rend() {
			return reverse_iterator(this->_first);
		}
		const_reverse_iterator	rend() const {
			return const_reverse_iterator(this->_first);
		}

	// Capacity functions
		bool	empty() const {
			return this->_size;
		}
		size_type	size() const {
			return this->_size;
		}
		size_type	max_size() const {
			return (PEER_MAX / sizeof(value_type));
		}

	// Element access functions
		mapped_type&		operator[](const key_type& k);
		mapped_type&		at(const key_type& k); //C++11, throws an exception if the key_type does not exist in the container
		const mapped_type&	at(const key_type& k) const; //C++11

	// Modifier functions
		std::pair<iterator, bool>	insert(const value_type& val) {
			if (this->_size == 0)
				return (std::make_pair(iterator(insert_root(val)), true));
			mapnode	*it(this->_root);
			while (it->left || it->right) {
				if (key_compare()(val.first, it->data.first)) {
					if (it->left && it->left != this->_first)
						it = it->left;
					else return std::make_pair(iterator(insert_left(it, val)), true);
				}
				else if (key_compare()(it->data.first, val.first)) {
					if (it->right && it->right != this->_last)
						it = it->right;
					else return std::make_pair(iterator(insert_right(it, val)), true);
				}
				else break;
			}
			return std::make_pair(iterator(it), false);
		}
		iterator				insert(iterator position, const value_type& val) {
			if (position.data < val.first) {
				while (position.data < val.first)
					--position;
				return iterator(insert_left(position, val));
			}
			else if (position.data > val.first) {
				while (position.data > val.first)
					++position;
				return iterator(insert_right(position, val));
			}
			return position;
		}
		template <class InputIterator>
		void					insert(InputIterator first, InputIterator last) {
			while (first != last) {
				insert(*first);
				// std::cout << "just inserted " << first->first << " => " << first->second << std::endl;
				++first;
			}
			std::cout << "breakpoint" << std::endl;
		}
		// void		erase(iterator position);
		size_type	erase(const key_type& k);
		// void		erase(iterator first, iterator last);
		void		swap(map& x);
		void		clear() {
			this->clear(this->_root);
			this->link_outer();
		}

	// Observer functions
		key_compare		key_comp() const {
			return this->_comp;
		}
		value_compare	value_comp() const;
	
	// Operation functions
		// iterator			find(const key_type& k);
		// const_iterator	find(const key_type& k) const;
		size_type	count(const key_type& k) const;
		// iterator			lower_bound(const key_type& k);
		// const_iterator	lower_bound(const key_type& k) const;
		// iterator			upper_bound(const key_type& k);
		// const_iterator	upper_bound(const key_type& k) const;
		// pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
		// pair<iterator,iterator>             equal_range (const key_type& k);
		
		private:
			void	initmap() {
				this->_top = new mapnode();
				this->_first = new mapnode();
				this->_first->parent = _top;
				this->_last = new mapnode(*this->_first);
				this->_top->left = _first;
				this->_top->right = _last;
				this->_size = 0;
			}
			mapnode	*insert_root(const value_type& val) {
				this->_root = new mapnode(val);
				++this->_size;
				_first->parent = _last->parent = \
				_top->left = _top->right = _root;
				_root->left = _first,	_root->right = _last,	_root->parent = _top;
				return this->_root;
			}
			mapnode	*insert_left(mapnode *it, const value_type& val = value_type()) {
				mapnode *insert = new mapnode(val);
				insert->parent = it;
				if (it->left)
					it->left->parent = insert;
				it->left = insert;
				++this->_size;
				return insert;
			}
			mapnode	*insert_right(mapnode *it, const value_type& val = value_type()) {
				mapnode *insert = new mapnode(val);
				insert->parent = it;
				if (it->right)
					it->right->parent = insert;
				it->right = insert;
				++this->_size;
				return insert;
			}
			void	clear(mapnode *pos) {
				if (!pos)
					return ;
				clear(pos->left);
				clear(pos->right);
				if (pos != _top && pos != _first && pos != _last)
					delete pos;
			}
			void	link_outer() {
				_top->left = _first;
				_top->right = _last;
				_first->parent = _top;
				_last->parent = _top;
			}
		mapnode			*_top;
		mapnode			*_root;
        mapnode			*_first;
        mapnode			*_last;
		allocator_type	_alloc;
		key_compare		_comp;
		size_type		_size;
	};
	
}


#endif
