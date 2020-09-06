/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 12:46:40 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/09/06 16:21:41 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "list.hpp"

int fakemain() {
	ft::list<int> l;
	l.push_back(8);
	l.push_back(8);
	l.push_back(8);
	std::cout << l.getlength() << std::endl;
	return 0;
}

int main() {
	fakemain();
	system("leaks containers.out");
}
