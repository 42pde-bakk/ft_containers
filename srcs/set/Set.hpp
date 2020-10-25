/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Set.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/27 23:49:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/25 13:16:31 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include "../utils/MapBase.hpp"

namespace ft {

template < class Key, class Compare = less<Key>, class Alloc = std::allocator<Key> >
	class set : public MapBase<const Key, const Key, const Key, Compare, Alloc>  {
	public:
		typedef MapBase<const Key, const Key, const Key, Compare, Alloc>	Base;
		typedef Key					key_type;
//		typedef Key					mapped_type;
		typedef Key					value_type;
		typedef	Compare				key_compare;
		typedef	Compare				value_compare;
		typedef Alloc				allocator_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef	const value_type*	const_pointer;
		using typename				Base::mapnode;
		using typename				Base::iterator;
		using typename				Base::const_iterator;
		using typename				Base::reverse_iterator;
		using typename				Base::const_reverse_iterator;
		using typename				Base::difference_type;
		using typename				Base::size_type;

	// Constructors, destructors and operator=
		explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: Base(comp, alloc) {
		}
		template <class InputIterator>
		set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
					typename enable_if<is_iterator<typename InputIterator::iterator_category>::value, InputIterator>::type * = 0)
				: Base(comp, alloc) {
			this->insert(first, last);
		}
		set (const set& x) : Base() {
			this->insert(x.begin(), x.end());
		}
		virtual	~set() { }

		set& operator= (const set& x) {
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
		virtual size_type	max_size() const {
			return this->_alloc.max_size() / sizeof(pointer);
		}
	// Modifier functions: see Base
		std::pair<iterator, bool>	insert(const value_type& val) {
			if (this->_size == 0)
				return (std::make_pair(iterator(Base::insert_root(val)), true));
			mapnode	*it(this->_root);
			while (it) {
				if (this->key_comp()(val, it->data)) {
					if (it->left && it->left != this->_first)
						it = it->left;
					else return std::make_pair(iterator(Base::insert_left(it, val)), true);
				}
				else if (key_compare()(it->data, val)) {
					if (it->right && it->right != this->_last)
						it = it->right;
					else return std::make_pair(iterator(Base::insert_right(it, val)), true);
				}
				else break ;
			}
			return std::make_pair(iterator(it), false);
		}
		iterator				insert(iterator position, const value_type& val, typename enable_if<is_iterator<typename iterator::iterator_category>::value, iterator>::type * = 0) {
			(void)position;
			return this->insert(val).first;
		}
		template <class InputIterator>
		void					insert(InputIterator first, InputIterator last, typename enable_if<is_iterator<typename InputIterator::iterator_category>::value, InputIterator>::type * = 0) {
			while (first != last) {
				this->insert(*first);
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
		virtual iterator			find(const key_type& k) {
			mapnode	*it(this->_root);
			while (it && it != this->_first && it != this->_last) {
				if (this->key_comp()(k, it->data))
					it = it->left;
				else if (this->key_comp()(it->data, k))
					it = it->right;
				else return iterator(it);
			}
			return this->end();
		}
		virtual const_iterator	find(const key_type& k) const {
			mapnode	*it(this->_root);
			while (it && it != this->_first && it != this->_last) {
				if (this->key_comp()(k, it->data))
					it = it->left;
				else if (this->key_comp()(it->data, k))
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
				if (this->key_comp()(*it, k) == false)
					break ;
				++it;
			}
			return it;
		}
		const_iterator	lower_bound(const key_type& k) const {
			const_iterator	it = Base::begin(), ite = Base::end();
			while (it != ite) {
				if (this->key_comp()(*it, k) == false)
					break ;
				++it;
			}
			return it;
		}
		iterator			upper_bound(const key_type& k) {
			iterator	it = Base::begin(), ite = Base::end();
			while (it != ite) {
				if (this->key_comp()(k, *it))
					break ;
				++it;
			}
			return it;
		}
		const_iterator			upper_bound(const key_type& k) const {
			const_iterator it = Base::begin(), ite = Base::end();
			while (it != ite) {
				if (this->key_comp()(k, *it))
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
	// Operation functions: see Base
	private:
		mapnode			*find(iterator position) {
			mapnode	*it(this->_root);
			while (it && it != this->_first && it != this->_last) {
				if (this->key_comp()(*position, it->data))
					it = it->left;
				else if (this->key_comp()(it->data, *position))
					it = it->right;
				else return (it);
			}
			return this->_last;
		}
	};

/* Relational operators (set): see Base */

} // ft namespace


#endif
