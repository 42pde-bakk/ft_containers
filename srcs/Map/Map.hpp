/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Map.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/27 23:49:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/18 17:08:43 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <cstddef>
# include <climits>
# include "MapNode.hpp"
# include "../Iterators/BidirectionalIterator.hpp"
# include "../Traits.hpp"
# include "../Extra.hpp"
#include <math.h>

namespace ft {

template <class T>
struct less : std::binary_function<T,T,bool> {
	bool operator() (const T& x, const T& y) const { return (x < y); }
};

template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
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
		typedef node<value_type, key_compare>	mapnode;
		typedef BidirectionalIterator<value_type, mapnode* >		iterator;
		typedef ConstBidirectionalIterator<value_type, mapnode*>	const_iterator;
		typedef RevBidirectionalIterator<value_type, mapnode*>		reverse_iterator;
		typedef ConstRevBidirectionalIterator<value_type, mapnode*>	const_reverse_iterator;
		typedef	ptrdiff_t					difference_type;
		typedef	size_t						size_type;

		class value_compare // ngl, I yoinked this class straight off http://www.cplusplus.com/reference/map/map/value_comp/
		{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			friend class map;
		protected:
			Compare comp;
			explicit value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const {
				return comp(x.first, y.first);
			}
		};

	// Constructors, destructors and operator=
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _comp(comp), _size(0){
			this->initmap();
		}
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
					typename enable_if<is_iterator<typename InputIterator::iterator_category>::value, InputIterator>::type * = 0)
				: _alloc(alloc), _comp(comp), _size(0) {
			this->initmap();
			this->insert(first, last);
		}
		map (const map& x) : _alloc(x._alloc), _comp(x._comp), _size(0) {
			this->initmap();
			this->insert(x.begin(), x.end());
		}
		~map() {
			this->clear();
			delete this->_first;
			delete this->_last;
		}
		map& operator= (const map& x) {
			if (this != &x) {
				this->clear();
				this->_alloc = x._alloc;
				this->_comp = x._comp;
				this->insert(x.begin(), x.end());
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
			return (this->_size == 0);
		}
		size_type	size() const {
			return (this->_size);
		}
		size_type	max_size() const {
			return this->_alloc.max_size();		// manjaro
			return this->_alloc.max_size() / 2;	// workflows
			// if (LINUX)
			// 	return (std::numeric_limits<size_type>::max() / (2 * (sizeof(mapnode) + sizeof(pointer))));
			// else
			// 	return (this->_alloc.max_size() / 2);
		}

	// Element access functions
		mapped_type&		operator[](const key_type& k) {
			return insert(std::make_pair(k, mapped_type())).first->second;
		}
		mapped_type&		at(const key_type& k) { //C++11, throws an exception if the key_type does not exist in the container
			iterator it = find(k);
			if (it == end())
				throw std::out_of_range("map::at:  key not found");
			return it->second;
		}
		const mapped_type&	at(const key_type& k) const {
			const_iterator it = find(k);
			if (it == end())
				throw std::out_of_range("map::at:  key not found");
			return it->second;
		}
	// Modifier functions
		std::pair<iterator, bool>	insert(const value_type& val) {
			if (this->_size == 0)
				return (std::make_pair(iterator(insert_root(val)), true));
			mapnode	*it(this->_root);
			while (it) {
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
		iterator				insert(iterator position, const value_type& val,
						typename enable_if<is_iterator<typename iterator::iterator_category>::value, iterator>::type * = 0) {
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
		void					insert(InputIterator first, InputIterator last, typename enable_if<is_iterator<typename InputIterator::iterator_category>::value, InputIterator>::type * = 0) {
			while (first != last) {
				insert(*first);
				++first;
			}
		}
		void		erase(iterator position) {
			mapnode	*erase = find(position);
			if (erase == _last) 
				return ;
			short children = (erase->left != 0) + (erase->right != 0);
			if (!children) {
				if (value_comp()(erase->data, erase->parent->data))
					erase->parent->left = erase->left;
				else
					erase->parent->right = erase->right;
			}
			else if (children == 1) {
				if (value_comp()(erase->data, erase->parent->data))
					erase->parent->left = (erase->left ? erase->left : erase->right);
				else
					erase->parent->right = (erase->left ? erase->left : erase->right);
				erase->left ? erase->left->parent = erase->parent : erase->right->parent = erase->parent;
			}
			else {
				bool switchdirection = false;
				mapnode	*tmp;
				if (erase->right != this->_last) {
					tmp = erase->right;
					while (tmp->left) {
						tmp = tmp->left;
						switchdirection = true;
					}
					tmp->parent = erase->parent;
					if (erase->parent && value_comp()(tmp->data, tmp->parent->data)) //node is smaller than parent
						tmp->parent->left = tmp;
					else if (erase->parent)
						tmp->parent->right = tmp;
					tmp->left = erase->left;
					tmp->left->parent = tmp;
					if (switchdirection) {
						tmp->right = erase->right;
						tmp->right->parent = tmp;
					}
				}
				else {
					tmp= erase->left;
					while (tmp->right) {
						tmp = tmp->right;
						switchdirection = true;
					}
					tmp->parent = erase->parent;
					if (erase->parent && value_comp()(tmp->data, tmp->parent->data)) //node is smaller than parent
						tmp->parent->left = tmp;
					else if (erase->parent)
						tmp->parent->right = tmp;
					tmp->right = erase->right;
					tmp->right->parent = tmp;
					if (switchdirection) {
						tmp->left = erase->left;
						tmp->left->parent = tmp;
					}
				}
				if (erase == this->_root)
					this->_root = tmp;
			}
			delete erase;
			--this->_size;
		}
		size_type	erase(const key_type& k) {
			iterator it = find(k);
			if (it == end())
				return 0;
			erase(it);
			return 1;
		}
		void		erase(iterator first, iterator last) {
			while (first != last) {
				erase(first);
				++first;
			}
		}
		void		swap(map& x) {
			map tmp(x);
			x = *this;
			*this = tmp;
		}
		void		clear() {
			if (!this->empty()) {
				this->clear(this->_root);
				this->link_outer();
			}
		}

	// Observer functions
		key_compare		key_comp() const {
			return this->_comp;
		}
		value_compare	value_comp() const {
			return value_compare(this->_comp);
		}
	
	// Operation functions
		iterator			find(const key_type& k) {
			mapnode	*it(this->_root);
			while (it && it != this->_first && it != this->_last) {
				if (key_compare()(k, it->data.first))
					it = it->left;
				else if (key_compare()(it->data.first, k))
					it = it->right;
				else return iterator(it);
			}
			return this->end();
		}
		const_iterator	find(const key_type& k) const {
			mapnode	*it(this->_root);
			while (it && it != this->_first && it != this->_last) {
				if (key_compare()(k, it->data.first))
					it = it->left;
				else if (key_compare()(it->data.first, k))
					it = it->right;
				else return const_iterator(it);
			}
			return this->end();
		}
		size_type	count(const key_type& k) const {
			return (find(k) != this->end());
		}
		iterator			lower_bound(const key_type& k) {
			iterator	it = begin(), ite = end();
			while (it != ite) {
				if (key_comp()(it->first, k) == false)
					break ;
				++it;
			}
			return it;
		}
		const_iterator	lower_bound(const key_type& k) const {
			const_iterator	it = begin(), ite = end();
			while (it != ite) {
				if (key_comp()(it->first, k) == false)
					break ;
				++it;
			}
			return it;
		}
		iterator			upper_bound(const key_type& k) {
			iterator	it = begin(), ite = end();
			while (it != ite) {
				if (key_comp()(k, it->first))
					break ;
				++it;
			}
			return it;
		}
		const_iterator			upper_bound(const key_type& k) const {
			const_iterator it = begin(), ite = end();
			while (it != ite) {
				if (key_comp()(k, it->first))
					break ;
				++it;
			}
			return it;
		}
		std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
			return std::make_pair(const_iterator(lower_bound(k)), const_iterator(upper_bound(k)));
		}
		std::pair<iterator,iterator>             equal_range (const key_type& k) {
			return std::make_pair(iterator(lower_bound(k)), iterator(upper_bound(k)));
		}
		void printBT() const {
			printBT("", this->_root, false);
			std::cerr << std::endl;
		}
		private:
			void printBT(const std::string& prefix, const mapnode* trav, bool isLeft) const {
				if (trav && trav != _first && trav != _last) {
					std::cerr << prefix;
					std::cerr << (isLeft ? "├──" : "└──" );
					// print the value of the node
					std::cerr << trav->data.first << std::endl;
					// enter the next tree level - left and right branch
					printBT( prefix + (isLeft ? "│   " : "    "), trav->left, true);
					printBT( prefix + (isLeft ? "│   " : "    "), trav->right, false);
				}
			}
			void	initmap() {
				this->_first = new mapnode();
				this->_last = new mapnode();
				this->link_outer();
				this->_size = 0;
			}
			mapnode	*insert_root(const value_type& val) {
				this->_root = new mapnode(val);
				++this->_size;
				_first->parent = _last->parent = this->_root;
				this->_root->left = _first;
				this->_root->right = _last;
				return this->_root;
			}
			void	erase_root() {
				if (this->_size == 1) {
					delete this->_root;
					this->link_outer();
					return ;
				}
				
			}
			mapnode	*insert_left(mapnode *it, const value_type& val = value_type()) {
				mapnode *insert = new mapnode(val);
				insert->parent = it;
				insert->left = it->left;
				if (it->left)
					it->left->parent = insert;
				it->left = insert;
				++this->_size;
				return insert;
			}
			mapnode	*insert_right(mapnode *it, const value_type& val = value_type()) {
				mapnode *insert = new mapnode(val);
				insert->parent = it;
				insert->right = it->right;
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
				if (pos != _first && pos != _last) {
					delete pos;
					--this->_size;
				}
			}
			void	link_outer() {
				this->_first->parent = this->_last;
				this->_last->parent = this->_first;
			}
			mapnode			*find(iterator position) {
				mapnode	*it(this->_root);
				while (it && it != this->_first && it != this->_last) {
					if (key_compare()(position->first, it->data.first))
						it = it->left;
					else if (key_compare()(it->data.first, position->first))
						it = it->right;
					else return (it);
				}
				return this->_last;
			}
		mapnode			*_root;
        mapnode			*_first;
        mapnode			*_last;

		allocator_type	_alloc;
		key_compare		_comp;
		size_type		_size;
	};

/* Relational operators (map) */
template <class Key, class T, class Compare, class Alloc>
bool operator== (const ft::map<Key,T,Compare, Alloc>& lhs, const ft::map<Key,T,Compare, Alloc>& rhs) {
	typename map<Key,T,Compare, Alloc>::const_iterator lit = lhs.begin();
	typename map<Key,T,Compare, Alloc>::const_iterator rit = rhs.begin();
	
	if (lhs.size() != rhs.size())
		return false;
	while (lit != lhs.end() && rit != rhs.end()) {
		if (*lit != *rit)
			return false;
		++lit;
		++rit;
	}
	return true;
}
template <class Key, class T, class Compare, class Alloc>
bool operator!= (const map<Key,T,Compare, Alloc>& lhs, const map<Key,T,Compare, Alloc>& rhs) {
	return !(lhs == rhs);
}
template <class Key, class T, class Compare, class Alloc>
bool operator<  (const map<Key,T,Compare, Alloc>& lhs, const map<Key,T,Compare, Alloc>& rhs) {
	typename map<Key,T,Compare, Alloc>::const_iterator lit = lhs.begin();
	typename map<Key,T,Compare, Alloc>::const_iterator rit = rhs.begin();
	if (lhs.size() > rhs.size())
		return false;
	while (lit != lhs.end() && rit != rhs.end()) {
		if (*lit != *rit)
			return (lit < rit);
		++lit;
		++rit;
	}
	return false;
}
template <class Key, class T, class Compare, class Alloc>
bool operator<= (const map<Key,T,Compare, Alloc>& lhs, const map<Key,T,Compare, Alloc>& rhs) {
	return !(lhs < rhs);
}
template <class Key, class T, class Compare, class Alloc>
bool operator>  (const map<Key,T,Compare, Alloc>& lhs, const map<Key,T,Compare, Alloc>& rhs) {
	return (rhs < lhs);
}
template <class Key, class T, class Compare, class Alloc>
bool operator>= (const map<Key,T,Compare, Alloc>& lhs, const map<Key,T,Compare, Alloc>& rhs) {
	return !(lhs > rhs);
}
template <class Key, class T, class Compare, class Alloc>
void swap (map<Key,T,Compare, Alloc>& x, map<Key,T,Compare, Alloc>& y) {
	map<Key,T,Compare, Alloc> tmp(x);
	x = y;
	y = tmp;
}
}


#endif
