//
// Created by Peer De bakker on 10/24/20.
//

#include "Multimap.hpp"
//#include "../srcs/multimap/Multimap.hpp"
#include <map>
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
void	print_container_content(ft::multimap<K, V>& mappie, const std::string& name = "container") {
	std::cout << name << " contains:" << std::endl;
	for (typename ft::multimap<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++)
		std::cout << it->first << " => " << it->second << std::endl;
	std::cout << " $" << std::endl;
}

template< typename K, typename V>
void	compare_keys(ft::multimap<K, V>& mappie, K compelem = K(), const std::string& name = "container") {
	typename ft::multimap<K, V>::key_compare kcomp = mappie.key_comp();
	(void)name;
	for (typename ft::multimap<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++) {
		if (kcomp(it->first, compelem))
			std::cout << it->first << " is lower than " << compelem << std::endl;
		else if (kcomp(compelem, it->first))
			std::cout << it->first << " is higher than " << compelem << std::endl;
		else
			std::cout << it->first << " is equal to " << compelem << std::endl;
	}
}

template< typename K, typename V>
void	compare_values(ft::multimap<K, V>& mappie, std::pair<K, V> compelem = std::make_pair(K(), V()), const std::string& name = "container") {
	typename ft::multimap<K, V>::value_compare vcomp = mappie.value_comp();
	(void)name;
	for (typename ft::multimap<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++) {
		if (vcomp(*it, compelem))
			std::cout << it->first << " is lower than " << compelem.first << std::endl;
		else if (vcomp(compelem, *it))
			std::cout << it->first << " is higher than " << compelem.first << std::endl;
		else
			std::cout << it->first << " is equal to " << compelem.first << std::endl;
	}
}

ft::multimap<int, std::string>	getstdmultimap() {
	ft::multimap<int, std::string> ret;
	ret.insert(std::make_pair(0, "nul"));
	ret.insert(std::make_pair(10, "tien"));
	ret.insert(std::make_pair(6, "zes"));
	ret.insert(std::make_pair(5, "vijf"));
	ret.insert(std::make_pair(-2, "min twee"));
	ret.insert(std::make_pair(1, "een"));
	ret.insert(std::make_pair(0, "nul-1"));
	ret.insert(std::make_pair(9, "negen"));
	ret.insert(std::make_pair(10, "tien-1"));
	ret.insert(std::make_pair(3, "drie"));
	ret.insert(std::make_pair(-5, "min vijf"));
	ret.insert(std::make_pair(-5 , "min vijf-1"));
	ret.insert(std::make_pair(-5 , "min vijf-2"));
	return ret;
}

void 	ctors_dtors() {
	ft::multimap<int, std::string>	mappie;
	mappie.insert(std::make_pair(0, "nul"));
	mappie.insert(std::make_pair(1, "een"));
	mappie.insert(std::make_pair(1, "een-1"));
	mappie.insert(std::make_pair(1, "een-2"));
	mappie.insert(std::make_pair(-1, "min een"));
	mappie.insert(std::make_pair(5, "vijf"));

	print_container_content(mappie, "mappie");
	ft::multimap<int, std::string> wappie(mappie);
	wappie.insert(std::make_pair(8, "acht"));
	wappie.insert(std::make_pair(7, "zeven"));
	wappie.insert(std::make_pair(7, "zeven-1"));
	print_container_content(wappie, "wappie");
	ft::multimap<int, std::string>::iterator it = wappie.begin();
	for (int i = 0; i < 4; i++)
		++it;
	ft::multimap<int, std::string>	range2(wappie.begin(), it);
	print_container_content(range2, "range2");
	range2 = mappie;
	print_container_content(range2, "range2 after operator=");
	if (range2 == mappie)
		std::cout << "het werrkt" << std::endl;
}

