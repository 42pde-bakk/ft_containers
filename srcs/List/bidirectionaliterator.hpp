/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bidirectionaliterator.hpp                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 12:20:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/09/09 17:56:10 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONALITERATOR_HPP
# define BIDIRECTIONALITERATOR_HPP

# include <limits>
# include <memory>
# include <iostream>
# include <cstddef>
# include <cstring>

namespace ft {
	
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
		listIterator	operator++(int) {
			if (this->ptr)
				this->ptr = this->ptr->next;
			return *this;
		}
		listIterator&	operator++() {
			if (this->ptr)
				this->ptr = this->ptr->next;
			return *this;
		}
		listIterator	operator--(int) {
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
		bool	operator==(const listIterator& rhs) const {
			if (this->ptr == rhs.ptr)
				return true;
			return false;
		}
		bool	operator!=(const listIterator& rhs) const {
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
