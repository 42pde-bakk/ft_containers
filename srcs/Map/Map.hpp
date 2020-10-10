/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Map.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/27 23:49:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/10 16:31:49 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <limits>
# include <memory>
# include <iostream>
# include <cstddef>
# include <cstdlib>
# include <cstring>
# include <climits>
# include <string>
# include "MapNode.hpp"
// # include "../Iterators/BidirectionalIterator.hpp"
# include "../Traits.hpp"
# include "../Extra.hpp"

# if defined(unix) || defined(__unix__) || defined(__unix)
#  define PEER_MAX SSIZE_MAX
# else
#  define PEER_MAX SIZE_T_MAX
# endif

namespace ft {

template <class T> struct less : std::binary_function <T,T,bool> {
  bool operator() (const T& x, const T& y) const {return x<y;}
};

template <	class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
	class map {
	public:
		typedef Key							key_type;
		typedef T							mapped_type;
		typedef std::pair<const Key, T>		value_type;
		typedef	Compare						key_compare;
		typedef Alloc						allocator_type;
		typedef	value_type&					reference;
		typedef	const value_type&			const_reference;
		typedef	value_type*					pointer;
		typedef	const value_type*			const_pointer;
		// typedef BidirectionalIterator<value_type>			iterator;
		// typedef ConstBidirectionalIterator<value_type>		const_iterator;
		// typedef RevBidirectionalIterator<value_type>		reverse_iterator;
		// typedef ConstRevBidirectionalIterator<value_type>	const_reverseiterator;
		typedef	ptrdiff_t					difference_type;
		typedef	size_t						size_type;
		typedef mapnode<value_type, key_compare>	mapnode;

	// Constructors, destructors and operator=
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _comp(comp) {
			this->initmap();
		}
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		map (const map& x);
		~map() {
			this->clear();
			delete this->_root;
			delete this->_first;
			delete this->_last;
		}
		map& operator= (const map& x) {
			if (this != &x) {
				this->clear();
				(void)x;
				this->_root->left = this->_first;
				this->_root->right = this->_last;
				this->_first->parent = this->_root;
				this->_last->parent = this->_root;				
			}
			return (*this);
		}
	// Iterator functions
		// iterator				begin();
		// const_iterator			begin() const;
		// iterator				end();
		// const_iterator			end() const;
		// reverse_iterator		rbegin();
		// const_reverse_iterator	rbegin() const;
		// reverse_iterator		rend();
		// const_reverse_iterator	rend() const;

	// Capacity functions
		bool	empty() const {
			return this->_size;
		}
		size_type	size() const {
			return this->_size;
		}
		size_type	max_size() const {
			return (PEER_MAX / sizeof(pair));
		}

	// Element access functions
		mapped_type&	operator[](const key_type& k);
		mapped_type&	at(const key_type& k); //C++11, throws an exception if the key_type does not exist in the container
		const mapped_type&	at(const key_type& k) const;

	// Modifier functions
		// pair<iterator, bool>	insert(const value_type& val);
		// iterator				insert(iterator position, const value_type& val);
		// template <class InputIterator>
		// void					insert(InputIterator first, InputIterator last);
		// void		erase(iterator position);
		size_type	erase(const key_type& k);
		// void		erase(iterator first, iterator last);
		void		swap(map& x);
		void		clear() {
			
		}

	// Observer functions
		key_compare		key_comp() const;
		// value_compare	value_comp() const;
	
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
				this->_root = new mapnode();
				this->_first = new mapnode();
				this->_first->parent = _root;
				this->_last = new mapnode(*this->_first);
				this->_root->left = _first;
				this->_root->right = _last;
			}
		mapnode			*_root;
		mapnode			*_first;
		mapnode			*_last;
		allocator_type	_alloc;
		key_compare		_comp;
		size_type		_size;
	};
	
}


#endif