void	iterators() {
	ft::multimap<int, std::string>	mappie = getstdmultimap();
	ft::multimap<int, std::string>::iterator it = mappie.begin();
	ft::multimap<int, std::string>::const_iterator cite = --mappie.end();
	ft::multimap<int, std::string>::reverse_iterator rit(mappie.rbegin());
	ft::multimap<int, std::string>::const_reverse_iterator crite(--mappie.rend());
	std::cout << "it gives: " << it->first << " ===> " << it->second << std::endl;
	std::cout << "cit gives: " << cite->first << " ===> " << cite->second << std::endl;
	std::cout << "rit gives: " << rit->first << " ===> " << rit->second << std::endl;
	std::cout << "crit gives: " << crite->first << " ===> " << crite->second << std::endl;
	// Testing if equal operators work
	if (it == cite)
		std::cout << "equal operator work on regular iterators " << it->first << " and " << cite->first << std::endl;
	if (rit == crite)
		std::cout << "equal operator work on reverse iterators " << rit->first << " and " << crite->first << std::endl;
	++it;
	it++;
	--it;
	it--;
	if (it != mappie.end() && cite != mappie.end())
		std::cout << "UNequal operator work on regular iterators " << (*it).first << " and " << (*cite).first << std::endl;
	if (rit != mappie.rend() && crite != mappie.rend())
		std::cout << "UNequal operator work on reverse iterators " << (*rit).first << " and " << (*crite).first << std::endl;
	it->second = "NIEUEEEEW";
	print_container_content(mappie, "mappie");
	std::pair<int, std::string> ret = *it++;
	std::cout << "ret: " << ret.first << " => " << ret.second << std::endl;
	std::cout << " it: " << it->first << " => " << it->second << std::endl;
}

void	capacity() {
	ft::multimap<int, std::string>	peer;
	std::cout << std::boolalpha << "is peer empty?: " << peer.empty() << std::endl;
	peer = getstdmultimap();
	std::cout << std::boolalpha << "is peer empty?: " << peer.empty() << std::endl;
	std::cout << "peer.size(): " << peer.size() << std::endl;
	std::cout << "peer.max_size(): " << peer.max_size() << std::endl;
}

void 	modifiers() {
	ft::multimap<int, std::string>	stdmulti = getstdmultimap();
	ft::multimap<int, std::string>	newmulti;
	newmulti.insert(std::make_pair(8, "octo"));
	newmulti.insert(std::make_pair(INT_MAX, "int maxie"));
	newmulti.insert(stdmulti.begin(), stdmulti.end());
	newmulti.erase(newmulti.find(1));
	size_t erased = newmulti.erase(10);
	std::cout << "erasing key1 returns: " << erased << std::endl;
	print_container_content(newmulti, "newmulti");
	newmulti.clear();
}

void	observers() {
	ft::multimap<int, int>	mymap;
	ft::multimap<int, int>	othermap;
	for (size_t i = 0; i < 20; i++) {
		mymap.insert(std::make_pair(i * 2, i * 4));
		mymap.insert(std::make_pair(i * 3, i * 6));
	}
	compare_keys(mymap, 18);
	compare_keys(othermap, 29);
	compare_values(mymap, std::make_pair(18, 45));
	compare_values(othermap, std::make_pair(29, 76));
}

void	operations() {
	ft::multimap<int, std::string> mymap = getstdmultimap();
	ft::multimap<int, std::string>::iterator it = mymap.find(10);
	ft::multimap<int, std::string>::iterator it2;
	std::cout << "it = map.find(1), it: " << it->first << " => " << it->second << std::endl;
	std::cout << "map.count(10) gives " << mymap.count(10) << std::endl;
	std::cout << "map.count(-10) gives " << mymap.count(-10) << std::endl;
	std::cout << "map.count(2) gives " << mymap.count(2) << std::endl;
	it = mymap.lower_bound(6);
	std::cout << "it = map.lower_bound(6), it: " << it->first << " => " << it->second << std::endl;
	it = mymap.upper_bound(6);
	std::cout << "it = map.upper_bound(6), it: " << it->first << " => " << it->second << std::endl;
	std::pair<ft::multimap<int, std::string>::iterator, ft::multimap<int, std::string>::iterator> itpair = mymap.equal_range(
			-5);
	std::cout << "it = map.equal_range(-5), itpair.first: " << itpair.first->first << " => " << itpair.first->second
			  << std::endl;
	std::cout << "it = map.equal_range(-5), itpair.second: " << itpair.second->first << " => " << itpair.second->second
			  << std::endl;
}

int	main(int argc, char **argv) {
	if (argc >= 2 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&tv, NULL);
		begintime = tv.tv_usec;
	}

	ctors_dtors();
	iterators();
	capacity();
	modifiers();
	observers();
	operations();

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
