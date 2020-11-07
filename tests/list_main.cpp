/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_main.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 12:46:40 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/11/06 22:56:58 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "../srcs/List/List.hpp"
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
void	print_container_content(ft::list<T>	&list, const std::string& name = "container") {
	std::cout << name << " contains:";
	for (ft::list<int>::iterator it = list.begin(); it != list.end(); it++)
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
	ft::list<int> mylist(10, 42);
	int i = 0;
	for (ft::list<int>::iterator it = mylist.begin(); it != mylist.end(); it++) {
		*it += i;
		++i;
	}
	ft::list<int> mysecondlist = mylist;
	ft::list<int>::const_iterator it = mylist.begin();
	std::cout << "mylist contains:";
	while (it != mylist.end())
	{
		std::cout << ' ' << *it;
		// *it = 0; // wont compile because the iterator is const
		++it;
	}
	std::cout << std::endl;
	ft::list<int>::reverse_iterator rit = mylist.rbegin();
	ft::list<int>::reverse_iterator ritend = mylist.rend();
	std::cout << "mylist.reverse contains:";
	while (rit != ritend)
	{
		std::cout << ' ' << *rit;
		++rit;
	}
	std::cout << std::endl;
	ft::list<int>::const_reverse_iterator crit = mylist.rbegin();
	std::cout << "mylist.ConstReverse contains:";
	while (crit != ritend)
	{
		std::cout << ' ' << *crit;
		// *crit = 0; // wont compile because this iterator too is const
		++crit;
	}
	std::cout << std::endl << std::endl;
}

void	capacity_test_element_access() {
	ft::list<std::string> mylist;
	std::cout << "Boolean whether mylist is empty or not: " << std::boolalpha << mylist.empty() << std::endl;
	std::string	strings[] = { "kissahomie", "pogchamp" , "Queen", "Yaas" };
	for (int i = 0; i < 4 ; i++)
		mylist.push_front(strings[i]);
	std::cout << "Boolean whether mylist is empty or not: " << std::boolalpha << mylist.empty() << std::endl;
	std::cout << "mylist.size() = " << mylist.size();
	// std::cout << ", and mylist.max_size() = " << mylist.max_size();
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

void	sam() {
   ft::list<int> first (3,100);   // three ints with a value of 100
   ft::list<int> second (5,200);  // five ints with a value of 200
   first.swap(second);
   std::cout << "first contains:";
   for (ft::list<int>::iterator it=first.begin(); it!=first.end(); it++) {
		*it = *it + 3;
      std::cout << ' ' << *it;
   }
   std::cout << '\n';
   std::cout << "second contains:";
   for (ft::list<int>::iterator it=second.begin(); it!=second.end(); it++)
      std::cout << ' ' << *it;
   std::cout << '\n';
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
	constructors_test();
	iterators_test();
	capacity_test_element_access();
	modifiers_test();
	operations_test();
	operations_test2();
	relational_operators();
	stl_test();
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
