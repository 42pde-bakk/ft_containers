/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Extra.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/26 13:20:35 by peerdb        #+#    #+#                 */
/*   Updated: 2020/09/26 13:22:40 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRA_HPP
# define EXTRA_HPP
# include "Traits.hpp"
# include <cstddef>

namespace ft {
	template<typename Iterator>
	ptrdiff_t distance(Iterator first, Iterator last,
			typename enable_if<is_iterator<typename Iterator::iterator_category>::value, Iterator>::type * = 0) {
		ptrdiff_t dist = 0;
		while (first != last) {
			++dist;
			first++;
		}
		return dist;
	}
	template <class InputIterator, class Distance>
	void advance (InputIterator& it, Distance n,
			typename enable_if<is_iterator<typename InputIterator::iterator_category>::value, InputIterator>::type * = 0) {
		while (n) {
			if (n > 0) {
				++it;
				--n;
			}
			else {
				--it;
				++n;
			}
		}
	}
	template< typename S >
	void	itemswap(S& var1, S& var2) {
		S tmpvar = var1;
		var1 = var2;
		var2 = tmpvar;
	}
}

#endif
