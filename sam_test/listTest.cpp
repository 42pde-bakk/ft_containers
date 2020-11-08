#include "Catch2.h"

#include "List.hpp"
#include <list>

TEST_CASE("List: Iterator", "[List]") {
	ft::list<std::string> myList;
	std::list<std::string> sysList;
	ft::list<int> myIntList;
	std::string str = "Hello, world!";
	myList.push_back(str);
	sysList.push_back(str);
	myList.push_back("I'm the next King");
	sysList.push_back("I'm the next King");
	myList.push_back("Welcome yourself to the next chapter");
	sysList.push_back("Welcome yourself to the next chapter");
	ft::list<std::string>::iterator myIt = myList.begin();
	std::list<std::string>::iterator sysIt = sysList.begin();

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
		res = (myIt == myList.begin());
		REQUIRE(res == true);
		myIt++;
		myIt++;
		myIt++;
		res = (myIt == myList.end());
		REQUIRE(res == true);
		res = (myIt == myList.begin());
		REQUIRE(res == false);
	}
	SECTION("!= overload") {
		bool res;
		res = (myIt != myList.end());
		REQUIRE(res == true);
		myIt++;
		myIt++;
		res = (myIt != myList.begin());
		REQUIRE(res == true);
		myIt++;
		res = (myIt != myList.end());
		REQUIRE(res == false);
	}
	SECTION("Test (*it)++") {
		myIntList.push_back(1);
		ft::list<int>::iterator myIntIt = myIntList.begin();
		REQUIRE(*myIntIt == 1);
		(*myIntIt)++;
		REQUIRE(*myIntIt == 2);
		*myIntIt++;
		bool res = (myIntIt == myIntList.end());
		REQUIRE(res == true);
	}
	SECTION("Test (*it)--") {
		myIntList.push_back(2);
		ft::list<int>::iterator myIntIt = myIntList.begin();
		REQUIRE(*myIntIt == 2);
		(*myIntIt)--;
		REQUIRE(*myIntIt == 1);
		*myIntIt--;
		bool res = (myIntIt != myIntList.begin());
		REQUIRE(res == true);
	}
	SECTION("Test assignemt with iterator") {
		myIntList.push_back(1);
		myIntList.push_back(8);
		ft::list<int>::iterator myIntIt = myIntList.begin();
		REQUIRE(*myIntIt == 1);
		*myIntIt = 5;
		REQUIRE(*myIntIt == 5);
	}
	SECTION("Test dereference as lvalue") {
		myIntList.push_back(1);
		myIntList.push_back(8);
		ft::list<int>::iterator myIntIt = myIntList.begin();
		*myIntIt++ = 5;
		REQUIRE(*myIntIt == 8);
		myIntIt--;
		REQUIRE(*myIntIt == 5);
	}
	SECTION("Reverse iterator") {
		ft::list<int> mylist;
		for (int i=1; i<=5; ++i) mylist.push_back(i);

		ft::list<int>::reverse_iterator rit=mylist.rbegin();
		REQUIRE(*rit == 5);
		rit++;
		REQUIRE(*rit == 4);
		rit--;
		REQUIRE(*rit == 5);
		*rit = 10;
		REQUIRE(*rit == 10);
	}
}

TEST_CASE("List: Push-front", "[List]") {
	ft::list<int> myList;
	myList.push_back(1);
	myList.push_front(2);
	myList.push_front(26);
	ft::list<int>::iterator it = myList.begin();
	REQUIRE(*it == 26);
	it++;
	REQUIRE(*it == 2);
}

TEST_CASE("List: Pop-front", "[List]") {
	ft::list<int> myList;
	myList.push_back(1);
	myList.push_back(2);
	myList.push_back(3);
	myList.pop_front();
	myList.pop_front();
	ft::list<int>::iterator it = myList.begin();
	REQUIRE(*it == 3);
}

TEST_CASE("List: Pop-back", "[List]") {
	ft::list<int> myList;
	myList.push_back(1);
	myList.push_back(2);
	myList.push_back(3);
	myList.pop_back();
	myList.pop_back();
	ft::list<int>::iterator it = myList.begin();
	REQUIRE(*it == 1);
}

