/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_main.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 21:10:23 by peerdb        #+#    #+#                 */
/*   Updated: 2020/09/26 18:26:15 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/Vector/Vector.hpp"
#include <vector>
#include <string>
#include <iostream>

template< typename T >
void	print_container_content(ft::vector<T> &vec, std::string name) {
	std::cout << name << " contains:";
	for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << ' ' << *it;
	std::cout << " $" << std::endl;
}

void	constructors_test() {
	ft::vector<int> def;
	print_container_content(def, "default constructor");
	ft::vector<int>	fill(8, 42);
	for (int i = 0; i < 8; i++)
		fill.push_back( i );
	print_container_content(fill, "fill constructor");
	ft::vector<int> range(fill.begin(), fill.end());
	print_container_content(range, "range constructor");
	ft::vector<int> copy(range);
	print_container_content(copy, "copy constructor");
	copy = def;
	print_container_content(copy, "assignation operator");
}

void	iterators_test() {
	ft::vector<int> hats;
	for (int i = 0; i < 72; i++)
		hats.push_back(i * 10);
	ft::vector<int>::iterator it = hats.begin();
	ft::vector<int>::const_iterator ite = hats.end();
	std::cout << "*it = " << *it << ", *ite = " << *ite << std::endl;
	ft::vector<int>::reverse_iterator rit = hats.rbegin();
	ft::vector<int>::reverse_iterator rite = hats.rend();
	std::cout << "*rit = " << *rit << ", *rite = " << *rite << std::endl;
	// if (it != ite)
	ite = it;
	if (it == ite)
		std::cout << "equal works" << std::endl;
	if (it != ite)
		std::cout << "unequal works" << std::endl;
	if (it < ite)
		std::cout << "smaller than works" << std::endl;
	if (it <= ite)
		std::cout << "smaller/equal works" << std::endl;
	if (it > ite)
		std::cout << "bigger than works" << std::endl;
	if (it >= ite)
		std::cout << "bigger/equal works" << std::endl;

	if (ite == it)
		std::cout << "equal works" << std::endl;
	if (ite != it)
		std::cout << "unequal works" << std::endl;
	if (ite < it)
		std::cout << "smaller than works" << std::endl;
	if (ite <= it)
		std::cout << "smaller/equal works" << std::endl;
	if (ite > it)
		std::cout << "bigger than works" << std::endl;
	if (ite >= it)
		std::cout << "bigger/equal works" << std::endl;
}

int	main() {
	// constructors_test();
	iterators_test();
	// peer();
}
