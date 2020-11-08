/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queueTest.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 13:40:18 by skorteka      #+#    #+#                 */
/*   Updated: 2020/10/29 13:40:18 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Catch2.h"

#include "list.hpp"
#include "Queue.hpp"
#include <deque>

TEST_CASE("Queue: Constructor", "[Queue]") {
	std::deque<int> mydeque (3,100);          // deque with 3 elements
	ft::list<int> mylist (2,200);        // list with 2 elements

	ft::queue<int> first;                    // empty queue
	ft::queue<int> second (mylist);         // queue initialized to copy of deque

	ft::queue<int,ft::list<int> > third;  // empty queue using list
	ft::queue<int,std::deque<int> > fourth (mydeque);
}

TEST_CASE("Queue: Size() + Empty()", "[Queue]") {
	std::deque<int> mydeque (3,100);          // deque with 3 elements
	ft::list<int> mylist (2,200);        // list with 2 elements

	ft::queue<int> first;             // empty queue
	ft::queue<int,ft::list<int> > second;  // empty queue using list
	ft::queue<int,std::deque<int> > third (mydeque);

	REQUIRE(first.empty() == true);
	REQUIRE(second.empty() == true);
	REQUIRE(third.size() == 3);
}

TEST_CASE("Queue: Back()", "[Queue]") {
	ft::list<int> mylist;

	// set some initial content:
	for (int i=1;i<6;i++) mylist.push_back(i);
	ft::queue<int,ft::list<int> > myqueue (mylist);
	myqueue.back() += 5;
	REQUIRE(myqueue.back() == 10);
}

TEST_CASE("Queue: Front()", "[Queue]") {
	ft::list<int> mylist;

	// set some initial content:
	for (int i=1;i<6;i++) mylist.push_back(i);
	ft::queue<int,ft::list<int> > myqueue (mylist);
	myqueue.front() += 5;
	REQUIRE(myqueue.front() == 6);
}

TEST_CASE("Queue: Push() + Pop()", "[Queue]") {
	ft::queue<int> myqueue;

	for (int i=0; i<5; ++i) myqueue.push(i);
	int i = 0;
	while (!myqueue.empty())
	{
		REQUIRE(myqueue.front() == i);
		myqueue.pop();
		i++;
	}
}

TEST_CASE("Queue: Relational operator overloads", "[Queue]") {
	ft::queue<int> a;
	a.push(10);
	a.push(20);
	a.push(30);
	ft::queue<int> b;
	b.push(10);
	b.push(20);
	b.push(30);
	ft::queue<int> c;
	c.push(30);
	c.push(20);
	c.push(10);

	REQUIRE((a == b) == true);
	REQUIRE((b != c) == true);
	REQUIRE((b < c) == true);
	REQUIRE((c > b) == true);
	REQUIRE((a <= b) == true);
	REQUIRE((a >= b) == true);

	REQUIRE((a <= b) == true);
	REQUIRE((a > b) == false);
	REQUIRE((a < b) == false);
	REQUIRE((a != b) == false);
	REQUIRE((b > c) == false);
	REQUIRE((b == c) == false);
	REQUIRE((b != c) == true);
}
