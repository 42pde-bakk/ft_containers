/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack_main.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/16 14:56:39 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/19 15:57:36 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/Stack/Stack.hpp"
#include <cstring>
#include <stack>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sys/time.h>

# if defined(unix) || defined(__unix__) || defined(__unix)
#  define LINUX 1
# else
#  define LINUX 0
# endif

size_t begintime;
size_t endtime;
struct timeval	tv;

void	peer() {
	ft::stack<int>	mystack;
	ft::stack<int>	otherstack;
	for (size_t i = 0; i < 10; i++)
		mystack.push(i * 8);
	std::cout << std::boolalpha << "mystack.empty( ) = " << mystack.empty() << std::endl;
	std::cout << std::boolalpha << "otherstack.empty( ) = " << otherstack.empty() << std::endl;
	std::cout << "first top: " << mystack.top() << std::endl;
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
	return 0;
}
