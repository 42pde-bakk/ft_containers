/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 12:23:59 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/09/16 17:15:42 by peerdb        ########   odam.nl         */
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
		node<T>		*lastelem;
		node<T>		*tail;
		allocator_type	alloc;
		size_type		length;
	public:
		explicit list(const allocator_type& alloc = allocator_type()) : alloc(alloc) /* Default constructor */
		{
			this->head = new node<T>();
			this->tail = new node<T>();
			// std::cout << "new list with head: " << head << ", and tail: " << tail << std::endl;
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
		}
		~list() {
			std::cout << "starting ~list()" << std::endl;
			std::cout << "this->head = " << this->head << ", this->tail = " << this->tail << std::endl;
			this->clear();
			std::cout << "after clear()" << std::endl;
			delete this->tail;
			std::cout << "after deleting tail" << std::endl;
			delete this->head;
			std::cout << "after deleting head" << std::endl;
		}
		iterator	begin() {
			return iterator(this->head->next);
		}
		iterator	end() {
			return iterator(this->tail);
		}
		const_iterator	cbegin() const {
			return const_iterator(this->head->next);
		}
		const_iterator	cend() const {
			return const_iterator(this->tail);
		}
		T	front() const {
			// What happens if this->length == 0?
			return this->head->next->data;
		}
		T	back() const {
			// same question as above<< &first << ", last: " << &last 
		}
		template <class InputIterator>
 		void assign(InputIterator first, InputIterator last) {
		// typename enable_if<is_iterator<typename InputIterator::iterator_category>::value, InputIterator>::type * = NULL) {
			this->clear();
			while (first != last) {
				push_back(*first);
				first++;
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
			ptr->next = ptr;
			this->length++;
			std::cout << "pushing front " << this->head->next << std::endl;

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
			this->lastelem = ptr;
			this->length++;
			std::cout << "pushing back " << this->lastelem << std::endl;
		}
		void	pop_back() {
			if (this->length)
			{
				std::cout << "this->lastelem->prev = " << lastelem->prev << std::endl;
				node<T>	*tmp = this->lastelem->prev;
				tmp->next = this->tail;
				this->tail->prev = tmp;
				std::cout << "popping back " << this->lastelem << std::endl;
				delete this->lastelem;
				this->lastelem = tmp;
				this->length--;
			}
		}
		void	clear() {
			int i = 0;
			while (this->length) {
				std::cout << "clear " << i << ", length = " << length << std::endl;
				pop_back();
				i++;
			}
		}
		size_type	size() const { return this->length; }
		size_type	max_size() const { return (SSIZE_MAX / sizeof(node<T>)); }
		bool empty() const {
			if (this->length > 0)
				return true;
			return false;
		}
	};
}

#endif