TEST_CASE("List: Assign", "[List]") {
	ft::list<int>	oneL;
	std::list<int>	twoL;
	twoL.push_back(1);
	twoL.push_back(2);
	twoL.push_back(3);

	oneL.assign(twoL.begin(), twoL.end());
	ft::list<int>::iterator it = oneL.begin();
	REQUIRE(*it == 1);
	it++;
	REQUIRE(*it == 2);
	REQUIRE(oneL.size() == 3);

	oneL.assign(4, 300);
	it = oneL.begin();
	REQUIRE(*it == 300);
	it++;
	REQUIRE(*it == 300);
	REQUIRE(oneL.size() == 4);

	int myint[5] = {1, 2, 3, 4, 5};
	oneL.assign(myint, myint + 5);
	it = oneL.begin();
	REQUIRE(*it == 1);
	it++;
	REQUIRE(*it == 2);
	REQUIRE(oneL.size() == 5);
}

TEST_CASE("List: Insert", "[List]") {
	ft::list<int> mylist;
	ft::list<int>::iterator it;

	// set some initial values:
	for (int i=1; i<=5; ++i) mylist.push_back(i); // 1 2 3 4 5

	it = mylist.begin();
	++it;       // it points now to number 2           ^
	REQUIRE(*it == 2);
	mylist.insert (it,10);                        // 1 10 2 3 4 5
	REQUIRE(mylist.size() == 6);
	// "it" still points to number 2                           ^
	mylist.insert (it,2,20);                      // 1 10 20 20 2 3 4 5
	REQUIRE(mylist.size() == 8);
	--it;       // it points now to the second 20            ^
	REQUIRE(*it == 20);
	std::vector<int> myvector (2,30);
	mylist.insert (it,myvector.begin(),myvector.end());
	// 1 10 20 30 30 20 2 3 4 5
	//               ^
	it--;
	REQUIRE(*it == 30);
	REQUIRE(mylist.size() == 10);
}

TEST_CASE("List: Erase", "[List]") {
	ft::list<int> mylist;
	ft::list<int>::iterator it1,it2;
	// set some values:
	for (int i=1; i<10; ++i) mylist.push_back(i*10);
										// 10 20 30 40 50 60 70 80 90
	it1 = it2 = mylist.begin(); 		// ^^
	advance (it2,6);				// ^                 ^
	++it1;								//    ^              ^
	REQUIRE(mylist.size() == 9);
	REQUIRE(*it1 == 20);
	REQUIRE(*it2 == 70);
	it1 = mylist.erase (it1);   // 10 30 40 50 60 70 80 90
								//    ^           ^
	REQUIRE(*it1 == 30);
	REQUIRE(*it2 == 70);
	REQUIRE(mylist.size() == 8);
	it2 = mylist.erase (it2);	// 10 30 40 50 60 80 90
								//    ^           ^
	++it1;						//       ^        ^
	--it2;						//       ^     ^
	REQUIRE(*it1 == 40);
	REQUIRE(*it2 == 60);
	REQUIRE(mylist.size() == 7);
	it1 = mylist.erase (it1,it2);		// 10 30 60 80 90
										//       ^
	REQUIRE(*it1 == 60);
	REQUIRE(*it2 == 60);
	REQUIRE(mylist.size() == 5);
}

TEST_CASE("List: Swap", "[List]") {
	ft::list<int> first (3,100);   // three ints with a value of 100
	ft::list<int> second (5,200);  // five ints with a value of 200

	first.swap(second);

	ft::list<int>::iterator it=first.begin();
	REQUIRE(*it == 200);
	REQUIRE(first.size() == 5);
	it = second.begin();
	REQUIRE(*it == 100);
	REQUIRE(second.size() == 3);
}

TEST_CASE("List: Resize", "[List]") {
	ft::list<int> mylist;

	// set some initial content:
	for (int i=1; i<10; ++i) mylist.push_back(i);

	mylist.resize(5);
	REQUIRE(mylist.size() == 5);
	mylist.resize(8,100);
	REQUIRE(mylist.size() == 8);
	mylist.resize(12);
	REQUIRE(mylist.size() == 12);
}

