/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_main.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 21:10:23 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/22 01:13:33 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Set.hpp"
#include <set>
#include <string>
#include <iostream>
#include <sys/time.h>
#include <cstring>
#include <stdlib.h>

# if defined(unix) || defined(__unix__) || defined(__unix)
#  define LINUX 1
# else
#  define LINUX 0
# endif

size_t begintime;
size_t endtime;
struct timeval	tv;

template< typename K, typename V >
void	print_container_content(ft::set<K, V>& mappie, const std::string& name = "container") {
	std::cout << name << " contains:";
	for (typename ft::set<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++)
		std::cout << ' ' << *it;
	std::cout << " $" << std::endl;
}

template< typename K, typename V>
void	compare_keys(ft::set<K, V>& mappie, K compelem = K(), const std::string& name = "container") {
	typename ft::set<K, V>::key_compare kcomp = mappie.key_comp();
	(void)name;
	for (typename ft::set<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++) {
		if (kcomp(*it, compelem))
			std::cout << *it << " is lower than " << compelem << std::endl;
		else if (kcomp(compelem, *it))
			std::cout << *it << " is higher than " << compelem << std::endl;
		else
			std::cout << *it << " is equal to " << compelem << std::endl;
	}
}

//template< typename K, typename V>
//void	compare_values(ft::set<K, V>& mappie, K compelem = K(), const std::string& name = "container") {
//	typename ft::set<K, V>::value_compare vcomp = mappie.value_comp();
//	(void)name;
//	for (typename ft::set<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++) {
//		if (vcomp(*it, compelem))
//			std::cout << *it << " is lower than " << compelem << std::endl;
//		else if (vcomp(compelem, *it))
//			std::cout << *it << " is higher than " << compelem << std::endl;
//		else
//			std::cout << *it << " is equal to " << compelem << std::endl;
//	}
//}

ft::set<int>	getstdset() {
	ft::set<int> ret;
	ret.insert(10);
	ret.insert(7);
	ret.insert(6);
	ret.insert(13);
	ret.insert(1);
	ret.insert(4);
	ret.insert(3);
	ret.insert(8);
	ret.insert(14);
	ret.insert(8);
	return ret;
}	

void	ctors_dtor() {
	ft::set<int>	setje;
	setje.insert(0);
	setje.insert(1);
	setje.insert(2);
	setje.insert(1);
	setje.insert(-1);

	print_container_content(setje, "setje");
	ft::set<int> wetje(setje);
	wetje.insert(8);
	wetje.insert(7);
	wetje.insert(0);
	print_container_content(wetje, "wetje");
	ft::set<int>::iterator it = wetje.begin();
	for (int i = 0; i < 4; i++)
		++it;
	ft::set<int>	range2(wetje.begin(), it);
	print_container_content(range2, "range2");
}

void	iterators() {
	ft::set<int>	stdset = getstdset();
	ft::set<int>	peer;

	// testing if the container is empty
	if (peer.begin() == peer.end())
		std::cout << "begin is the same as end" << std::endl;
	else std::cout << "begin is NOTTTT the same as end" << std::endl;
	peer.insert(stdset.begin(), stdset.end());

	ft::set<int>::iterator					it = peer.begin();
	ft::set<int>::reverse_iterator			rit = peer.rbegin();
	ft::set<int>::const_reverse_iterator	crit(rit);				// Just testing if you can convert a regular iterator to a const one
	ft::set<int>::const_iterator 			cit(it);				// Just testing if you can convert a regular iterator to a const one
	std::cout << "it gives: " << *it << std::endl;
	std::cout << "cit gives: " << *cit << std::endl;
	std::cout << "rit gives: " << *rit << std::endl;
	std::cout << "crit gives: " << *crit << std::endl;

	// Testing if equal operators work
	if (it == cit)
		std::cout << "equal operator work on regular iterators " << *it << " and " << *cit << std::endl;
	if (rit == crit)
		std::cout << "equal operator work on reverse iterators " << *rit << " and " << *crit << std::endl;
	++it;
	it++;
	--it;
	it--;
	if (it != peer.end() && cit != peer.end())
		std::cout << "UNequal operator work on regular iterators " << (*it) << " and " << (*cit) << std::endl;
	if (rit != peer.rend() && crit != peer.rend())
		std::cout << "UNequal operator work on reverse iterators " << (*rit) << " and " << (*crit) << std::endl;
//	*it = 8;
	print_container_content(peer);
	int ret = *it++;
	std::cout << "ret: " << ret << std::endl;
	std::cout << " it: " << *it << std::endl;
}

