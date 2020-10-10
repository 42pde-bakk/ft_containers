/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_main.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 21:10:23 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/10 14:47:15 by pde-bakk      ########   odam.nl         */
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

// template< typename T >
// void	print_container_content(ft::map<T> &vec, std::string name = "container") {
// 	std::cout << name << " contains:";
// 	for (ft::map<int>::iterator it = vec.begin(); it != vec.end(); it++)
// 		std::cout << ' ' << *it;
// 	std::cout << " $" << std::endl;
// }

void	peer() {
	ft::map<std::string, std::string> peer;
	ft::map<std::string, std::string> papa;
	papa = peer;
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
