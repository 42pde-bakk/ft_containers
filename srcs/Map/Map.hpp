/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Map.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/27 23:49:18 by peerdb        #+#    #+#                 */
/*   Updated: 2020/09/28 00:16:47 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <limits>
# include <memory>
# include <iostream>
# include <cstddef>
# include <cstdlib>
# include <cstring>
# include <climits>
# include <string>
# include "MapNode.hpp"
# include "../Iterators/BidirectionalIterator.hpp"
# include "../Traits.hpp"
# include "../Extra.hpp"

# if defined(unix) || defined(__unix__) || defined(__unix)
#  define PEER_MAX SSIZE_MAX
# else
#  define PEER_MAX SIZE_T_MAX
# endif

template <class T> struct less : binary_function <T,T,bool> {
  bool operator() (const T& x, const T& y) const {return x<y;}
};

namespace ft {
template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
	class map {
		typedef Key							key_type;
		typedef T							mapped_type;
		typedef std::pair<const Key, T>		value_type;
		typedef	Compare						key_compare;
		typedef Alloc						allocator_type;
		typedef	value_type&					reference;
		typedef	const value_type&			const_reference;
		typedef	value_type*					pointer;
		typedef	const value_type*			const_pointer;
		typedef BidirectionalIterator<value_type>				iterator;
		typedef ConstBidirectionalIterator<const value_type>	const_iterator;
		typedef RevBidirectionalIterator<value_type>			reverse_iterator;
		typedef ConstRevBidirectionalIterator<const value_type>	const_reverseiterator;
		typedef	ptrdiff_t	difference_type;
		typedef	size_t		size_type;
	};
	
}


#endif
