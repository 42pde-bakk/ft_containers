/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 12:23:59 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/09/07 13:02:50 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP
# include <limits>
# include <memory>
# include <iostream>
# include <cstddef>
# include <cstring>

namespace ft {
	template <typename T>
	class node {
	public:
		T			data;
		node<T>		*next;
		node<T>		*prev; /* Bi-directional list means it has a pointer to the next element and to the previous one */

		node<T>() : data(), next(NULL), prev(NULL) { } /* Default constructor for  */
		node<T>(T data) : data(data), next(NULL), prev(NULL) { } /* Fill constructor */
		node<T>(const node<T>& other) : data(other.data), next(other.next), prev(other.prev) { } /* Copy constructor */
		~node<T>() { } /* Default destructor */
	};

	template < class T, class Category = std::bidirectional_iterator_tag >
	class listIterator {
	private:
		node<T>	*ptr;
	public:
		listIterator() : ptr(NULL) { }
		listIterator(const listIterator& other) {
			*this = other;
		}
		listIterator&	operator=(const listIterator& other) {
			if (this != &other)
				this->ptr = other.ptr;
			return *this;
		}
		~listIterator() { }
		listIterator(node<T> *list) {
			this->ptr = list;
		}
		listIterator&	operator++(int) {
			if (this->ptr)
				this->ptr = this->ptr->next;
			return *this;
		}
		listIterator&	operator++() {
			if (this->ptr)
				this->ptr = this->ptr->next;
			return *this;
		}
		listIterator&	operator--(int) {
			if (this->ptr)
				this->ptr = this->ptr->prev;
			return *this;
		}
		listIterator&	operator--() {
			if (this->ptr)
				this->ptr = this->ptr->prev;
			return *this;
		}
		T&	operator*() {
			return this->ptr->data;
		}
		// T	*operator->() {
		// 	return *this->ptr->data;
		// }
		node<T>	*getptr() {
			return this->ptr;
		}
	};
	
	template < class T, class Alloc = std::allocator<T> >
	class list {
	public:
		typedef T		value_type;
		typedef Alloc	allocator_type;
		typedef T		&reference;
		typedef const T	&const_reference;
		typedef T		*pointer;
		typedef const T	*const_pointer;
		typedef ft::listIterator<T>	iterator;
		// typedef const_iterator;
		// typedef reverse_iterator;
		// typedef const_reverse_iterator;
		typedef ptrdiff_t	difference_type;
		typedef size_t		size_type;
	private:
		node<T>		*head;
		node<T>		*firstelem;
		node<T>		*lastelem;
		node<T>		*tail;
		allocator_type	alloc;
		size_type		length;
	public:
		list(const allocator_type& alloc = allocator_type()) : alloc(alloc) /* Default constructor */
		{
			this->head = new node<T>();
			this->tail = new node<T>();
			this->head->next = this->tail;
			this->tail->prev = this->head;
			this->length = 0;
		}
		~list() {
			this->clear();
			delete this->tail;
			delete this->head;
		}
		iterator	begin() {
			return iterator(this->head->next);
		}
		iterator	end() {
			return iterator(this->tail);
		}
		
		void	push_back(const value_type &val) {
			node<T>	*ptr = new node<T>();
			ptr->next = this->tail;
			ptr->prev = this->tail->prev;
			this->tail->prev->next = ptr;
			this->tail->prev = ptr;
			ptr->data = val;
			this->lastelem = ptr;
			this->length++;
		}
		void	pop_back() {
			if (this->length)
			{
				// if (this->length == 1)
				// {
				// 	this->head->next = this->tail;
				// 	std::cout << "deleting " << tail->prev << std::endl;
				// 	delete this->tail->prev;
				// 	this->tail->prev = this->head;
				// }
				// else
				{
					node<T>	*tmp = this->lastelem->prev;
					tmp->next = this->tail;
					this->tail->prev = tmp;
					delete this->lastelem;
					this->lastelem = tmp;
				}
				this->length--;
			}
		}
		void	clear() {
			while (this->length) {
				pop_back();
				// std::cout << "after popping, length is " << this->getlength() << std::endl;
			}
		}
		size_type	getlength() const { return this->length; }
	};
}

#endif
