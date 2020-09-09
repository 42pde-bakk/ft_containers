/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 12:46:40 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/09/07 13:53:56 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "list.hpp"

int fakemain() {
	ft::list<int> l;
	l.push_back(8);
	l.push_back(42);
	l.push_back(12387);
	ft::list<int>::iterator it = l.begin();
	// std::cout << "iterator = " << &it << std::endl;
	it++;
	it--;
	++it;
	--it;
	for (int i = 0; i < 3; i++) {
		std::cout << "*it = " << *it << std::endl;
		it++;
	}
	std::cout << l.getlength() << std::endl;
	return 0;
}

int main() {
	fakemain();
	// system("leaks containers.out");
	//thx djevayo for the pr
}