TEST_CASE("List: Splice", "[List]") {
	ft::list<int> mylist1, mylist2;
	ft::list<int>::iterator it;
	ft::list<int>::iterator ptrIt;

	SECTION("Functionality") {
		// set some initial values:
		for (int i=1; i<=4; ++i)
			mylist1.push_back(i);      // mylist1: 1 2 3 4

		for (int i=1; i<=3; ++i)
			mylist2.push_back(i*10);   // mylist2: 10 20 30

		it = mylist1.begin();
		++it;                         // points to 2
		mylist1.splice (it, mylist2);
		// mylist1: 1 10 20 30 2 3 4
		// mylist2 (empty)
		// "it" still points to 2 (the 5th element)
		REQUIRE(mylist1.size() == 7);
		REQUIRE(mylist2.empty() == true);
		REQUIRE(*it == 2);

		mylist2.splice (mylist2.begin(),mylist1, it);
		// mylist1: 1 10 20 30 3 4
		// mylist2: 2
		// "it" is now invalid.
		REQUIRE(mylist1.size() == 6);
		REQUIRE(mylist2.size() == 1);

		it = mylist1.begin();
		std::advance(it,3);           // "it" points to 30
		REQUIRE(*it == 30);

		mylist1.splice ( mylist1.begin(), mylist1, it, mylist1.end());
		// mylist1 contains: 30 3 4 1 10 20
		// mylist2 contains: 2
		REQUIRE(mylist1.size() == 6);
		REQUIRE(mylist2.size() == 1);
	}
	SECTION("Check pointers") {
		// set some initial values:
		for (int i=1; i<=4; ++i)
			mylist1.push_back(i);      // mylist1: 1 2 3 4

		for (int i=1; i<=3; ++i)
			mylist2.push_back(i*10);   // mylist2: 10 20 30

		it = mylist1.begin();
		++it;                         // points to 2

		// Save the ptr to _data of 1st element in L2
		ptrIt =  mylist2.begin();
		int* ptr = &(*ptrIt);

		mylist1.splice (it, mylist2); // mylist1: 1 10 20 30 2 3 4
		// mylist2 (empty)

		// Get ptr to _data of the second element in L1 (10 from L2)
		ptrIt = mylist1.begin();
		ptrIt++;
		int* ptr2 = &(*ptrIt);
		// ptr and ptr2 should be the same because the element was moved without destructing it
		REQUIRE(ptr == ptr2);
	}
}

TEST_CASE("List: Remove", "[List]") {
	int myints[]= {17,89,7,7};
	ft::list<int> mylist (myints,myints+4);

	mylist.remove(7);
	// mylist contains: 17 7 14
	REQUIRE(mylist.size() == 2);
}

// a predicate implemented as a function:
bool single_digit (const int& value) { return (value<10); }

// a predicate implemented as a class:
struct is_odd {
	bool operator() (const int& value) { return (value%2)==1; }
};
TEST_CASE("List: Remove_if", "[List]") {
	int myints[]= {15,36,7,17,20,39,4,1};
	ft::list<int> mylist (myints,myints+8);   // 15 36 7 17 20 39 4 1

	mylist.remove_if (single_digit);           // 15 36 17 20 39

	mylist.remove_if (is_odd());               // 36 20
	REQUIRE(mylist.size() == 2);
}

TEST_CASE("List: Front() + Back()", "[List]") {
	ft::list<int> mylist;

	mylist.push_back(77);
	mylist.push_back(22);

	// now front equals 77, and back 22

	mylist.front() -= mylist.back();
	REQUIRE(mylist.front() == 55);
}

// comparison, not case sensitive.
bool compare_nocase (const std::string& first, const std::string& second)
{
	unsigned int i=0;
	while ( (i<first.length()) && (i<second.length()) )
	{
		if (tolower(first[i])<tolower(second[i])) return true;
		else if (tolower(first[i])>tolower(second[i])) return false;
		++i;
	}
	return ( first.length() < second.length() );
}

