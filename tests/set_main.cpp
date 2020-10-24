//
// Created by Peer De bakker on 10/24/20.
//

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

template< typename K >
void	print_container_content(ft::set<K>& mappie, const std::string& name = "container") {
	std::cout << name << " contains:\n";
	for (typename ft::set<K>::const_iterator it = mappie.begin(); it != mappie.end(); it++)
		std::cout << *it << std::endl;
	std::cout << " $" << std::endl;
}

void 	peer() {
	ft::set<char>	hats;
	hats.insert('a');
	hats.insert('b');
	hats.insert('a');
	hats.insert('d');

	print_container_content(hats);
	std::cout << "hats size = " << hats.size();
	std::cout << "count of 'a' = " << hats.count('a');
	std::cout << "count of 'b' = " << hats.count('b');
	std::cout << "count of 'c' = " << hats.count('c');
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
