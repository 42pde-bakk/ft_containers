/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_main.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 21:10:23 by peerdb        #+#    #+#                 */
/*   Updated: 2020/09/27 01:50:43 by peerdb        ########   odam.nl         */
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
	ft::vector<int>::iterator		it = hats.begin();
	ft::vector<int>::iterator		ite = hats.end();
									ite--;
	ft::vector<int>::const_iterator	cit = hats.begin();
	ft::vector<int>::const_iterator	cite = hats.end();
									cite--;
	std::cout << "*it = " << *it << ", *ite = " << *ite << std::endl;
	ft::vector<int>::reverse_iterator		rit = hats.rbegin();
	ft::vector<int>::reverse_iterator		rite = hats.rend();
	ft::vector<int>::const_reverse_iterator	crit = hats.rbegin();
	ft::vector<int>::const_reverse_iterator	crite = hats.rend();
	std::cout << "*rit = " << *rit << ", *rite = " << *rite << std::endl;
	if (it == cit && cit == it)
		std::cout << "equal works" << std::endl;
	std::cout << "first: " << (it != cite) << ", second: " << (cite != it) << std::endl;
	if (it != cite && cite != it)
		std::cout << "unequal works" << std::endl;
	if (it < cite && !(cite < it))
		std::cout << "smaller than works" << std::endl;
	if (it <= ite && !(cite <= it))
		std::cout << "smaller/equal works" << std::endl;
	if (ite > cit && !(cit > ite))
		std::cout << "bigger than works" << std::endl;
	if (cite >= it && !(it >= cite))
		std::cout << "bigger/equal works" << std::endl;
	ite = it;
	if (rit == crit && crit == rit)
		std::cout << "equal works" << std::endl;
	if (rit != crite && crite != rit)
		std::cout << "unequal works" << std::endl;
	if (rit < crite && !(crite < rit))
		std::cout << "smaller than works" << std::endl;
	if (rit <= rite && !(crite <= rit))
		std::cout << "smaller/equal works" << std::endl;
	if (rite > crit && !(crit > rite))
		std::cout << "bigger than works" << std::endl;
	if (crite >= rit && !(rit >= crite))
		std::cout << "bigger/equal works" << std::endl;
	int a = it[2];
	int b = rite[3];
	std::cout << "a: " << a << ", b: " << b << std::endl;
}

int	main() {
	// constructors_test();
	iterators_test();
	// peer();
}
