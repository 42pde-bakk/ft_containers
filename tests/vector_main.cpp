/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_main.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-bakk <pde-bakk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 21:10:23 by peerdb            #+#    #+#             */
/*   Updated: 2022/04/19 20:06:50 by pde-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <sys/time.h>
#include <cstring> // for strcmp
#include <stddef.h>
#include <stdlib.h> // for system()

# if defined(unix) || defined(__unix__) || defined(__unix)
#  define LINUX 1
# else
#  define LINUX 0
# endif

size_t begintime;
size_t endtime;
struct timeval	tv;

template< typename T >
void	print_container_content(ft::vector<T> &vec, std::string name = "container") {
	std::cout << name << " contains:";
	for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << ' ' << *it;
	std::cout << " $" << std::endl;
}

template< typename T >
void	reverse_print_container_content(ft::vector<T> &vec, const std::string& name = "container") {
	std::cout << name << " contains:";
	for (ft::vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); it++)
		std::cout << ' ' << *it;
	std::cout << " $" << std::endl;
}

void	constructors_test() {
	int i = 8;
	ft::vector<int> def;
	print_container_content(def, "default constructor");
	ft::vector<int>	fill(i, 42);
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
	ft::vector<int>::iterator test = 5 + it;
	std::cout << "*test = " << *test << std::endl;
	std::cout << "*it = " << *it << ", *ite = " << *ite << std::endl;
	ft::vector<int>::const_iterator	cit = hats.begin();
	ft::vector<int>::const_iterator	cite = hats.end();
		cite--;
	std::cout << "sfhkdsfh" << std::endl;
	std::cout << "*cit = " << *cit << ", *cite = " << *cite << std::endl;
	ft::vector<int>::reverse_iterator		rit = hats.rbegin();
	ft::vector<int>::reverse_iterator		rite = hats.rend();
	(void)rite;
	ft::vector<int>::const_reverse_iterator	crit = hats.rbegin();
	ft::vector<int>::const_reverse_iterator	crite = hats.rend();
	std::cout << "regular iterators:" << std::endl;
	std::cout << "reg: operator==(): " << std::boolalpha << (it == cit) << ", " << (cit == it) << std::endl;
	std::cout << "reg: operator!=(): " << std::boolalpha << (it != cite) << ", " << (cite != it) << std::endl;
	std::cout << "reg: operator<(): " << std::boolalpha << (it < cite) << ", " << (cite < it) << std::endl;
	std::cout << "reg: operator<=(): " << std::boolalpha << (it <= cite) << ", " << (cite <= it) << std::endl;
	std::cout << "reg: operator>(): " << std::boolalpha << (it > cite) << ", " << (cite > it) << std::endl;
	std::cout << "reg: operator>=(): " << std::boolalpha << (it >= cite) << ", " << (cite >= it) << std::endl;
	ite = it;
	std::cout << "*it++ gives: " << *it++ << ", it now is " << *it << std::endl;
	std::cout << "*++it gives: " << *++it << ", it now is " << *it << std::endl;
	std::cout << "*rit++ gives: " << *rit++ << ", it now is " << *rit << std::endl;
	std::cout << "*++rit gives: " << *++rit << ", it now is " << *rit << std::endl;
	std::cout << "*it-- gives: " << *it-- << ", it now is " << *it << std::endl;
	std::cout << "*--it gives: " << *--it << ", it now is " << *it << std::endl;
	std::cout << "*rit-- gives: " << *rit-- << ", it now is " << *rit << std::endl;
	std::cout << "*--rit gives: " << *--rit << ", it now is " << *rit << std::endl;
	// *cit += 10;
	// *crit += 10;
	std::cout << "reverse iterators:" << std::endl;
	std::cout << "reverse: operator==(): " << std::boolalpha << (rit == crit) << ", " << (crit == rit) << std::endl;
	std::cout << "reverse: operator!=(): " << std::boolalpha << (rit != crite) << ", " << (crite != rit) << std::endl;
	std::cout << "reverse: operator<(): " << std::boolalpha << (rit < crite) << ", " << (crite < rit) << std::endl;
	std::cout << "reverse: operator<=(): " << std::boolalpha << (rit <= crite) << ", " << (crite <= rit) << std::endl;
	std::cout << "reverse: operator>(): " << std::boolalpha << (rit > crite) << ", " << (crite > rit) << std::endl;
	std::cout << "reverse: operator>=(): " << std::boolalpha << (rit >= crite) << ", " << (crite >= rit) << std::endl;
	std::cout << "dereference operator on iterators: " << it[2] << ", " << cit[3] << ", " << rit[4] << ", " << crit[5] << " WORK!" << std::endl;
}

void	capacity_test() {
	ft::vector<int>	papajohns;

	std::cout << "papajohns.empty(): " << std::boolalpha<< papajohns.empty() << std::endl;
	for (int i = 0; i < 10; ++i)
		papajohns.push_back(i);
	std::cout << "papajohns.size(): " << papajohns.size() << std::endl;
	std::cout << "papajohns.max_size(): " << papajohns.max_size() << std::endl;
	std::cout << "papajohns.capacacity(): " << papajohns.capacity() << std::endl;
	std::cout << "papajohns.empty(): " << std::boolalpha << papajohns.empty() << std::endl;

}

void	element_access_test() {
	ft::vector<int> kokkita;

	for (int i = 0; i < 10; ++i)
		kokkita.push_back(-3 * i);

	const ft::vector<int> constkita(kokkita);
	std::cout << "kokkita[3]: " << kokkita[3] << ", constkita[4]: " << constkita[4] << std::endl;
	try {
		std::cout << "the [] operator does not check if the input value is inbounds of the array" << std::endl;
		std::cout << "the function .at() does check and throws an exception if it is out of bounds, here I'll show you:" << std::endl;
		std::cout << "kokkita.at(13): " << kokkita.at(13) << std::endl;
	}
	catch (std::out_of_range& e) {
		std::cout << "See? it threw an exception" << std::endl;
		// I didnt print e.what(), because diff will see it as different (and wrong) sadface
	}
	std::cout << "kokkita.front() = " << kokkita.front() << ", constkita.front() = " << constkita.front() << std::endl;
	std::cout << "kokkita.back() = " << kokkita.back() << ", constkita.back() = " << constkita.back() << std::endl;
	// std::cout << "kokkita[" << 812039 << "]: " << kokkita[812039] << std::endl;
}

void	modifiers_test() {

	ft::vector<int>	tocopy;
	for (int i = 0; i < 14; ++i)
		tocopy.push_back(14 * i);
	ft::vector<int> wap;
	wap.assign(5, 69);
	print_container_content(wap, "after the first assign, wapwap");
	wap.assign(tocopy.begin(), tocopy.end());
	print_container_content(wap, "and after the second, wapwap");
	while (!(tocopy.empty()))
		tocopy.pop_back();
	print_container_content(wap, "wap");
	ft::vector<int>::iterator it = wap.begin() + 2;
	std::cout << "*it = " << *it << std::endl;
	wap.insert(it, 2, 800);
	it = wap.insert(wap.begin() + 1, 9999);
	std::cout << "returned iterator from insert gives " << *it << std::endl;
	tocopy.insert(tocopy.begin(), wap.begin(), wap.end() - 5);
	print_container_content(wap, "after insert, wap");
	
	it = tocopy.erase(tocopy.begin());
	std::cout << "erasing returns iterator to " << *it << std::endl;
	print_container_content(tocopy, "after insert and erasing, tocopy");
	it = tocopy.erase(tocopy.begin(), tocopy.begin() + 6);
	std::cout << "erasing returns iterator to " << *it << std::endl;
	
	print_container_content(tocopy, "after insert and erasing, tocopy");

}

void	relational_operators_test() {
	ft::vector<int>	a;
	ft::vector<int>	b;
	for (int i = 0; i < 8; i++) {
		a.push_back(i);
		b.push_back(i);
	}
	std::cout << "this one should return 1: " << (a == b) << ", and this one 0: " << (a != b) << std::endl;
	std::cout << (a < b) << (b < a) << (a <= b) << (b <= a) << std::endl;
	a.push_back(0);
	b.push_back(5);
	std::cout << "now vice versa, should return 0: " << (a == b) << ", and this one 1: " << (a != b) << std::endl;
	std::cout << (a < b) << (b < a) << (a <= b) << (b <= a) << std::endl;
}

void	stl_test() {
	// checking if I can also assign items from STL iterators
	ft::vector<int>		wap;
	std::vector<int>	stl;
	for (int i = 0; i < 12; i++)
		stl.push_back(i * 4);
	wap.assign(stl.begin(), stl.end());
	print_container_content(wap, "wap");
	reverse_print_container_content(wap, "wap");
}

void	sam() {
	ft::vector<int>	sam(8, 123);
	// int ret = sam.end() - sam.begin();
	int ret = sam.end() - sam.begin();
	std::cout << "ret = " << ret << std::endl;
	sam.resize(5);
	std::cout << "vector capacity: " << sam.capacity() << std::endl;
	std::cout << "vector size: " << sam.size() << std::endl;
	std::cout << "vector front: " << sam.front() << std::endl;
	std::cout << "vector back: " << sam.back() << std::endl;
	sam.resize(8, 100);
	std::cout << "vector capacity: " << sam.capacity() << std::endl;
	std::cout << "vector size: " << sam.size() << std::endl;
	std::cout << "vector front: " << sam.front() << std::endl;
	std::cout << "vector back: " << sam.back() << std::endl;
	sam.resize(12389);
	std::cout << "vector capacity: " << sam.capacity() << std::endl;
	std::cout << "vector size: " << sam.size() << std::endl;
	std::cout << "vector front: " << sam.front() << std::endl;
	std::cout << "vector back: " << sam.back() << std::endl;
}

void	testVstresstest()
{
	std::cout << "+-------------------+" << std::endl;
	std::cout << "| Vector Stress test|" << std::endl;
	std::cout << "+-------------------+" << std::endl << std::endl;
	ft::vector<int>		stressVec;

	stressVec.reserve(60000);
	for (size_t i = 0; i < 60000; i++)
		stressVec.insert(stressVec.end(), 1, i * 3);
	// print_container_content(stressVec, "stressVec");
	// printVector(stressVec);
}


int	main(int argc, char **argv) {
	if (argc == 2 && strcmp(argv[1], "time")) {
		gettimeofday(&tv, NULL);
		begintime = tv.tv_usec;
	}
	//  stl_test();
	//  constructors_test();
	//  iterators_test();
	//  capacity_test();
	//  element_access_test();
	//  modifiers_test();
	//  relational_operators_test();
	 testVstresstest();
	// sam();
	if (argc == 2 && strcmp(argv[1], "time")) {
		gettimeofday(&tv, NULL);
		endtime = tv.tv_usec;
		std::cout << "Time elapsed in total! = " << endtime - begintime << " nanoseconds" << std::endl;
	}
	if (argc == 3 && strcmp(argv[2], "leaks") == 0 && !LINUX) {
		int a = system("leaks containers.out | grep \"total leaked bytes\" >&2");
		(void)a;
	}
	return 0;
}
