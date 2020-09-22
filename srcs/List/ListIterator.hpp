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
# include "../Traits.hpp"

namespace ft {

	template < typename T, class Category = std::bidirectional_iterator_tag >
	class ListIterator {
	private:
		node<T>	*ptr;
	public:
		typedef T			value_type;
		typedef T&			reference;
		typedef T*			pointer;
		typedef node<T>*	node_pointer;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
		typedef bidirectional_iterator_tag iterator_category;
		// typedef ListIterator self_type;

		ListIterator() : ptr(NULL) { }
		ListIterator(node_pointer element) : ptr(element) {}
		ListIterator(const ListIterator& other) {
			std::cout << "what the hoer" << std::endl;
			*this = other;
		}
		ListIterator&	operator=(const ListIterator& other) {
			if (this != &other)
				this->ptr = other.ptr;
			return *this;
		}
		~ListIterator() {}

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
		reference	operator*() {
			return this->ptr->data;
		}
		pointer		operator->() {
			return (&(this->ptr->data));
		}
		bool	operator==(const ListIterator& rhs) const {
			if (this->ptr == rhs.ptr)
				return true;
			return false;
		}
		bool	operator!=(const ListIterator& rhs) const {
			if (this->ptr == rhs.ptr) {
				return false;
			}
			return true;
		}
		node<T>	*getptr() {
			return this->ptr;
		}
		node<T>	*getnext() {
			return this->ptr->next;
		}
		node<T>	*getprev() {
			return this->ptr->prev;
		}
	};
	template < typename T, class Category = std::bidirectional_iterator_tag >
	class ConstListIterator {
	private:
		node<T>	*ptr;
	public:
		typedef T			value_type;
		typedef const T&	reference;
		typedef const T*	pointer;
		typedef node<T>*	node_pointer;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
		typedef bidirectional_iterator_tag iterator_category;
		ConstListIterator() : ptr(NULL) { }
		ConstListIterator(node_pointer element) : ptr(element) {}
		ConstListIterator(const ConstListIterator& other) {
			std::cout << "fuck me" << std::endl;
			*this = other;
		}
		ConstListIterator(const ListIterator<T> &other) {
			std::cout << "fuck" << std::endl;
			*this = other;
			std::cout << "hsdfskdjf" << std::endl;
		}
		ConstListIterator&	operator=(const ConstListIterator& other) {
			if (this != &other)
				this->ptr = other.ptr;
			return *this;
		}
		~ConstListIterator() { }

		ConstListIterator	operator++(int) {
			if (this->ptr)
				this->ptr = this->ptr->next;
			return *this;
		}
		ConstListIterator&	operator++() {
			if (this->ptr)
				this->ptr = this->ptr->next;
			return *this;
		}
		ConstListIterator	operator--(int) {
			if (this->ptr)
				this->ptr = this->ptr->prev;
			return *this;
		}
		ConstListIterator&	operator--() {
			if (this->ptr)
				this->ptr = this->ptr->prev;
			return *this;
		}
		bool	operator==(const ConstListIterator& rhs) const {
			if (this->ptr == rhs.ptr)
				return true;
			return false;
		}
		bool	operator!=(const ConstListIterator& rhs) const {
			if (this->ptr == rhs.ptr)
				return false;
			return true;
		}
		reference	operator*() {
			return (this->ptr->data);
		}
	};

	template < typename T, class Category = std::bidirectional_iterator_tag >
	class RevListIterator : public ListIterator<T> {
	private:
		node<T>	*ptr;
	public:
		typedef T			value_type;
		typedef T&			reference;
		typedef T*			pointer;
		typedef node<T>*	node_pointer;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
		typedef bidirectional_iterator_tag iterator_category;
		// typedef RevListIterator self_type;

		RevListIterator() : ptr(NULL) { }
		RevListIterator(node_pointer element) : ptr(element) {}
		RevListIterator(const RevListIterator& other) {
			*this = other;
		}
		RevListIterator&	operator=(const RevListIterator& other) {
			if (this != &other)
				this->ptr = other.ptr;
			return *this;
		}
		~RevListIterator() { }
		RevListIterator	operator++(int) {
			if (this->ptr)
				this->ptr = this->ptr->prev;
			return *this;
		}
		RevListIterator&	operator++() {
			if (this->ptr)
				this->ptr = this->ptr->prev;
			return *this;
		}
		RevListIterator	operator--(int) {
			if (this->ptr)
				this->ptr = this->ptr->next;
			return *this;
		}
		RevListIterator&	operator--() {
			if (this->ptr)
				this->ptr = this->ptr->next;
			return *this;
		}
	};
	template < typename T, class Category = std::bidirectional_iterator_tag >
	class ConstRevListIterator : public ConstListIterator<T>{
	private:
		node<T>	*ptr;
	public:
		typedef T			value_type;
		typedef const T&	reference;
		typedef const T*	pointer;
		typedef node<T>*	node_pointer;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
		typedef bidirectional_iterator_tag iterator_category;
		ConstRevListIterator() : ptr(NULL) { }
		ConstRevListIterator(node_pointer element) : ptr(element) {}
		ConstRevListIterator(const ConstRevListIterator<T> &other) {
			*this = other;
		}
		ConstRevListIterator(const ConstRevListIterator& other) {
			*this = other;
		}
		ConstRevListIterator&	operator=(const ConstRevListIterator& other) {
			if (this != &other)
				this->ptr = other.ptr;
			return *this;
		}
		~ConstRevListIterator() { }

		ConstRevListIterator	operator++(int) {
			if (this->ptr)
				this->ptr = this->ptr->prev;
			return *this;
		}
		ConstRevListIterator&	operator++() {
			if (this->ptr)
				this->ptr = this->ptr->prev;
			return *this;
		}
		ConstRevListIterator	operator--(int) {
			if (this->ptr)
				this->ptr = this->ptr->next;
			return *this;
		}
		ConstRevListIterator&	operator--() {
			if (this->ptr)
				this->ptr = this->ptr->next;
			return *this;
		}
	};
}

#endif
