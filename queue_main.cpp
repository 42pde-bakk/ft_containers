/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_main.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/16 14:56:39 by peerdb        #+#    #+#                 */
/*   Updated: 2020/10/16 15:53:48 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/Queue/Queue.hpp"
#include <cstring>
#include <queue>
#include <string>
#include <iostream>
#include <sys/time.h>

size_t begintime;
size_t endtime;
struct timeval	tv;

void	peer() {
	ft::queue<int>	peer;
	ft::queue<int>	hats;
	peer.push(8);
	hats.push(8);
	if (peer == hats)
		std::cout << "yeah we equal" << std::endl;
	else
		std::cout << "not equal ffs" << std::endl;
	if (peer != hats)
		std::cout << "yeah we not equal" << std::endl;
	else
		std::cout << "equal ffs" << std::endl;
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
	// if (argc == 3 && strcmp(argv[2], "leaks") == 0)
	// 	system("leaks containers.out | grep \"total leaked bytes\"");
}