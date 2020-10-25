/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MultiSet.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/27 23:49:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/25 13:16:19 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTISET_HPP
# define MULTISET_HPP

# include "../utils/MapBase.hpp"

namespace ft {

template < class Key, class Value, class Compare = less<Key>, class Alloc = std::allocator<Key> >
	class multiset : public MapBase<Key, Key, Compare, Alloc>  {
	public:
		typedef MapBase<Key, Key, Compare, Alloc>	Base;
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
		explicit multiset(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: Base(comp, alloc) {
		}
		template <class InputIterator>
		multiset (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
					typename enable_if<is_iterator<typename InputIterator::iterator_category>::value, InputIterator>::type * = 0)
				: Base(comp, alloc) {
			this->insert(first, last);
		}
		multiset (const multiset& x) : Base() {
			this->insert(x.begin(), x.end());
		}
		virtual	~multiset() { }

		multiset& operator= (const multiset& x) {
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
	// Modifier functions: see Base
		iterator	insert(const value_type& val) {
			if (this->_size == 0)
				return iterator(Base::insert_root(val));
			mapnode	*it(this->_root);
			while (it) {
				if (key_compare()(val.first, it->data.first)) {
					if (it->left && it->left != this->_first)
						it = it->left;
					else return iterator(Base::insert_left(it, val));
				}
				else  {
					if (it->right && it->right != this->_last)
						it = it->right;
					else return iterator(Base::insert_right(it, val));
				}
			}
			return Base::end();
		}
		iterator				insert(iterator position, const value_type& val,
									   typename enable_if<is_iterator<typename iterator::iterator_category>::value, iterator>::type * = 0) {
			(void)position;
			return insert(val).first;
		}
		template <class InputIterator>
		void					insert(InputIterator first, InputIterator last) { //, typename enable_if<is_iterator<typename InputIterator::iterator_category>::value, InputIterator>::type * = 0) {
			while (first != last) {
				insert(*first);
				++first;
			}
		}
		size_type	erase(const key_type& k) {
			size_type ret = 0;
			mapnode	*trav(this->_root);
			while (trav) {
				if (key_compare()(k, trav->data.first)) {
					trav = trav->left;
				}
				else if (key_compare()(trav->data.first, k))
					trav = trav->right;
				else {
					mapnode	*erase(trav);
					trav = trav->parent;
					Base::RedBlackDelete((erase));
					delete erase;
					--this->_size;
					++ret;
					if (!trav)
						trav = this->_root;
				}
			}
			return ret;
		}
	// Observer functions: see Base

	// Operation functions: see Base
		virtual size_type	count(const key_type& k) const {
			const_iterator	it = this->begin();
			size_type		count = 0;

			while (it != this->end()) {
				if (key_compare()(k, it->first) == false && key_compare()(it->first, k) == false)
					++count;
				++it;
			}
			return count;
		}
	};

/* Relational operators (multiset): see Base */

} // ft namespace


#endif
