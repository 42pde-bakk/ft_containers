/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MapNode.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/28 00:16:51 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/11 16:13:37 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPNODE_HPP
# define MAPNODE_HPP

# include <limits>
# include <memory>
# include <iostream>
# include <cstddef>
# include <cstdlib>
# include <cstring>
# include <climits>
# include <string>
// # include "../Iterators/BidirectionalIterator.hpp"
# include "../Traits.hpp"
# include "../Extra.hpp"

namespace ft {
	template <typename T, class C>
	class node {
	public:
		typedef T			value_type;
		typedef	T&			reference;
		typedef const T&	const_reference;
		typedef	T*			pointer;
		typedef	const T*	const_pointer;
		typedef	C			key_compare;
		
		value_type	data;
		node		*parent;
		node		*left;
		node 	    *right;

        node(value_type const& val = value_type()) : data(val), parent(0), left(0), right(0) { }
        node(const node& x) : data(x.data), parent(x.parent), left(x.left), right(x.right) {
		}
		~node() {}
		node&	operator=(const node& x) {
			if (this != &x) {
				this->data = x.data; //fuck
				this->parent = x.parent;
				this->left = x.left;
				this->right = x.right;
			}
			return *this;
		}
		bool	operator==(const node& other) {
			return (this->data == other.data);
		}
		bool	operator!=(const node& other) {
			return (this->data != other.data);
		}
		bool	operator>(const node& other) {
			return (this->data > other.data);
		}
		bool	operator<(const node& other) {
			return (this->data < other.data);
		}
		bool 	operator<=(const node& other) {
        	return (this->data <= other.data);
        }
        bool 	operator>=(const node& other) {
        	return (this->data >= other.data);
        }
		node*   getnext() {
        	node* it(this);
        	if (it->right) {
        		it = it->right;
        		while (it->left)
        			it = it->left;
        	}
        	else while (it->data <= this->data)
        			it = it->parent;
        	return (it);
        }
        node*   getprevious() {
	        node* it(this);
	        if (it->left) {
		        it = it->left;
		        while (it->right)
			        it = it->right;
	        }
	        else while (it->data >= this->data)
					it = it->parent;
	        return (it);
        }
	};
}

#endif
