/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_main.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 21:10:23 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/13 19:23:20 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/Map/Map.hpp"
#include <map>
#include <string>
#include <iostream>
#include <sys/time.h>

size_t begintime;
size_t endtime;
struct timeval	tv;

template< typename K, typename V >
void	print_container_content(ft::map<K, V>& mappie, std::string name = "container") {
	std::cout << name << " contains:";
	for (typename ft::map<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++)
		std::cout << ' ' << it->second;
	std::cout << " $" << std::endl;
}
template< typename K, typename V >
void	stl_print_container_content(std::map<K, V>& mappie, std::string name = "container") {
	std::cout << name << " contains:";
	for (typename std::map<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++)
		std::cout << ' ' << it->second;
	std::cout << " $" << std::endl;
}
template< typename K, typename V>
void	compare_keys(ft::map<K, V>& mappie, K compelem = K(), std::string name = "container") {
	typename ft::map<K, V>::key_compare kcomp = mappie.key_comp();
	(void)name;
	for (typename ft::map<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++) {
		if (kcomp(it->first, compelem))
			std::cout << it->first << " is lower than " << compelem << std::endl;
		else if (kcomp(compelem, it->first))
			std::cout << it->first << " is higher than " << compelem << std::endl;
		else
			std::cout << it->first << " is equal to " << compelem << std::endl;
	}
}
template< typename K, typename V>
void	stl_compare_keys(std::map<K, V>& mappie, K compelem = K(), std::string name = "container") {
	typename std::map<K, V>::key_compare kcomp = mappie.key_comp();
	(void)name;
	for (typename std::map<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++) {
		if (kcomp(it->first, compelem))
			std::cout << it->first << " is lower than " << compelem << std::endl;
		else if (kcomp(compelem, it->first))
			std::cout << it->first << " is higher than " << compelem << std::endl;
		else
			std::cout << it->first << " is equal to " << compelem << std::endl;
	}
}
template< typename K, typename V>
void	compare_values(ft::map<K, V>& mappie, std::pair<K, V> compelem, std::string name = "container") {
	typename ft::map<K, V>::value_compare vcomp = mappie.value_comp();
	(void)name;
	for (typename ft::map<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++) {
		if (vcomp(*it, compelem))
			std::cout << it->first << " is lower than " << compelem.first << std::endl;
		else if (vcomp(compelem, *it))
			std::cout << it->first << " is higher than " << compelem.first << std::endl;
		else
			std::cout << it->first << " is equal to " << compelem.first << std::endl;
	}
}
template< typename K, typename V>
void	stl_compare_values(std::map<K, V>& mappie, std::pair<K, V> compelem, std::string name = "container") {
	typename std::map<K, V>::value_compare vcomp = mappie.value_comp();
	(void)name;
	for (typename std::map<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++) {
		if (vcomp(*it, compelem))
			std::cout << it->first << " is lower than " << compelem.first << std::endl;
		else if (vcomp(compelem, *it))
			std::cout << it->first << " is higher than " << compelem.first << std::endl;
		else
			std::cout << it->first << " is equal to " << compelem.first << std::endl;
	}
}

std::map<int, std::string>	getstlmap() {
	std::map<int, std::string> stl;
	stl[8] = "acht";
	stl[3] = "drie";
	stl[10] = "tien";
	stl[1] = "een";
	stl[6] = "zes";
	stl[14] = "veertien";
	stl[4] = "vier";
	stl[7] = "zeven";
	stl[13] = "dertien";
	return stl;
}

void	ctors_dtor() {
	std::map<int, std::string> stl = getstlmap();
	ft::map<int, std::string>	mydefault; // testing default ctor
	mydefault.insert(std::make_pair(5, "vijf"));
	ft::map<int, std::string>	mycopy(mydefault); // testing copy ctor
	print_container_content(mydefault);
	print_container_content(mycopy);
	ft::map<int, std::string> myfill(stl.begin(), stl.end());
	print_container_content(myfill);
}

void	iterators() {
	std::map<int, std::string>	stl = getstlmap();
	ft::map<int, std::string>	peer;

	// testing if the container is empty
	if (peer.begin() == peer.end())
		std::cout << "begin is the same as end" << std::endl;
	else std::cout << "begin is NOTTTT the same as end" << std::endl;
	peer.insert(stl.begin(), stl.end());

	ft::map<int, std::string>::iterator it = peer.begin();
	ft::map<int, std::string>::reverse_iterator rit = peer.rbegin();
	ft::map<int, std::string>::const_reverse_iterator crit(rit);	// Just testing if you can convert a regular iterator to a const one
	ft::map<int, std::string>::const_iterator cit(it);				// Just testing if you can convert a regular iterator to a const one
	std::cout << "it gives: " << it->first << " ===> " << it->second << std::endl;
	std::cout << "cit gives: " << cit->first << " ===> " << cit->second << std::endl;
	std::cout << "rit gives: " << rit->first << " ===> " << rit->second << std::endl;
	std::cout << "crit gives: " << crit->first << " ===> " << crit->second << std::endl;

	// Testing if equal operators work
	if (it == cit)
		std::cout << "equal operator work on regular iterators " << it->first << " and " << cit->first << std::endl;
	if (rit == crit)
		std::cout << "equal operator work on reverse iterators " << rit->first << " and " << crit->first << std::endl;
	++it;
	it++;
	--it;
	it--;
	if (it != peer.end() && cit != peer.end())
		std::cout << "UNequal operator work on regular iterators " << (*it).first << " and " << (*cit).first << std::endl;
	if (rit != peer.rend() && crit != peer.rend())
		std::cout << "UNequal operator work on reverse iterators " << (*rit).first << " and " << (*crit).first << std::endl;
	it->second = "NIEUW";
	print_container_content(peer);
	std::pair<int, std::string> ret = *it++;
	std::cout << "ret: " << ret.first << " => " << ret.second << std::endl;
	std::cout << " it: " << it->first << " => " << it->second << std::endl;
}

void 	capacity() {
	std::map<int, std::string>	stl = getstlmap();
	ft::map<int, std::string>	mymap(stl.begin(), stl.end());
	std::cout << std::boolalpha << "mymap.empty() returns " << mymap.empty() << std::endl;
	std::cout << "mymap.size() returns " << mymap.size() << std::endl;
	std::cout << "mymap.max_size() returns " << mymap.max_size() << std::endl;
}
int	main(int argc, char **argv) {
	if (argc >= 2 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&tv, NULL);
		begintime = tv.tv_usec;
	}
	// ctors_dtor();
	iterators();
	capacity();
	if (argc >= 2 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&tv, NULL);
		endtime = tv.tv_usec;
		std::cout << "Time elapsed in total! = " << endtime - begintime << " nanoseconds" << std::endl;
	}
	if (argc == 3 && strcmp(argv[2], "leaks") == 0)
		system("leaks containers.out | grep \"total leaked bytes\"");
}
