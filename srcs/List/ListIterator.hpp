/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ListIterator.hpp                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 12:20:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/09/10 17:33:03 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ListIterator_HPP
# define ListIterator_HPP

# include <limits>
# include <memory>
# include <iostream>
# include <cstddef>
# include <cstring>

namespace ft {
	
	template < typename T, class Category = std::bidirectional_iterator_tag >
	class ListIterator {
	private:
		node<T>	*ptr;
	public:
		// typedef T value_type;
		// typedef R reference;
		// typedef P pointer;
		// typedef N node_pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		// typedef std::bidirectional_iterator_tag iterator_category;
		// typedef ListIterator self_type;

		ListIterator() : ptr(NULL) { }
		// ListIterator(node_pointer element) : ptr(element) {}
		ListIterator(const ListIterator& other) {
			*this = other;
		}
		ListIterator&	operator=(const ListIterator& other) {
			if (this != &other)
				this->ptr = other.ptr;
			return *this;
		}
		~ListIterator() {}

		ListIterator(node<T> *element) {
			this->ptr = element;
			// std::cout << "constructor with node<T> *list" << std::endl;
		}	
		ListIterator	operator++(int) {
			if (this->ptr)
				this->ptr = this->ptr->next;
			return *this;
		}
		ListIterator&	operator++() {
			if (this->ptr)
				this->ptr = this->ptr->next;
			return *this;
		}
		ListIterator	operator--(int) {
			if (this->ptr)
				this->ptr = this->ptr->prev;
			return *this;
		}
		ListIterator&	operator--() {
			if (this->ptr)
				this->ptr = this->ptr->prev;
			return *this;
		}
		T&	operator*() {
			return this->ptr->data;
		}
		bool	operator==(const ListIterator& rhs) const {
			if (this->ptr == rhs.ptr)
				return true;
			return false;
		}
		bool	operator!=(const ListIterator& rhs) const {
			// std::cout << "lhs: " << (*this).ptr << ", rhs: " << rhs.ptr << std::endl;
			if (this->ptr == rhs.ptr) {
				return false;
			}
			return true;
		}
		// T	*operator->() {
		// 	return *this->ptr->data;
		// }
		node<T>	*getptr() {
			return this->ptr;
		}
	};
}

#endif