TEST_CASE("List: Sort", "[List]") {
	ft::list<std::string> mylist;
	ft::list<std::string>::iterator it;
	mylist.push_back ("Three");
	mylist.push_back ("one");
	mylist.push_back ("two");
	mylist.push_back ("Three");

	mylist.sort();
//	mylist contains: Three Three one two
	it = mylist.begin();
	REQUIRE(*it == "Three");
	std::advance(it, 2);
	REQUIRE(*it == "one");
	std::advance(it, 1);
	REQUIRE(*it == "two");

	mylist.sort(compare_nocase);
//	mylist contains: one Three Three two
	it = mylist.begin();
	REQUIRE(*it == "one");
	std::advance(it, 2);
	REQUIRE(*it == "Three");
	std::advance(it, 1);
	REQUIRE(*it == "two");
}

// a binary predicate implemented as a function:
bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

// a binary predicate implemented as a class:
struct is_near {
	bool operator() (double first, double second)
	{ return (fabs(first-second)<5.0); }
};
TEST_CASE("List: Unique", "[List]") {
	SECTION("Doubles") {
		double mydoubles[] = {12.15, 2.72, 73.0, 12.77, 3.14, 12.77, 73.35, 72.25, 15.3, 72.25};
		std::list<double> mylist(mydoubles, mydoubles + 10);

		mylist.sort();                //  2.72,  3.14, 12.15, 12.77, 12.77, 15.3,  72.25, 72.25, 73.0,  73.35

		mylist.unique();            //  2.72, 3.14, 12.15, 12.77, 15.3,  72.25, 73.0,  73.35
		REQUIRE(mylist.size() == 8);
		REQUIRE(mylist.back() == 73.35);
		mylist.unique(same_integral_part);  //  2.72,  3.14, 12.15, 15.3,  72.25, 73.0

		mylist.unique(is_near());           //  2.72, 12.15, 72.25
		REQUIRE(mylist.size() == 3);
		REQUIRE(mylist.back() == 72.25);

		// mylist contains: 2.72 12.15 72.25
	}

	SECTION("Only ones") {
		double myOnes[]={ 1, 1, 1, 1 };
		std::list<double> mylist (myOnes,myOnes+4);

		mylist.sort();

		mylist.unique();
		REQUIRE(mylist.size() == 1);
		REQUIRE(*mylist.begin() == 1);

		mylist.unique (same_integral_part);

		mylist.unique (is_near());
		REQUIRE(mylist.size() == 1);
		REQUIRE(*mylist.begin() == 1);
	}
}

// compare only integral part:
bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }
TEST_CASE("List: Merge", "[List]") {
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
	// first contains: 1.4 2.2 2.9 3.1 3.7 7.1
	REQUIRE(first.size() == 6);
	REQUIRE(first.front() == 1.4);
	REQUIRE(first.back() == 7.1);
	it = first.begin();
	double* ptr2 = &(*it);
	REQUIRE(ptr == ptr2);
	std::advance(it, 4);
	REQUIRE(*it == 3.7);
	// (second is now empty)
	REQUIRE(second.empty() == true);

	second.push_back (2.1);

	first.merge(second,mycomparison);
	// first contains: 1.4 2.2 2.9 2.1 3.1 3.7 7.1
	REQUIRE(first.size() == 7);
	REQUIRE(first.front() == 1.4);
	REQUIRE(first.back() == 7.1);
	it = first.begin();
	std::advance(it, 3);
	REQUIRE(*it == 2.1);
	// (second is now empty)
	REQUIRE(second.empty() == true);
}

TEST_CASE("List: Reverse", "[List]") {
	ft::list<int> mylist;

	for (int i=1; i<10; ++i) mylist.push_back(i);

	mylist.reverse();
	REQUIRE(mylist.size() == 9);
	REQUIRE(mylist.front() == 9);
	REQUIRE(mylist.back() == 1);
}

TEST_CASE("List: Relational operator overloads", "[List]") {
	ft::list<int> a;
	a.push_back(10);
	a.push_back(20);
	a.push_back(30);
	ft::list<int> b;
	b.push_back(10);
	b.push_back(20);
	b.push_back(30);
	ft::list<int> c;
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
