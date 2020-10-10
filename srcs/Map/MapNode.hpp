/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MapNode.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/28 00:16:51 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/10 16:52:27 by pde-bakk      ########   odam.nl         */
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
		node 	*right;
		
		mapnode(value_type const& val = value_type()) : data(val), parent(0), left(0), right(0) { }
		mapnode(const node& x) : data(x.data), parent(x.parent), left(x.left), right(x.right) {
		}
		~node() {}
		node&	operator=(const node& x) {
			if (this != &x) {
				this->data = x.data;
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
	};
}

#endif
