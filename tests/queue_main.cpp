/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_main.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/16 14:56:39 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/20 15:04:51 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Queue.hpp"
#include <cstring>
#include <queue>
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
		ft::queue<int> MyQueue;
		std::cout << MyQueue.empty() << std::endl;
		std::cout << MyQueue.size() << std::endl;
	}
	std::cout << std::endl;
	{
		ft::queue<int> MyQueue;
		std::cout << MyQueue.empty() << std::endl;
		MyQueue.push(88);
		std::cout << MyQueue.back() << std::endl;
		MyQueue.push(44);
		std::cout << MyQueue.back() << std::endl;
		std::cout << MyQueue.size() << std::endl;
		MyQueue.pop();
		std::cout << MyQueue.size() << std::endl;
		std::cout << MyQueue.back() << std::endl;
		MyQueue.pop();
		std::cout << MyQueue.size() << std::endl;
	}
	std::cout << std::endl;
	{
		ft::queue<int> MyQueue;
		std::cout << MyQueue.empty() << std::endl;
		MyQueue.push(88);
		std::cout << MyQueue.front() << std::endl;
		MyQueue.push(44);
		std::cout << MyQueue.front() << std::endl;
		std::cout << MyQueue.size() << std::endl;
		MyQueue.pop();
		std::cout << MyQueue.size() << std::endl;
		std::cout << MyQueue.front() << std::endl;
		MyQueue.pop();
		std::cout << MyQueue.size() << std::endl;
	}
	{
		ft::queue<int> MyQueue1;
		ft::queue<int> MyQueue2;

		MyQueue1.push(100);
		MyQueue1.push(44);

		MyQueue2.push(100);
		MyQueue2.push(44);

		if (MyQueue1 == MyQueue2)
			std::cout << "MyQueue1 is equal to MyQueue2" << std::endl;
		if (MyQueue1 < MyQueue2)
			std::cout << "MyQueue1 is smaller than MyQueue2" << std::endl;
		if (MyQueue1 <= MyQueue2)
			std::cout << "MyQueue1 is smaller than or equal to MyQueue2" << std::endl;
		if (MyQueue1 > MyQueue2)
			std::cout << "MyQueue1 is larger than MyQueue2" << std::endl;
		if (MyQueue1 >= MyQueue2)
			std::cout << "MyQueue1 is larger than or equal to MyQueue2" << std::endl;
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
