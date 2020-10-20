/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack_main.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/16 14:56:39 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/20 15:04:56 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Stack.hpp"
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

void	telly() {
	{
		ft::stack<int> MyStack;
		std::cout << MyStack.empty() << std::endl;
		std::cout << MyStack.size() << std::endl;
	}
	std::cout << std::endl;
	{
		ft::stack<int> MyStack;
		std::cout << MyStack.empty() << std::endl;
		MyStack.push(88);
		std::cout << MyStack.top() << std::endl;
		MyStack.push(44);
		std::cout << MyStack.top() << std::endl;
		std::cout << MyStack.size() << std::endl;
		MyStack.pop();
		std::cout << MyStack.size() << std::endl;
		std::cout << MyStack.top() << std::endl;
		MyStack.pop();
		std::cout << MyStack.size() << std::endl;
	}
	{
		ft::stack<int> MyStack1;
		ft::stack<int> MyStack2;

		MyStack1.push(100);
		MyStack1.push(44);

		MyStack2.push(100);
		MyStack2.push(44);

		if (MyStack1 == MyStack2)
			std::cout << "MyStack1 is equal to MyStack2" << std::endl;
		if (MyStack1 < MyStack2)
			std::cout << "MyStack1 is smaller than MyStack2" << std::endl;
		if (MyStack1 <= MyStack2)
			std::cout << "MyStack1 is smaller than or equal to MyStack2" << std::endl;
		if (MyStack1 > MyStack2)
			std::cout << "MyStack1 is larger than MyStack2" << std::endl;
		if (MyStack1 >= MyStack2)
			std::cout << "MyStack1 is larger than or equal to MyStack2" << std::endl;
	}
}


int	main(int argc, char **argv) {
	if (argc >= 2 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&tv, NULL);
		begintime = tv.tv_usec;
	}
	telly();

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
