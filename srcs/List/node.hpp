/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 12:18:41 by peerdb        #+#    #+#                 */
/*   Updated: 2020/09/09 17:47:55 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

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

		node	operator=(const node& rhs) {
			this->data = rhs.data;
			this->next = rhs.next;
			this->prev = rhs.prev;
			return *this;
		}
		bool	operator==(const node& rhs) const {
			if (this->data != rhs.data || this->next != rhs.next || this->prev != rhs.prev)
				return false;
			return true;
		}
		bool	operator!=(const node& rhs) const {
			if (this->data == rhs.data || this->next == rhs.next || this->prev == rhs.prev)
				return false;
			return true;
		}
	};
}

#endif
