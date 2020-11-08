/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mapTest.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 11:14:55 by sam           #+#    #+#                 */
/*   Updated: 2020/11/01 11:14:55 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Catch2.h"
#include "Map.hpp"
#include "Pair.hpp"

TEST_CASE("Map: Insert + empty + size", "[Map]") {
	ft::map<char,int> mymap;
	REQUIRE(mymap.empty() == true);
	// first insert function version (single parameter):
	mymap.insert ( ft::pair<char,int>('a',100) );
	mymap.insert ( ft::pair<char,int>('z',200) );

	ft::pair<ft::map<char,int>::iterator,bool> ret;
	ret = mymap.insert ( ft::pair<char,int>('z',500) );
	REQUIRE(ret.second == false);

	// second insert function version (with hint position):
	ft::map<char,int>::iterator it = mymap.begin();
	mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
	mymap.insert (it, ft::pair<char,int>('c',400));	  // no max efficiency inserting
	REQUIRE(mymap.size() == 4);

	// third insert function version (range insertion):
	ft::map<char,int> anothermap;
	anothermap.insert(mymap.begin(), mymap.end());
	REQUIRE(mymap.size() == 4);
}

TEST_CASE("Map: Find", "[Map]") {
	ft::map<char,int> mymap;
	// first insert function version (single parameter):
	mymap.insert ( ft::pair<char,int>('a',100) );
	mymap.insert ( ft::pair<char,int>('z',200) );

	// second insert function version (with hint position):
	ft::map<char,int>::iterator it;
	it = mymap.find('a');
	bool res = it == mymap.begin();
	REQUIRE(res == true);
	it = mymap.find('x');
	res = it == mymap.end();
	REQUIRE(res == true);
}

TEST_CASE("Map: Iterators", "[Map]") {
	ft::map<int, int> myMap;

	myMap.insert(ft::make_pair(9, 9));
	myMap.insert(ft::make_pair(3, 3));
	myMap.insert(ft::make_pair(8, 8));
	myMap.insert(ft::make_pair(0, 0));
	myMap.insert(ft::make_pair(7, 7));
	myMap.insert(ft::make_pair(6, 6));
	myMap.insert(ft::make_pair(5, 5));
	myMap.insert(ft::make_pair(4, 4));
	myMap.insert(ft::make_pair(2, 2));
	myMap.insert(ft::make_pair(1, 1));

	ft::map<int, int>::iterator it = myMap.begin();
	for (int i = 0; i < 10; ++i) {
		REQUIRE(i == it->second);
		++it;
	}
}
