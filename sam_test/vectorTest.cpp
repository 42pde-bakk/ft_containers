/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectorTest.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 13:30:18 by sam           #+#    #+#                 */
/*   Updated: 2020/10/28 13:30:18 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Catch2.h"

#include "Vector.hpp"

TEST_CASE("Vector: Iterator", "[Vector]") {
	ft::vector<std::string> myVec;
	std::vector<std::string> sysVec;
	ft::vector<int> myIntVec;
	std::string str = "Hello, world!";
	myVec.push_back(str);
	sysVec.push_back(str);
	myVec.push_back("I'm the next King");
	sysVec.push_back("I'm the next King");
	myVec.push_back("Welcome yourself to the next chapter");
	sysVec.push_back("Welcome yourself to the next chapter");
	ft::vector<std::string>::iterator myIt = myVec.begin();
	std::vector<std::string>::iterator sysIt = sysVec.begin();

	SECTION("Increment") {
		myIt++;
		sysIt++;
		REQUIRE(*myIt == *sysIt);
		++myIt;
		++sysIt;
		REQUIRE(*myIt == *sysIt);
	}
	SECTION("Decrement") {
		myIt++;
		sysIt++;
		REQUIRE(*myIt == *sysIt);
		myIt--;
		sysIt--;
		REQUIRE(*myIt == *sysIt);
	}
	SECTION("-> overload") {
		myIt++;
		sysIt++;
		REQUIRE(*myIt->data() == *sysIt->data());
	}
	SECTION("* overload") {
		myIt++;
		sysIt++;
		REQUIRE(*myIt == *sysIt);
	}
	SECTION("== overload") {
		bool res;
		res = (myIt == myVec.begin());
		REQUIRE(res == true);
		myIt++;
		myIt++;
		myIt++;
		res = (myIt == myVec.end());
		REQUIRE(res == true);
		res = (myIt == myVec.begin());
		REQUIRE(res == false);
	}
	SECTION("!= overload") {
		bool res;
		res = (myIt != myVec.end());
		REQUIRE(res == true);
		myIt++;
		myIt++;
		res = (myIt != myVec.begin());
		REQUIRE(res == true);
		myIt++;
		res = (myIt != myVec.end());
		REQUIRE(res == false);
	}
	SECTION("Test (*it)++") {
		myIntVec.push_back(1);
		ft::vector<int>::iterator myIntIt = myIntVec.begin();
		REQUIRE(*myIntIt == 1);
		(*myIntIt)++;
		REQUIRE(*myIntIt == 2);
		*myIntIt++;
		bool res = (myIntIt == myIntVec.end());
		REQUIRE(res == true);
	}
	SECTION("Test (*it)--") {
		myIntVec.push_back(2);
		ft::vector<int>::iterator myIntIt = myIntVec.begin();
		REQUIRE(*myIntIt == 2);
		(*myIntIt)--;
		REQUIRE(*myIntIt == 1);
		*myIntIt--;
		bool res = (myIntIt != myIntVec.begin());
		REQUIRE(res == true);
	}
	SECTION("Test assignemt with iterator") {
		myIntVec.push_back(1);
		myIntVec.push_back(8);
		ft::vector<int>::iterator myIntIt = myIntVec.begin();
		REQUIRE(*myIntIt == 1);
		*myIntIt = 5;
		REQUIRE(*myIntIt == 5);
	}
	SECTION("Test dereference as lvalue") {
		myIntVec.push_back(1);
		myIntVec.push_back(8);
		ft::vector<int>::iterator myIntIt = myIntVec.begin();
		*myIntIt++ = 5;
		REQUIRE(*myIntIt == 8);
		myIntIt--;
		REQUIRE(*myIntIt == 5);
	}
	SECTION("Reverse iterator") {
		ft::vector<int> myvector;
		for (int i=1; i<=5; ++i) myvector.push_back(i);

		ft::vector<int>::reverse_iterator rit=myvector.rbegin();
		REQUIRE(*rit == 5);
		rit++;
		REQUIRE(*rit == 4);
		rit--;
		REQUIRE(*rit == 5);
		*rit = 10;
		REQUIRE(*rit == 10);
	}
	SECTION("Test - + += -+ overloads") {
		myIntVec.push_back(2);
		myIntVec.push_back(3);
		myIntVec.push_back(4);
		myIntVec.push_back(5);
		myIntVec.push_back(6);
		ft::vector<int>::iterator it = myIntVec.begin();
		REQUIRE(*it == 2);
		it = it + 1;
		REQUIRE(*it == 3);
		it + 1;
		REQUIRE(*it == 3);
		it = it - 1;
		REQUIRE(*it == 2);
		int i = *it + *it;
		REQUIRE(i == 4);
		it += 3;
		REQUIRE(*it == 5);
	}
}

TEST_CASE("Vector: Constructors", "[Vector]") {
	// constructors used in the same order as described above:
	ft::vector<int> first;                                // empty vector of ints
	REQUIRE(first.capacity() == 0);
	ft::vector<int> second(5, 100);                // four ints with value 100
	REQUIRE(second.capacity() == 5);
	ft::vector<int> third(second.begin(), second.end());  // iterating through second
	REQUIRE(third.capacity() == 5);
	ft::vector<int> fourth(third);                       // a copy of third
	REQUIRE(fourth.capacity() == 5);

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16, 2, 77, 29, 66};
	ft::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
	REQUIRE(fifth.capacity() == 5);
	REQUIRE(fifth.front() == 16);
	REQUIRE(fifth.back() == 66);

	ft::vector<int> sixt = fifth;
	REQUIRE(sixt.capacity() == 5);
	REQUIRE(sixt.front() == 16);
	REQUIRE(sixt.back() == 66);
}

TEST_CASE("Vector: Resize", "[Vector]") {
	ft::vector<int> myvector;

	// set some initial content:
	for (int i=1;i<6;i++) myvector.push_back(i);

	myvector.resize(5);
	REQUIRE(myvector.capacity() == 8);
	REQUIRE(myvector.size() == 5);
	REQUIRE(myvector.front() == 1);
	REQUIRE(myvector.back() == 5);
	myvector.resize(8,100);
	REQUIRE(myvector.capacity() == 8);
	REQUIRE(myvector.size() == 8);
	REQUIRE(myvector.front() == 1);
	REQUIRE(myvector.back() == 100);
	myvector.resize(12);
	REQUIRE(myvector.capacity() == 16);
	REQUIRE(myvector.size() == 12);
	REQUIRE(myvector.front() == 1);
	REQUIRE(myvector.back() == 0);
}

TEST_CASE("Vector: [] operator overload", "[Vector]") {
	ft::vector<int> myvector;

	for (int i = 0; i < 6; i++) myvector.push_back(i);

	for (int i = 0; i < 6; i++) {
		REQUIRE(myvector[i] == i);
	}
}

TEST_CASE("Vector: At", "[Vector") {
	ft::vector<int> myvector (10);   // 10 zero-initialized ints

	// assign some values:
	for (unsigned i=0; i<myvector.size(); i++)
		myvector.at(i)=i;

	for (unsigned i=0; i<myvector.size(); i++)
		REQUIRE(myvector.at(i) == i);

	REQUIRE_THROWS_AS(myvector.at(10), std::out_of_range);
}

TEST_CASE("Vector: Insert", "[Vector]") {
	ft::vector<int> myvector (3,100);
	ft::vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert ( it , 200 );
	// myvector contains: 200 100 100 100
	REQUIRE(myvector.size() == 4);
	REQUIRE(myvector.capacity() == 6);
	REQUIRE(myvector.at(0) == 200);
	REQUIRE(myvector.at(2) == 100);


	myvector.insert (it,2,300);
	// myvector contains: 300 300 200 100 100 100
	REQUIRE(myvector.size() == 6);
	REQUIRE(myvector.capacity() == 6);
	REQUIRE(myvector.at(0) == 300);
	REQUIRE(myvector.at(2) == 200);

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	ft::vector<int> anothervector (2,400);
	myvector.insert (it+2,anothervector.begin(),anothervector.end());
	REQUIRE(myvector.size() == 8);
	REQUIRE(myvector.capacity() == 12);

	int myarray [] = { 501,502,503 };
	myvector.insert (myvector.begin(), myarray, myarray+3);
	REQUIRE(myvector.size() == 11);
	REQUIRE(myvector.capacity() == 12);
	REQUIRE(myvector.at(0) == 501);
	REQUIRE(myvector.at(2) == 503);
	REQUIRE(myvector.at(5) == 400);
	REQUIRE(myvector.at(7) == 200);
	REQUIRE(myvector.back() == 100);
}

TEST_CASE("Vector: Erase", "[Vector]") {
	ft::vector<int> myvector;

	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++) myvector.push_back(i);

	SECTION("Erase end") {
		// erase the 6th element
		myvector.erase (myvector.begin()+9);
		// myvector contains: 1 2 3 4 5 7 8 9 10
		REQUIRE(myvector.size() == 9);
		REQUIRE(myvector.capacity() == 16);
		REQUIRE(myvector.back() == 9);
	}
	SECTION("Erase 1 element") {
		// erase the 6th element
		myvector.erase (myvector.begin()+5);
		// myvector contains: 1 2 3 4 5 7 8 9 10
		REQUIRE(myvector.size() == 9);
		REQUIRE(myvector.capacity() == 16);
		REQUIRE(myvector.at(4) == 5);
		REQUIRE(myvector.at(5) == 7);

		myvector.erase (myvector.begin());
		REQUIRE(myvector.size() == 8);
		REQUIRE(myvector.capacity() == 16);
		REQUIRE(myvector.at(0) == 2);
	}
	SECTION("Erase range from begin") {
		myvector.erase (myvector.begin(), myvector.begin()+5);
		REQUIRE(myvector.size() == 5);
		REQUIRE(myvector.capacity() == 16);
		REQUIRE(myvector.at(0) == 6);
		REQUIRE(myvector.at(1) == 7);
	}
	SECTION("Erase range from middle") {
		myvector.erase (myvector.begin()+1, myvector.begin()+5);
		REQUIRE(myvector.size() == 6);
		REQUIRE(myvector.capacity() == 16);
		REQUIRE(myvector.at(0) == 1);
		REQUIRE(myvector.at(1) == 6);
	}
	SECTION("Erase range until end - 1") {
		myvector.erase (myvector.begin()+5, myvector.begin()+9);
		REQUIRE(myvector.size() == 6);
		REQUIRE(myvector.capacity() == 16);
		REQUIRE(myvector.at(4) == 5);
		REQUIRE(myvector.at(5) == 10);
	}
	SECTION("Erase range until end") {
		myvector.erase (myvector.begin()+5, myvector.end());
		REQUIRE(myvector.size() == 5);
		REQUIRE(myvector.capacity() == 16);
		REQUIRE(myvector.at(4) == 5);
	}
}

TEST_CASE("Vector: Swap", "[Vector]") {
	ft::vector<int> foo (3,100);   // three ints with a value of 100
	ft::vector<int> bar (5,200);   // five ints with a value of 200

	foo.swap(bar);

	REQUIRE(foo.size() == 5);
	REQUIRE(foo.capacity() == 5);
	REQUIRE(bar.size() == 3);
	REQUIRE(bar.capacity() == 3);
}

TEST_CASE("Vector: Relational operator overloads", "[Vector]") {
	ft::vector<int> a;
	a.push_back(10);
	a.push_back(20);
	a.push_back(30);
	ft::vector<int> b;
	b.push_back(10);
	b.push_back(20);
	b.push_back(30);
	ft::vector<int> c;
	c.push_back(30);
	c.push_back(20);
	c.push_back(10);

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

TEST_CASE("Vector: subtracting two iterators", "[Vector]") {
	ft::vector<int> myvector (3,100);
	ft::vector<int>::iterator it;
	ft::vector<int>::iterator it2;

	it = myvector.begin();
	it2 = myvector.end();
	REQUIRE(it2 - it == 3);
}
