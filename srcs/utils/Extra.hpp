/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Extra.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/26 13:20:35 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/20 00:55:32 by peerdb        ########   odam.nl         */
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
			++first;
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
	template<class value_type>
	const value_type&	min(const value_type& a, const value_type& b) {
		return (a < b ? a : b);
	}

	template<class value_type>
	const value_type&	max(const value_type& a, const value_type& b) {
		return (a < b ? b : a);
	}

	template<typename value_type>
	struct less: public std::binary_function<value_type, value_type, bool> {
		bool	operator()(const value_type& x, const value_type& y) const {
			return (x < y);
		}
	};

	template<typename value_type>
	bool	is_equal(const value_type& a, const value_type& b) {
		return (a == b);
	}
	template<typename value_type>
	bool	less_than(const value_type& a, const value_type& b) {
		return (a < b);
	}
	template<typename value_type>
	bool	more_than(const value_type& a, const value_type& b) {
		return (a > b);
	}

	template <class Iterator1, class Iterator2>
	bool equal(Iterator1 first1, Iterator1 last1, Iterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

//	template <typename Compare, typename value_type>
//	class value_compare // ngl, I yoinked this class straight off http://www.cplusplus.com/reference/map/map/value_comp/
//	{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
////		friend class MapBase;
//	protected:
//		Compare comp;
//		explicit value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
//	public:
//		bool operator() (const value_type& x, const value_type& y) const {
//			return comp(x.first, y.first);
//		}
//	};
//	template<typename Compare, typename value_type>
//	class set_compare // ngl, I yoinked this class straight off http://www.cplusplus.com/reference/map/map/value_comp/
//	{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
////		friend class MapBase;
//	protected:
//		Compare comp;
//		explicit set_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
//	public:
//		template<typename iterator>
//		bool operator() (const value_type& x, const iterator& y) const {
//			return comp(x, *y);
//		}
//		template<typename iterator>
//		bool operator() (const iterator& x, const value_type& y) const {
//			return comp(*x, y);
//		}
//	};

} // ft namespace

#endif
