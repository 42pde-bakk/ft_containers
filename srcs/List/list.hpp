/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 12:23:59 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/09/18 00:26:30 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <limits>
# include <memory>
# include <iostream>
# include <cstddef>
# include <cstring>
# include <climits>
# include "node.hpp"
# include "ListIterator.hpp"
// # include "../Traits.hpp"

namespace ft {
	
	template<typename Iterator>
	ptrdiff_t distance(Iterator first, Iterator last) {
		ptrdiff_t dist = 0;
		while (first != last) {
			++dist;
			first++;
		}
		return dist;
	}
	
	template < class T, class Alloc = std::allocator<T> >
	class list {
	public:
		typedef T		value_type;
		typedef Alloc	allocator_type;
		typedef T		&reference;
		typedef const T	&const_reference;
		typedef T		*pointer;
		typedef const T	*const_pointer;
		typedef node<T> *node_pointer;
		typedef ptrdiff_t	difference_type;
		typedef size_t		size_type;
		typedef ListIterator<value_type, reference, pointer, node_pointer> iterator;
		typedef ListIterator<value_type, const_reference, const_pointer, node_pointer> const_iterator;
		// typedef reverse_iterator;
		// typedef const_reverse_iterator;
	private:
		node<T>		*head;
		node<T>		*firstelem;
		node<T>		*tail;
		allocator_type	alloc;
		size_type		length;
	public:
	
	/* Constructors, destructor and operator= */
		explicit list(const allocator_type& alloc = allocator_type()) : alloc(alloc) /* Default constructor */
		{
			this->head = new node<T>();
			this->tail = new node<T>();
			this->head->next = this->tail;
			this->tail->prev = this->head;
			this->length = 0;
		}
		explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : alloc(alloc)
		{
			this->head = new node<T>();
			this->tail = new node<T>();
			this->head->next = this->tail;
			this->tail->prev = this->head;
			this->length = 0;
			this->assign(n, val);
		}
		template <class InputIterator>
		list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : alloc(alloc) {
			this->head = new node<T>();
			this->tail = new node<T>();
			this->head->next = this->tail;
			this->tail->prev = this->head;
			this->length = 0;
			this->assign(first, last);
		}
		list (const list& x) {
			this->head = new node<T>();
			this->tail = new node<T>();
			this->head->next = this->tail;
			this->tail->prev = this->head;
			this->length = 0;
			this->assign(x.begin(), x.end());
		}
		list&	operator=(const list& x) {
			this->clear();
			this->head = new node<T>();
			this->tail = new node<T>();
			this->head->next = this->tail;
			this->tail->prev = this->head;
			this->length = 0;
			this->assign(x.begin(), x.end());
			return *this;
		}
		~list() {
			this->clear();
			delete this->tail;
			delete this->head;
		}
	/* Iterators */
		iterator	begin() {
			return iterator(this->head->next);
		}
		iterator	end() {
			return iterator(this->tail);
		}
		const_iterator	begin() const {
			return const_iterator(this->head->next);
		}
		const_iterator	end() const {
			return const_iterator(this->tail);
		}
		const_iterator	cbegin() const {
			return const_iterator(this->head->next);
		}
		const_iterator	cend() const {
			return const_iterator(this->tail);
		}

	/* Capacity */
		bool		empty() const {
			return !this->length;
		}
		size_type	size() const {
			return this->length;
		}
		size_type	max_size() const {
			return (SSIZE_MAX / sizeof(node<T>));
		}
		
	/* Element access */
		reference		front() {
			return this->head->next->data;
		}
		const_reference	front() const {
			return this->head->next->data;
		}
		reference		back() {
			return this->tail->prev->data;
		}
		const_reference	back() const {
			return this->tail->prev->data;
		}
	
	/* Modifiers */
		template <class InputIterator>
 		void assign(InputIterator first, InputIterator last) {
		// typename enable_if<is_iterator<typename InputIterator::iterator_category>::value, InputIterator>::type * = NULL) {
			this->clear();
			while (first != last) {
				push_back(*first);
				++first;
			} 
		}
		void	assign(size_type n, const value_type& val) {
			this->clear();
			while (n > 0) {
				push_back(val);
				--n;
			}
		}
		void	push_front(const value_type &val) {
			node<T> *ptr = new node<T>(val);
			ptr->prev = this->head;
			ptr->next = this->head->next;
			this->head->next->prev = ptr;
			this->head->next = ptr;
			this->length++;
		}
		void	pop_front() {
			if (this->length)
			{
				node<T> *tmp = this->head->next->next;
				tmp->prev = this->head;
				delete this->head->next;
				this->head->next = tmp;
				this->length--;
			}
		}
		void	push_back(const value_type &val) {
			node<T>	*ptr = new node<T>(val);
			ptr->next = this->tail;
			ptr->prev = this->tail->prev;
			this->tail->prev->next = ptr;
			this->tail->prev = ptr;
			this->length++;
		}
		void	pop_back() {
			if (this->length)
			{
				node<T>	*tmp = this->tail->prev->prev;
				tmp->next = this->tail;
				delete this->tail->prev;
				this->tail->prev = tmp;
				this->length--;
			}
		}
		iterator	insert(iterator position, const value_type& val) {
			node<T> *insertion = new node<T>(val);
			insertion->prev = position.getptr()->prev;
			insertion->next = position.getptr();
			insertion->prev->next = insertion;
			insertion->next->prev = insertion;
			this->length++;
			return iterator(insertion);
		}
		void		insert(iterator position, size_type n, const value_type& val) {
			while (n > 0) {
				insert(position, val);
				--n;
			}
		}
		template <class InputIterator>
		void		insert(iterator position, InputIterator first, InputIterator last) {
			while (first != last) {
				insert(position, *first);
				first++;
			}
		}
		iterator	erase(iterator position) {
			node<T> *tmp = position.getptr();
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			delete tmp;
			this->length--;
			return position.getptr()->next;
		}
		iterator	erase(iterator first, iterator last) {
			iterator out = first;
			while (first != last) {
				if (first != this->head && first != this->tail)
					out = erase(first);
				first++;
			}
			return out;
		}
		void	swap(list& x) {
			list tmp(x);
			x = *this;
			*this = tmp; 
		}
		void	resize(size_type n, value_type val = value_type()) {
			while (this->length > n) {
				pop_back();
			}
			while (this->length < n) {
				push_back(val);
			}
		}
		void	clear() {
			int i = 0;
			while (this->length) {
				pop_back();
				i++;
			}
		}
	/* Relational operators (list) */
	};
	
template <class T, class Alloc>
bool operator== (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs) {
	typename list<T,Alloc>::const_iterator lit = lhs.begin();
	typename list<T,Alloc>::const_iterator rit = rhs.begin();
	
	if (lhs.size() != rhs.size())
		return false;
	while (1) {
		if (*lit != *rit)
			return false;
		if (lit == lhs.end() && rit == rhs.end())
			return true;
		lit++;
		rit++;
	}
	return false;
}
template <class T, class Alloc>
bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
	return !(lhs == rhs);
}

} // namespace ft
// template <typename T, typename Alloc>
// bool operator== (const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) {
// 	if (lhs.getlength() == rhs.getlenght())
// 		return true;
// 	return false;
// }
#endif
