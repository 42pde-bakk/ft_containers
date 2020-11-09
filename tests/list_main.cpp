/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_main.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 12:46:40 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/11/06 16:49:36 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "List.hpp"
#include <iostream>
#include <list>
#include <string>
#include <cstdlib>
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

template<typename T>
void	print_container_content(ft::list<T>& l, const std::string& name = "container") {
	std::cout << name << " contains:";
	for (typename ft::list<T>::iterator it = l.begin(); it != l.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

void	constructors_test() {
	ft::list<int>	defaultList; // default constructor makes an empty list
	print_container_content(defaultList, "defaultList");
	ft::list<int>	fillList(5, -10); // fill constructor makes 5 elements with value -10
	print_container_content(fillList, "fillList");

	for (int i = 0; i < 5; i++)
		defaultList.push_front(i * 4);
	ft::list<int>::iterator	advance_it = defaultList.begin();
	ft::advance(advance_it, 3);
	ft::list<int>	rangeList(defaultList.begin(), advance_it); // range constructor takes a range of 2 iterators
	print_container_content(rangeList, "rangeList");

	ft::list<int>	copyList(rangeList);
	print_container_content(copyList, "copyList");
	copyList = defaultList;
	print_container_content(copyList, "copyList");
	std::cout << std::endl;
}

void	iterators_test() {
	ft::list<int> hats;
	for (int i = 0; i < 12; ++i)
		hats.push_back(i);
	ft::list<int>::iterator it = hats.begin(), ite = hats.end();
	ft::list<int>::const_iterator cit(it), cite(ite);
	ft::list<int>::reverse_iterator rit = hats.rbegin(), rite(it);
	ft::list<int>::const_reverse_iterator crit(rit), crite(it);
	std::cout << "regular operator==(): " << std::boolalpha << (it == ite) << ", " << (it == cit) << ", " << (it == cite) << ", " << (cite == cit) << ", " << (cite == ite) << std::endl;
	std::cout << "regular operator!=(): " << std::boolalpha << (it != ite) << ", " << (it != cit) << ", " << (it != cite) << ", " << (cite != cit) << ", " << (cite != ite) << std::endl;
	std::cout << "reverse operator==(): " << std::boolalpha << (rit == rite) << ", " << (rit == crit) << ", " << (rit == crite) << ", " << (crite == crit) << ", " << (crite == rite) << std::endl;
	std::cout << "reverse operator!=(): " << std::boolalpha << (rit != rite) << ", " << (rit != crit) << ", " << (rit != crite) << ", " << (crite != crit) << ", " << (crite != rite) << std::endl;

}

void	capacity_test_element_access() {
	ft::list<std::string> mylist;
	std::cout << "Boolean whether mylist is empty or not: " << std::boolalpha << mylist.empty() << std::endl;
	std::string	strings[] = { "kissahomie", "pogchamp" , "Queen", "Yaas" };
	for (int i = 0; i < 4 ; i++)
		mylist.push_front(strings[i]);
	std::cout << "Boolean whether mylist is empty or not: " << std::boolalpha << mylist.empty() << std::endl;
	std::cout << "mylist.size() = " << mylist.size();
//	std::cout << ", and mylist.max_size() = " << mylist.max_size();
	std::cout << std::endl;

	std::cout << "mylist.front() = " << mylist.front() << std::endl;
	std::cout << "mylist.back() = " << mylist.back() << std::endl << std::endl;
}

void	modifiers_test() {
	ft::list<int>	mylist;
	mylist.assign(23, 7);
	print_container_content(mylist, "mylist");

	ft::list<int>	otherlist(12, 23897);
	mylist.assign(otherlist.begin(), otherlist.end());
	print_container_content(mylist, "mylist");
	for (int i = 0; i < 3; i++)
		otherlist.push_front(0);
	for (int i = 0; i < 3; i++)
		otherlist.push_back(999);
	print_container_content(otherlist, "otherlist");
	for (int i = 0; i < 14; i++)
		otherlist.pop_front();
	print_container_content(otherlist, "otherlist");
	for (int i = 0; i < 3; i++)
		otherlist.pop_back();
	print_container_content(otherlist, "otherlist");

	otherlist.insert(otherlist.end(), -42);
	otherlist.insert(otherlist.end(), 3, 89);
	otherlist.insert(otherlist.end(), mylist.begin(), mylist.end());
	print_container_content(otherlist, "otherlist");

	otherlist.erase(otherlist.begin());
	ft::list<int>::iterator it = otherlist.begin();
	ft::advance(it, 10);
	otherlist.erase(otherlist.begin(), it);
	print_container_content(otherlist, "otherlist");
	otherlist.swap(mylist);
	std::cout << std::endl << "After swapping lists:" << std::endl;
	print_container_content(otherlist, "otherlist");
	print_container_content(mylist, "mylist");
	mylist.resize(8);
	otherlist.resize(8);
	std::cout << std::endl << "After resizing both my lists to size 8:" << std::endl;
	print_container_content(otherlist, "otherlist");
	print_container_content(mylist, "mylist");
	mylist.clear();
	otherlist.clear();
	std::cout << std::endl << "After clearing my lists:" << std::endl;
	print_container_content(otherlist, "otherlist");
	print_container_content(mylist, "mylist");
	std::cout << std::endl;
}

bool single_digit (const int& value) { return (value < 10); }

void	operations_test() {
	ft::list<int>	splicelist1(4, 0);
	ft::list<int>	splicelist2;
	for (int i = 0; i < 4; i++)
		splicelist2.push_back(i * 4 + 1);
	ft::list<int>	splicelist3(4, 69);
	ft::list<int>::iterator it = splicelist3.begin();
	ft::advance(it, 2);
	ft::list<int>	mylist;
	for (int i = 0; i < 10; i++)
		mylist.push_back(i);
	mylist.splice(mylist.begin(), splicelist1);
	mylist.splice(mylist.begin(), splicelist2, splicelist2.begin());
	mylist.splice(mylist.begin(), splicelist3, splicelist3.begin(), splicelist3.end());
	print_container_content(splicelist1, "splicelist1");
	print_container_content(splicelist2, "splicelist2");
	print_container_content(splicelist3, "splicelist3");
	print_container_content(mylist, "mylist");
	mylist.remove(69);
	mylist.remove_if(single_digit);
	print_container_content(mylist, "mylist");
	std::cout << std::endl;
	std::cout << "end of operations_test()" << std::endl;
}

void	operations_test2() {
	ft::list<int>	mylist;
	for (int i = 0; i < 20; i++) {
		if (i % 3 == 0 || i % 5 == 0)
			mylist.push_back(0);
		else
			mylist.push_back(i);
	}
	ft::list<int>	myotherlist;
	for (int i = 0; i < 20; i++)
		myotherlist.push_back(i);
	print_container_content(mylist, "mylist");
	mylist.unique();
	print_container_content(mylist, "mylist");
	mylist.sort();
	print_container_content(mylist, "Mylist");
	print_container_content(myotherlist, "My Other list");
	mylist.merge(myotherlist);
	mylist.reverse();
	print_container_content(mylist, "mylist");
	std::cout << std::endl;
}

void	relational_operators() {
	ft::list<std::string> myList(5, "hats");
	ft::list<std::string> otherList;//(6, "");

	if (myList == otherList)
		std::cout << "\tmylist == otherlist" << std::endl;
	else
		std::cout << "NOT\tmylist == otherlist" << std::endl;

	if (myList != otherList)
		std::cout << "\tmylist != otherlist" << std::endl;
	else
		std::cout << "NOT\tmylist != otherlist" << std::endl;

	if (myList < otherList)
		std::cout << "\tmylist < otherlist" << std::endl;
	else
		std::cout << "NOT\tmylist < otherlist" << std::endl;

	if (myList > otherList)
		std::cout << "\tmylist > otherlist" << std::endl;
	else
		std::cout << "NOT\tmylist > otherlist" << std::endl;

	if (myList >= otherList)
		std::cout << "\tmylist >= otherlist" << std::endl;
	else
		std::cout << "NOT\tmylist >= otherlist" << std::endl;
	if (myList <= otherList)
		std::cout << "\tmylist <= otherlist" << std::endl;
	else
		std::cout << "NOT\tmylist <= otherlist" << std::endl;
}

bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

void	sam() {
	ft::list<double> first, second;
	ft::list<double>::iterator it;

	first.push_back (3.1);
	first.push_back (2.2);
	first.push_back (2.9);

	second.push_back (3.7);
	second.push_back (7.1);
	second.push_back (1.4);

	first.sort();
	second.sort();

	it = second.begin();
	double* ptr = &(*it);

	first.merge(second);
	std::cout << "first.size() = " << first.size() << std::endl;
	std::cout << "first.front() = " << first.front() << std::endl;
	std::cout << "first.back() = " << first.back() << std::endl;
	it = first.begin();
	double* ptr2 = &(*it);
	std::cout << "ptr == ptr2 : " << std::boolalpha << (ptr == ptr2) << std::endl;
	ft::advance(it, 4);
	std::cout << "*it = " << *it << std::endl;
	std::cout << "second.empty(): " << std::boolalpha << second.empty() << std::endl;

	second.push_back(2.1);
	print_container_content(second, "second for the first time");
	print_container_content(first, "first for the first time");
	first.merge(second, mycomparison);
	std::cout << "first.size() = " << first.size() << std::endl;
	std::cout << "first.front() = " << first.front() << std::endl;
	std::cout << "first.back() = " << first.back() << std::endl;
	it = first.begin();
	print_container_content(first, "first");
	print_container_content(second, "second");
	std::cout << "*it = " << *it << std::endl;
	std::cout << "second.empty(): " << std::boolalpha << second.empty() << std::endl;
}

void	stl_test() {
	std::list<int> stl;
	ft::list<int> nonstl;
	for (int i = 0; i < 10; i++)
		stl.push_front(i * 3);
	nonstl.assign(stl.begin(), stl.end());
	print_container_content(nonstl, "nonstl");
}

int main(int argc, char **argv) {
	if (argc == 2 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&tv, NULL);
		begintime = tv.tv_usec;
	}
//	constructors_test();
//	iterators_test();
//	capacity_test_element_access();
//	modifiers_test();
//	operations_test();
//	operations_test2();
//	relational_operators();
//	stl_test();
	sam();
	if (argc == 2 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&tv, NULL);
		endtime = tv.tv_usec;
		std::cout << "Time elapsed in total! = " << endtime - begintime << " nanoseconds" << std::endl;
	}
	if (argc == 3 && strcmp(argv[2], "leaks") == 0) {
		int a = system("leaks containers.out | grep \"total leaked bytes\" >&2");
		(void)a;
	}
	return 0;
}
