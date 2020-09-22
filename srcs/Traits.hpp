/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Traits.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/09 22:07:27 by peerdb        #+#    #+#                 */
/*   Updated: 2020/09/22 16:29:29 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAITS_HPP
# define TRAITS_HPP
namespace ft
{

// struct random_access_iterator_tag
// {
// };

struct bidirectional_iterator_tag
{
};

// struct forward_iterator_tag
// {
// };

// struct input_iterator_tag
// {
// };

// struct output_iterator_tag
// {
// };

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

// template <>
// struct iterator_check<random_access_iterator_tag>
// 	: public iterator_result<true, random_access_iterator_tag>
// {
// };

template <>
struct iterator_check<std::bidirectional_iterator_tag>
	: public iterator_result<true, std::bidirectional_iterator_tag>
{
};

// template <>
// struct iterator_check<forward_iterator_tag>
// 	: public iterator_result<true, forward_iterator_tag>
// {
// };

// template <>
// struct iterator_check<input_iterator_tag>
// 	: public iterator_result<true, input_iterator_tag>
// {
// };

template <typename T>
struct is_iterator : public iterator_check<T>
{
};

} // namespace ft

#endif
