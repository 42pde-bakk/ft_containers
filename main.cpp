/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 12:46:40 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/09/17 21:50:34 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "srcs/List/list.hpp"
#include <list>
#include <string>
#include <cstdlib>

void	constants(void)
{
	ft::list<int> myList;
	std::cout << "myList.empty() = " << myList.empty() << std::endl;
	std::cout << "myList.front() = " << myList.front() << std::endl;
	std::cout << "myList.back() = " << myList.back() << std::endl;
	for (int i = 0; i < 20; i++) {
		myList.push_front(i * 7 + 1);
		// std::cout << "added " << i * 7 << std::endl;
	}
	std::cout << "myList.front() = " << myList.front() << std::endl;
	std::cout << "myList.back() = " << myList.back() << std::endl;
	
	const ft::list<int> myConstList(size_t(8), 7);
	ft::list<int>::const_iterator cit = myConstList.begin();
	ft::list<int>::const_iterator cite = myConstList.end();
	while (cit != cite)
	{
		// *cit = 8; // won't compile, because its a const_iterator!
		cit++;
	}
	std::cout << std::endl;
	ft::list<int>::iterator einde = myList.end();
	std::cout << "myList.end() = " << *einde << std::endl;
}

int peer() {
	ft::list<int> l;
	for (int i = 0; i < 8; i++)
		l.push_back(i * 2);
	for (ft::list<int>::iterator it = l.begin(); it != l.end(); it++) {
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
	ft::list<int>::iterator myIt = l.begin();
	for (int i = 0; i < 5; i++)
		myIt++;
	
	for (int i = 0; i < 10; i++)
		l.push_back(i * 3);
	
	std::cout << "*myIt = " << *myIt << std::endl;
	ft::list<int>::iterator tmp = l.insert(myIt, -800);
	std::cout << "tmp = " << *tmp << std::endl;
	l.insert(myIt, (size_t)5, 42);
	ft::list<int> tocopyList((size_t)3, 69);
	l.insert(myIt, tocopyList.begin(), tocopyList.end());
	ft::list<int>::iterator del = l.erase(myIt);
	std::cout << "list.erase() returned " << *del << std::endl;
	for (ft::list<int>::iterator it = l.begin(); it != l.end(); it++)
		std::cout << "*it = " << *it << std::endl;
	ft::list<int>::iterator delrange = l.erase(l.begin(), l.end());
	std::cout << "outcome of delrange = " << *delrange << std::endl;
	// while (l.size())
	// 	l.pop_front();
	// std::cout << "l.size() = " << l.size() << std::endl;
	// std::cout << "l.max_size() = " << l.max_size() << std::endl;
	return 0;
}

void	eraser() {
	ft::list<int> listone((size_t)3, 42);
	// ft::list<int> listtwo((size_t)5, 84);
	ft::list<int>::iterator delrange = listone.erase(listone.begin(), listone.end());
	std::cout << "outcome of delrange = " << *delrange << std::endl;
}

void	swapper() {
	ft::list<int> first((size_t)10, 42);
	ft::list<int> second((size_t)2, 200);
	first.swap(second);
	for (ft::list<int>::iterator it = first.begin(); it != first.end(); it++) {
		std::cout << "swapped first *it: " << *it << std::endl;
	}
	for (ft::list<int>::iterator it = second.begin(); it != second.end(); it++) {
		std::cout << "swapped second *it: " << *it << std::endl;
	}
}

void	resizer() {
	ft::list<int> first((size_t)10, 42);
	ft::list<int> second((size_t)2, 200);
	first.resize(5);
	second.resize(5);
	for (ft::list<int>::iterator it = first.begin(); it != first.end(); it++) {
		std::cout << "resized first *it: " << *it << std::endl;
	}
	for (ft::list<int>::iterator it = second.begin(); it != second.end(); it++) {
		std::cout << "resized second *it: " << *it << std::endl;
	}
	if (first == second)
		std::cout << "yes" << std::endl;
}

int main() {
	srand(time(0));
	// peer();
	// constants();
	// eraser();
	// swapper();
	resizer();
	// system("leaks containers.out");
	//thx djevayo for the pr
}