void 	capacity() {
	ft::set<int>	stdmap = getstdset();
	std::cout << std::boolalpha << "mymap.empty() returns " << stdmap.empty() << std::endl;
	ft::set<int>	mymap(stdmap.begin(), stdmap.end());
	std::cout << std::boolalpha << "mymap.empty() returns " << mymap.empty() << std::endl;
	std::cout << "mymap.size() returns " << mymap.size() << std::endl;
// 	std::cout << "mymap.max_size() returns " << mymap.max_size() << std::endl;
}

void	modifiers() {
	ft::set<int> myset = getstdset();
	myset.insert(12);
	myset.insert(12);
	myset.insert(myset.find(7), 2);
//	 mymap.printBT();

	myset.erase(1);
	myset.erase(13);
	myset.erase(myset.find(4));
	myset.erase(7);
	for (ft::set<int>::iterator it = myset.begin(); it != myset.end(); it++) {
		std::cout << "it: " << *it << std::endl;
	}
	ft::set<int> emptyset;
	std::cout << "wtf" << std::endl;
	emptyset.swap(myset);
	print_container_content(myset);
	print_container_content(emptyset);
	std::cout << "wtf" << std::endl;
}

void	operations() {
	ft::set<int> myset = getstdset();
	print_container_content(myset);
	ft::set<int>::iterator it = myset.find(4);
	if (it == myset.end())
		std::cout << "element not found!" << std::endl;
	else std::cout << *it << std::endl;
	std::cout << "i have " << myset.count(1) << " elements with key = 1" << std::endl;
	std::cout << "i have " << myset.count(2) << " elements with key = 2" << std::endl;
	std::cout << "i have " << myset.count(3) << " elements with key = 3" << std::endl;

	it = myset.lower_bound(6);
	std::cout << "lower bound of 6 returns: " << *it << std::endl;
	it = myset.upper_bound(6);
	std::cout << "upper bound of 6 returns: " << *it << std::endl;
	it = myset.upper_bound(14);
	if (it != myset.end())
		std::cout << "upper bound of 14 returns: " << *it << std::endl;
	std::pair<ft::set<int>::iterator, ft::set<int>::iterator> peer \
	= myset.equal_range(10);
	std::cout << "mymap.equal_range(10) gives a range from " << *peer.first << " to " << *peer.second << std::endl;
}

void	observers() {
	ft::set<int>	myset;
	ft::set<int>	otherset;
	for (size_t i = 0; i < 20; i++) {
		myset.insert(i * 2);
		otherset.insert(i * 4);
	}
	compare_keys(myset, 18);
	compare_keys(otherset, 29);
//	compare_values(myset);
//	compare_values(otherset);
}

void	tellyinspired() {
	ft::set<int>::iterator it;
	ft::set<int> myset;
	myset.insert(18);
	myset.insert(30);
	myset.insert(22);
	myset.insert(17);
	myset.insert(15);

	ft::set<int> insertalot;
//	stdmap.printBT();
	for (size_t i = 0; i < 1000000; i++)
		insertalot.insert(i);

}

int	main(int argc, char **argv) {
	if (argc >= 2 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&tv, NULL);
		begintime = tv.tv_usec;
	}
	 ctors_dtor();
	 iterators();
	 capacity();
		modifiers();
	 observers();
	 operations();
//	 tellyinspired();
	if (argc >= 2 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&tv, NULL);
		endtime = tv.tv_usec;
		std::cerr << "Time elapsed in total! = " << endtime - begintime << " nanoseconds" << std::endl;
	}
	if (argc == 3 && strcmp(argv[2], "leaks") == 0 && !LINUX) {
		int a = system("leaks containers.out | grep \"total leaked bytes\" >&2");
		(void)a;
	}
}
