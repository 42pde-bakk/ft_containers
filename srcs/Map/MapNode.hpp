/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MapNode.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/28 00:16:51 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/09 18:17:01 by pde-bakk      ########   odam.nl         */
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
# include "../Iterators/BidirectionalIterator.hpp"
# include "../Traits.hpp"
# include "../Extra.hpp"

namespace ft {
	template <typename T, class C>
	class mapnode {
	public:
		typedef T	value_type;
		typedef	T&	reference;
		typedef	T*	pointer;
		typedef	C	key_compare;
		typedef	const pointer	const_pointer;
		typedef const reference	const_reference;
		
		value_type	data;
		mapnode		*parent;
		mapnode		*left;
		mapnode 	*right;
		
		mapnode(value_type const& val = value_type()) : data(val), parent(0), left(0), right(0) { }
		mapnode(const node& x) {
			*this = x;
		}
		~mapnode() {}
		mapnode&	operator=(const mapnode& x) {
			if (this != &x) {
				this->data = x.data;
				this->parent = x.parent;
				this->left = x.left;
				this->right = x.right;
			}
			return *this;
		}
		bool	operator==(const mapnode& other);
	};
}

#endif
