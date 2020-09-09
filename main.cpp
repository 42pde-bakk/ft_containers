/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 12:46:40 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/09/09 21:03:41 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "srcs/List/list.hpp"
#include <list>

int fakemain() {
	ft::list<int> l(8, 42);
	for (int i = 0; i < 10; i++)
		l.push_front(i * 3);
	std::cout << "aftr constr" << std::endl;
	ft::list<int> lrange(l.begin(), l.end());
	std::cout << "aftr constr" << std::endl;
	for (ft::list<int>::iterator lrangeit = lrange.begin(); lrangeit != lrange.end(); lrangeit++) {
		std::cout << "*lrangeit = " << *lrangeit << std::endl;
	}
	ft::list<int>::iterator it = l.begin();
	int i = 0;
	while (it != l.end()) {
		// *it *= i;
		std::cout << "*it: " << *it << std::endl;
		i++;
		it++;
	}
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
