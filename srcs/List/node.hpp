/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 12:18:41 by peerdb        #+#    #+#                 */
/*   Updated: 2020/09/14 16:19:02 by peerdb        ########   odam.nl         */
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
		node		*next;
		node		*prev; /* Bi-directional list means it has a pointer to the next element and to the previous one */

		node() : data(), next(NULL), prev(NULL) { } /* Default constructor for  */
		node(T &val) : data(val), next(NULL), prev(NULL) { } /* Fill constructor */
		node(const node &other) : data(other.data), next(other.next), prev(other.prev) { } /* Copy constructor */
		~node() { } /* Default destructor */

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
