/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 12:46:40 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/09/14 22:00:46 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "srcs/List/list.hpp"
#include <list>
#include <string>

int fakemain() {
	ft::list<int> l((size_t)8, 42);
	ft::list<std::string> s(size_t(10), "anker");

	for (int i = 0; i < 10; i++)
		l.push_front(i * 3);

	// ft::list<int> lrange(l.begin(), l.end());

	// for (ft::list<int>::iterator lrangeit = lrange.begin(); lrangeit != lrange.end(); lrangeit++) {
	// 	std::cout << "*lrangeit = " << *lrangeit << std::endl;
	// }
	ft::list<std::string>::const_iterator cit = s.begin();
	std::cout << "*cit: " << *cit << std::endl;
	cit++;
	std::cout << "*cit: " << *cit << std::endl;
	// ft::list<int>::iterator it = l.begin();
	// while (it != l.end()) {
	// 	std::cout << "*it: " << *it << std::endl;
	// 	it++;
	// }
	while (l.size())
		l.pop_front();
	std::cout << "l.size() = " << l.size() << std::endl;
	std::cout << "l.max_size() = " << l.max_size() << std::endl;
	return 0;
}

int main() {
	fakemain();
	// system("leaks containers.out");
	//thx djevayo for the pr
}
