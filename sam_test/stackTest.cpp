/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stackTest.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 11:44:38 by skorteka      #+#    #+#                 */
/*   Updated: 2020/10/29 11:44:38 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Catch2.h"

#include "vector.hpp"
#include "Stack.hpp"
#include <list>
#include <deque>

TEST_CASE("Stack: Constructor", "[Stack]") {
	std::deque<int> mydeque (3,100);          // deque with 3 elements
	ft::vector<int> myvector (2,200);        // vector with 2 elements

	ft::stack<int> first;                    // empty stack
	ft::stack<int> second (myvector);        // stack initialized to copy of deque

	ft::stack<int,ft::vector<int> > third;  // empty stack using vector
	ft::stack<int,std::deque<int> > fourth (mydeque);
}

TEST_CASE("Stack: Size() + Empty()", "[Stack]") {
	std::deque<int> mydeque (3,100);          // deque with 3 elements
	ft::vector<int> myvector (2,200);        // vector with 2 elements

	ft::stack<int> first;               // empty stack

	ft::stack<int,ft::vector<int> > second;  // empty stack using vector
	ft::stack<int,std::deque<int> > third (mydeque);

	REQUIRE(first.empty() == true);
	REQUIRE(second.empty() == true);
	REQUIRE(third.size() == 3);
}

TEST_CASE("Stack: Top()", "[Stack]") {
	ft::vector<int> myvector;

	// set some initial content:
	for (int i=1;i<6;i++) myvector.push_back(i);
	ft::stack<int,ft::vector<int> > mystack (myvector);
	mystack.top() += 5;
	REQUIRE(mystack.top() == 10);
}

TEST_CASE("Stack: Push() + Pop()", "[Stack]") {
	ft::stack<int> mystack;

	for (int i=0; i<5; ++i) mystack.push(i);
	int i = 4;
	while (!mystack.empty())
	{
		REQUIRE(mystack.top() == i);
		mystack.pop();
		i--;
	}
}

TEST_CASE("Stack: Relational operator overloads", "[Stack]") {
	ft::stack<int> a;
	a.push(10);
	a.push(20);
	a.push(30);
	ft::stack<int> b;
	b.push(10);
	b.push(20);
	b.push(30);
	ft::stack<int> c;
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
