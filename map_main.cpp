/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_main.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 21:10:23 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/11 18:10:22 by peerdb        ########   odam.nl         */
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
void	print_container_content(std::map<K, V>& mappie, std::string name = "container") {
	std::cout << name << " contains:";
	for (typename std::map<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++)
		std::cout << ' ' << it->second;
	std::cout << " $" << std::endl;
}

void	peer() {
	std::map<std::string, std::string> equal;
	std::map<std::string, std::string> oper;
	equal = oper;
	std::map<int, std::string> stl;
	stl[8] = "acht";
	stl[3] = "drie";
	stl[10] = "tien";
	stl[1] = "een";
	stl[6] = "tien";
	stl[14] = "veertien";
	stl[4] = "vier";
	stl[7] = "zeven";
	stl[13] = "dertien";
	print_container_content(stl, "stl");
	ft::map<std::string, std::string> peer;
	peer.insert(std::make_pair("hats", "pimpampet"));
	peer.insert(std::make_pair("pampa", "pierowet"));
	peer.insert(std::make_pair("abc", "tje"));
	// ft::map<std::string, std::string>::iterator it = peer.begin();
	// std::cout << "it: " << it->first << " => " << it->second << std::endl;
	// std::cout << "it: " << (*it).first << " => " << (*it).second << std::endl;
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
