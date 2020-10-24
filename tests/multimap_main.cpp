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
void	print_container_content(ft::multimap<K, V>& mappie, std::string name = "container") {
	std::cout << name << " contains:\n";
	for (typename ft::multimap<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++)
		std::cout << it->first << " => " << it->second << std::endl;
	std::cout << " $" << std::endl;
}

void 	peer() {
	ft::multimap<char, int>	hats;
	hats.insert(std::make_pair('a', 0));
	hats.insert(std::make_pair('a', 1));
	hats.insert(std::make_pair('a', 2));
	hats.insert(std::make_pair('a', 3));
	hats.insert(std::make_pair('c', 4));
	hats.insert(std::make_pair('c', 5));

	print_container_content(hats);
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
		std::cerr << "Time elapsed in total! = " << endtime - begintime << " nanoseconds" << std::endl;
	}
	if (argc == 3 && strcmp(argv[2], "leaks") == 0 && !LINUX) {
		int a = system("leaks containers.out | grep \"total leaked bytes\" >&2");
		(void)a;
	}
}
