/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Traits.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 22:07:27 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/19 18:08:01 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAITS_HPP
# define TRAITS_HPP
namespace ft {

template <bool B, class T = void>
struct enable_if
{
};
template <class T>
struct enable_if<true, T>
{
	typedef T type;
};

template <bool is_iterator, typename T>
struct iterator_result
{
	typedef T type;
	static const bool value = is_iterator;
};

template <typename>
struct iterator_check : public iterator_result<false, bool>
{
};

template <>
struct iterator_check<std::random_access_iterator_tag>
	: public iterator_result<true, std::random_access_iterator_tag>
{
};

template <>
struct iterator_check<std::bidirectional_iterator_tag>
	: public iterator_result<true, std::bidirectional_iterator_tag>
{
};

template <>
struct iterator_check<std::forward_iterator_tag>
	: public iterator_result<true, std::forward_iterator_tag>
{
};

template <>
struct iterator_check<std::input_iterator_tag>
	: public iterator_result<true, std::input_iterator_tag>
{
};

template <typename T>
struct is_iterator : public iterator_check<T>
{
};

} // namespace ft

#endif
