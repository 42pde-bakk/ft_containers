/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Map.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/27 23:49:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/22 14:23:58 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "../utils/MapBase.hpp"

namespace ft {

template < class Key, class Value, class Compare = less<Key>, class Alloc = std::allocator<std::pair<const Key,Value> > >
class map : public MapBase<const Key, Value, std::pair<const Key, Value>, Compare, Alloc>  {
	public:
		typedef MapBase<const Key, Value, std::pair<const Key, Value>, Compare, Alloc>	Base;
		using typename								Base::key_type;
		using typename								Base::mapped_type;
		using typename								Base::value_type;
		using typename								Base::key_compare;
		using typename								Base::allocator_type;
		using typename								Base::reference;
		using typename								Base::const_reference;
		using typename								Base::pointer;
		using typename								Base::const_pointer;
		using typename								Base::mapnode;
		using typename								Base::iterator;
		using typename								Base::const_iterator;
		using typename								Base::reverse_iterator;
		using typename								Base::const_reverse_iterator;
		using typename								Base::difference_type;
		using typename								Base::size_type;

	// Constructors, destructors and operator=
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: Base(comp, alloc) {
		}
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
					typename enable_if<is_iterator<typename InputIterator::iterator_category>::value, InputIterator>::type * = 0)
				: Base(comp, alloc) {
			this->insert(first, last);
		}
		map (const map& x) : Base() {
			this->insert(x.begin(), x.end());
		}

		virtual	~map() { }

		map& operator= (const map& x) {
			if (this != &x) {
				this->clear();
				this->_alloc = x._alloc;
				this->_comp = x._comp;
				this->insert(x.begin(), x.end());
			}
			return (*this);
		}
	// Iterator functions: see MapBase

	// Capacity functions: see MapBase

	// Element access functions
		mapped_type&		operator[](const key_type& k) {
			return insert(std::make_pair(k, mapped_type())).first->second;
		}
		mapped_type&		at(const key_type& k) {
			iterator it =this->find(k);
			if (it == Base::end())
				throw std::out_of_range("map::at:  key not found");
			return it->second;
		}
		const mapped_type&	at(const key_type& k) const {
			const_iterator it = this->find(k);
			if (it == Base::end())
				throw std::out_of_range("map::at:  key not found");
			return it->second;
		}
	// Modifier functions: see Base
		std::pair<iterator, bool>	insert(const value_type& val) {
			if (this->_size == 0)
				return (std::make_pair(iterator(Base::insert_root(val)), true));
			mapnode	*it(this->_root);
			while (it) {
				if (key_compare()(val.first, it->data.first)) {
					if (it->left && it->left != this->_first)
						it = it->left;
					else return std::make_pair(iterator(Base::insert_left(it, val)), true);
				}
				else if (key_compare()(it->data.first, val.first)) {
					if (it->right && it->right != this->_last)
						it = it->right;
					else return std::make_pair(iterator(Base::insert_right(it, val)), true);
				}
				else break ;
			}
			return std::make_pair(iterator(it), false);
		}
		iterator	insert(iterator position, const value_type& val, typename enable_if<is_iterator<typename iterator::iterator_category>::value, iterator>::type * = 0) {
			(void)position;
			return insert(val).first;
		}
		template <class InputIterator>
		void		insert(InputIterator first, InputIterator last, typename enable_if<is_iterator<typename InputIterator::iterator_category>::value, InputIterator>::type * = 0) {
			while (first != last) {
				insert(*first);
				++first;
			}
		}
		void		erase(iterator position) {
			mapnode	*erase = this->find(position);
			if (erase == this->_last)
				return ;
			this->RedBlackDelete(erase);
			delete erase;
			--this->_size;
		}
		virtual size_type	erase(const key_type& k) {
			iterator it = this->find(k);
			if (it == this->end())
				return 0;
			this->erase(it);
			return 1;
		}
		void		erase(iterator first, iterator last) {
			while (first != last) {
				this->erase(first);
				++first;
			}
		}
	// Observer functions: see Base

	// Operation functions
		virtual iterator			find(const key_type& k) {
			mapnode	*it(this->_root);
			while (it && it != this->_first && it != this->_last) {
				if (this->key_comp()(k, it->data.first))
					it = it->left;
				else if (this->key_comp()(it->data.first, k))
					it = it->right;
				else return iterator(it);
			}
			return this->end();
		}
		virtual const_iterator	find(const key_type& k) const {
			mapnode	*it(this->_root);
			while (it && it != this->_first && it != this->_last) {
				if (this->key_comp()(k, it->data.first))
					it = it->left;
				else if (this->key_comp()(it->data.first, k))
					it = it->right;
				else return const_iterator(it);
			}
			return this->end();
		}
		virtual size_type	count(const key_type& k) const {
			return (find(k) != this->end());
		}
		iterator			lower_bound(const key_type& k) {
			iterator	it = Base::begin(), ite = Base::end();
			while (it != ite) {
				if (this->key_comp()(it->first, k) == false)
					break ;
				++it;
			}
			return it;
		}
		const_iterator	lower_bound(const key_type& k) const {
			const_iterator	it = Base::begin(), ite = Base::end();
			while (it != ite) {
				if (this->key_comp()(it->first, k) == false)
					break ;
				++it;
			}
			return it;
		}
		iterator			upper_bound(const key_type& k) {
			iterator	it = Base::begin(), ite = Base::end();
			while (it != ite) {
				if (this->key_comp()(k, it->first))
					break ;
				++it;
			}
			return it;
		}
		const_iterator			upper_bound(const key_type& k) const {
			const_iterator it = Base::begin(), ite = Base::end();
			while (it != ite) {
				if (this->key_comp()(k, it->first))
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
	private:
		mapnode			*find(iterator position) {
			mapnode	*it(this->_root);
			while (it && it != this->_first && it != this->_last) {
				if (this->key_comp()(position->first, it->data.first))
					it = it->left;
				else if (this->key_comp()(it->data.first, position->first))
					it = it->right;
				else return (it);
			}
			return this->_last;
		}
	};

/* Relational operators (map): see Base */

} // ft namespace


#endif
