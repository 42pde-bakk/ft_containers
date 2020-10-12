/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_main.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 21:10:23 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/12 15:46:42 by pde-bakk      ########   odam.nl         */
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



void	peer() {
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
	ft::map<int, std::string> peer(stl.begin(), stl.end());
	std::pair<int, std::string> compPair = std::make_pair(10, "tien");
	stl_compare_values(stl, compPair, "realstl");
	stl_compare_keys(stl, 10, "realstl");
	std::cout << std::endl;
	compare_values(peer, compPair, "peerstl");
	compare_keys(peer, 10, "peerstl");
	std::cout << std::endl;
	// print_container_content(peer, "peerstl");
}

int	main(int argc, char **argv) {
	if (argc >= 2 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&tv, NULL);
		begintime = tv.tv_usec;
	}
	peer();
	if (argc >= 2 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&tv, NULL);
		endtime = tv.tv_usec;
		std::cout << "Time elapsed in total! = " << endtime - begintime << " nanoseconds" << std::endl;
	}
	if (argc == 3 && strcmp(argv[2], "leaks") == 0)
		system("leaks containers.out | grep \"total leaked bytes\"");
}
