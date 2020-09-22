/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 12:46:40 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/09/22 16:27:00 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "srcs/List/List.hpp"
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

void	assign_test() {
	ft::list<int> first;
	ft::list<int> second;

	first.assign (7,100);                      // 7 ints with value 100

	second.assign (first.begin(),first.end()); // a copy of first

	// int myints[]={1776,7,4};
	// first.assign (myints,myints+3);            // assigning from array
	// std::cout << "first contains: "

	std::cout << "Size of first: " << int (first.size()) << std::endl;
	std::cout << "Size of second: " << int (second.size()) << std::endl;
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

// void	swapper() {
// 	ft::list<int> first((size_t)10, 42);
// 	ft::list<int> second((size_t)2, 200);
// 	first.swap(second);
// 	for (ft::list<int>::iterator it = first.begin(); it != first.end(); it++) {
// 		std::cout << "swapped first *it: " << *it << std::endl;
// 	}
// 	for (ft::list<int>::iterator it = second.begin(); it != second.end(); it++) {
// 		std::cout << "swapped second *it: " << *it << std::endl;
// 	}
// }

void	resizer() {
	ft::list<int> first((size_t)10, 42);
	ft::list<int> second((size_t)2, 200);
	first.resize(5);
	second.resize(5);
	std::cout << "first < second: " << (first < second) << std::endl;
	std::cout << "first > second: " << (first > second) << std::endl;
	for (ft::list<int>::iterator it = first.begin(); it != first.end(); it++) {
		std::cout << "resized first *it: " << *it << std::endl;
	}
	for (ft::list<int>::iterator it = second.begin(); it != second.end(); it++) {
		std::cout << "resized second *it: " << *it << std::endl;
	}
	std::cout << "are first and second the same?: " << (first == second) << std::endl;
	std::cout << "are first and second difference?: " << (first != second) << std::endl;
}

// void	relational() {
// 	ft::list<int> first;
// 	first.push_back(3);
// 	first.push_back(5);
// 	ft::list<int> second((size_t)2, 4);
// 	std::cout << "first < second: " << (first < second) << std::endl;
// 	swap(first, second);
// 	std::cout << "first < second: " << (first < second) << std::endl;
// }

void	reverser() {
	ft::list<int> wop;
	for (int i = 0; i < 10; i++) {
		wop.push_back(i * 2);
		std::cout << "wop[" << i << "]: " << i * 2 << std::endl;
	}
	wop.reverse();
	for (ft::list<int>::iterator it = wop.begin(); it != wop.end(); it++) {
		std::cout << "wop: " << *it << std::endl;
	}
}

void	splicing() {
  ft::list<int> mylist1, mylist2;
  ft::list<int>::iterator it;

  // set some initial values:
  for (int i=1; i<=4; ++i)
     mylist1.push_back(i);      // mylist1: 1 2 3 4

  for (int i=1; i<=3; ++i)
     mylist2.push_back(i*10);   // mylist2: 10 20 30

  it = mylist1.begin();
  ++it;                         // points to 2

  mylist1.splice (it, mylist2); // mylist1: 1 10 20 30 2 3 4
                                // mylist2 (empty)
                                // "it" still points to 2 (the 5th element)
                                          
  mylist2.splice (mylist2.begin(),mylist1, it);
                                // mylist1: 1 10 20 30 3 4
                                // mylist2: 2
                                // "it" is now invalid.
  it = mylist1.begin();
  ft::advance(it,3);           // "it" points now to 30
  std::cout << "mylist1 contains:";

  mylist1.splice ( mylist1.begin(), mylist1, it, mylist1.end());
                                // mylist1: 30 3 4 1 10 20

  std::cout << "mylist1 contains:";
  for (it=mylist1.begin(); it!=mylist1.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "mylist2 contains:";
  for (it=mylist2.begin(); it!=mylist2.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

// void	remover() {
// 	int myints[]= {17,89,7,14};
// 	ft::list<int> mylist (myints,myints+4);

// 	mylist.remove(89);

// 	std::cout << "mylist contains:";
// 	for (ft::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
// 		std::cout << ' ' << *it;
// 	std::cout << '\n';
// }

// a predicate implemented as a function:
bool single_digit (const int& value) { return (value<10); }

// a predicate implemented as a class:
struct is_odd {
	bool operator() (const int& value) { return (value%2)==1; }
};

// void	remover_if()
// {
// 	int myints[]= {15,36,7,17,20,39,4,1};
// 	ft::list<int> mylist (myints,myints+8);   // 15 36 7 17 20 39 4 1

// 	mylist.remove_if(single_digit);           // 15 36 17 20 39

// 	mylist.remove_if (is_odd());               // 36 20

// 	std::cout << "mylist contains:";
// 	for (ft::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
// 		std::cout << ' ' << *it;
// 	std::cout << '\n';
// }

bool	is_within_five(int first, int second) {
	return (abs(first - second) <= 5);
}

void	unique_test() {
	ft::list<double> mylist;

	for (int i = 0; i < 10; i++) {
		int n = i;
		if (i % 2)
			n = 0;
		mylist.push_back(n);
	}
  
	// mylist.sort();

	mylist.unique();
	mylist.unique(is_within_five);

	std::cout << "mylist contains:";
	for (ft::list<double>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	sort_test() {
	ft::list<int> mylist;
	int	myints[] = {0, 4, 213, 20, 22, 20, -100, 300};
	ft::list<int>::iterator it;
	for (int i = 0; i < 8; i++)
		mylist.push_back(myints[i]);
	std::cout << "mylist contains:";
	for (it=mylist.begin(); it!=mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	mylist.sort();
	std::cout << "After sorting, mylist contains:";
	for (it=mylist.begin(); it!=mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << " loveyou" << std::endl;


}

void	merge_test() {
	ft::list<int> mylist;
	int	myints[] = {0, 2, 4, 6, 8};
	int	myints2[] = {1, 3, 5, 7, 9};
	for (int i = 0; i < 5; i++) {
		mylist.push_back(myints[i]);
	}
	ft::list<int> mysecondlist;
	for (int i = 0; i < 5; i++) {
		mysecondlist.push_back(myints2[i]);
	}
	mylist.sort();
	mysecondlist.sort();
	ft::list<int>::iterator it;
	std::cout << "Before mergin, mylist contains:";
	for (it = mylist.begin(); it != mylist.end(); it++)
		std::cout << ' ' << *it;
	std::cout << " loveyou" << std::endl;
	std::cout << std::endl << "Before mergin, mysecondlist contains:";
	for (it = mysecondlist.begin(); it != mysecondlist.end(); it++)
		std::cout << ' ' << *it;
	std::cout << " loveyou" << std::endl;
	mylist.merge(mysecondlist);
	std::cout << "After mergin, mylist contains:";
	for (it = mylist.begin(); it != mylist.end(); it++)
		std::cout << ' ' << *it;
	std::cout << " loveyou" << std::endl;
	std::cout << std::endl << "After mergin, mysecondlist contains:";
	for (it = mysecondlist.begin(); it != mysecondlist.end(); it++)
		std::cout << ' ' << *it;
	std::cout << " loveyou" << std::endl;
}

int main() {
	srand(time(0));
	assign_test();
	// peer();
	// constants();
	// eraser();
	// swapper();
	// resizer();
	// relational();
	// reverser();
	// splicing();
	// remover();
	// remover_if();
	// unique_test();
	// sort_test();
	// merge_test();
	// system("leaks containers.out | grep \"total leaked bytes\"");
	//thx djevayo for the pr
}
