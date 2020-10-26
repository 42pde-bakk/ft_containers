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

#include "MultiSet.hpp"
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
void	print_container_content(ft::multiset<K, V>& mappie, const std::string& name = "container") {
	std::cout << name << " contains:";
	for (typename ft::multiset<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++)
		std::cout << ' ' << *it;
	std::cout << " $" << std::endl;
}

template< typename K, typename V>
void	compare_keys(ft::multiset<K, V>& mappie, K compelem = K(), const std::string& name = "container") {
	typename ft::multiset<K, V>::key_compare kcomp = mappie.key_comp();
	(void)name;
	for (typename ft::multiset<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++) {
		if (kcomp(*it, compelem))
			std::cout << *it << " is lower than " << compelem << std::endl;
		else if (kcomp(compelem, *it))
			std::cout << *it << " is higher than " << compelem << std::endl;
		else
			std::cout << *it << " is equal to " << compelem << std::endl;
	}
}

//template< typename K, typename V>
//void	compare_values(ft::multiset<K, V>& mappie, K compelem = K(), const std::string& name = "container") {
//	typename ft::multiset<K, V>::value_compare vcomp = mappie.value_comp();
//	(void)name;
//	for (typename ft::multiset<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++) {
//		if (vcomp(*it, compelem))
//			std::cout << *it << " is lower than " << compelem << std::endl;
//		else if (vcomp(compelem, *it))
//			std::cout << *it << " is higher than " << compelem << std::endl;
//		else
//			std::cout << *it << " is equal to " << compelem << std::endl;
//	}
//}

ft::multiset<int>	getstdmultiset() {
	ft::multiset<int> ret;
	ret.insert(10);
	ret.insert(7);
	ret.insert(7);
	ret.insert(6);
	ret.insert(6);
	ret.insert(13);
	ret.insert(1);
	ret.insert(1);
	ret.insert(4);
	ret.insert(3);
	ret.insert(3);
	ret.insert(8);
	ret.insert(14);
	ret.insert(8);
	return ret;
}	

void	ctors_dtor() {
	ft::multiset<int>	multisetje;
	multisetje.insert(0);
	multisetje.insert(1);
	multisetje.insert(1);
	multisetje.insert(2);
	multisetje.insert(1);
	multisetje.insert(1);
	multisetje.insert(-1);

	print_container_content(multisetje, "multisetje");
	ft::multiset<int> wetje(multisetje);
	wetje.insert(8);
	wetje.insert(7);
	wetje.insert(0);
	print_container_content(wetje, "wetje");
	ft::multiset<int>::iterator it = wetje.begin();
	for (int i = 0; i < 4; i++)
		++it;
	ft::multiset<int>	range2(wetje.begin(), it);
	print_container_content(range2, "range2");
}

void	iterators() {
	ft::multiset<int>	stdmultiset = getstdmultiset();
	ft::multiset<int>	peer;

	// testing if the container is empty
	if (peer.begin() == peer.end())
		std::cout << "begin is the same as end" << std::endl;
	else std::cout << "begin is NOTTTT the same as end" << std::endl;
	peer.insert(stdmultiset.begin(), stdmultiset.end());

	ft::multiset<int>::iterator					it = peer.begin();
	ft::multiset<int>::reverse_iterator			rit = peer.rbegin();
	ft::multiset<int>::const_reverse_iterator	crit(rit);				// Just testing if you can convert a regular iterator to a const one
	ft::multiset<int>::const_iterator 			cit(it);				// Just testing if you can convert a regular iterator to a const one
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
	ft::multiset<int>	stdmap = getstdmultiset();
	std::cout << std::boolalpha << "mymap.empty() returns " << stdmap.empty() << std::endl;
	ft::multiset<int>	mymap(stdmap.begin(), stdmap.end());
	std::cout << std::boolalpha << "mymap.empty() returns " << mymap.empty() << std::endl;
	std::cout << "mymap.size() returns " << mymap.size() << std::endl;
// 	std::cout << "mymap.max_size() returns " << mymap.max_size() << std::endl;
}

void	modifiers() {
	ft::multiset<int> mymultiset = getstdmultiset();
	mymultiset.insert(12);
	mymultiset.insert(12);
	mymultiset.insert(mymultiset.find(7), 2);
//	 mymap.printBT();

	mymultiset.erase(1);
	mymultiset.erase(13);
	mymultiset.erase(mymultiset.find(4));
	mymultiset.erase(7);
	for (ft::multiset<int>::iterator it = mymultiset.begin(); it != mymultiset.end(); it++) {
		std::cout << "it: " << *it << std::endl;
	}
	ft::multiset<int> emptymultiset;
	std::cout << "wtf" << std::endl;
	emptymultiset.swap(mymultiset);
	print_container_content(mymultiset);
	print_container_content(emptymultiset);
	std::cout << "wtf" << std::endl;
}

void	operations() {
	ft::multiset<int> mymultiset = getstdmultiset();
	print_container_content(mymultiset);
	ft::multiset<int>::iterator it = mymultiset.find(4);
	if (it == mymultiset.end())
		std::cout << "element not found!" << std::endl;
	else std::cout << *it << std::endl;
	std::cout << "i have " << mymultiset.count(1) << " elements with key = 1" << std::endl;
	std::cout << "i have " << mymultiset.count(2) << " elements with key = 2" << std::endl;
	std::cout << "i have " << mymultiset.count(3) << " elements with key = 3" << std::endl;

	it = mymultiset.lower_bound(6);
	std::cout << "lower bound of 6 returns: " << *it << std::endl;
	it = mymultiset.upper_bound(6);
	std::cout << "upper bound of 6 returns: " << *it << std::endl;
	it = mymultiset.upper_bound(14);
	if (it != mymultiset.end())
		std::cout << "upper bound of 14 returns: " << *it << std::endl;
	std::pair<ft::multiset<int>::iterator, ft::multiset<int>::iterator> peer \
	= mymultiset.equal_range(10);
	std::cout << "mymap.equal_range(10) gives a range from " << *peer.first << " to " << *peer.second << std::endl;
}

void	observers() {
	ft::multiset<int>	mymultiset;
	ft::multiset<int>	othermultiset;
	for (size_t i = 0; i < 20; i++) {
		mymultiset.insert(i * 2);
		othermultiset.insert(i * 4);
	}
	compare_keys(mymultiset, 18);
	compare_keys(othermultiset, 29);
//	compare_values(mymultiset);
//	compare_values(othermultiset);
}

void	tellyinspired() {
	ft::multiset<int>::iterator it;
	ft::multiset<int> mymultiset;
	mymultiset.insert(18);
	mymultiset.insert(30);
	mymultiset.insert(22);
	mymultiset.insert(17);
	mymultiset.insert(15);

	ft::multiset<int> insertalot;
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
