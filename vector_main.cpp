/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_main.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 21:10:23 by peerdb        #+#    #+#                 */
/*   Updated: 2020/09/26 01:22:04 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/Vector/Vector.hpp"
#include <vector>
#include <string>
#include <iostream>

template<typename T>
void	print_container_content(ft::vector<T> vec, std::string name) {
	std::cout << name << " contains:";
	for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

void	peer() {
	ft::vector<int>	peer(6, 42);
	for (int i = 0; i < 6; i++)
		peer[i] = i;
	// print_container_content(peer, "peer");
	ft::vector<int>::iterator it = peer.begin();
	it += 2;
	peer.erase(it);
	std::cout << "peer" << " contains:";
	for (it = peer.begin(); it != peer.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	// peer.clear();
	std::cout << "peer.size = " << peer.size() << ", cap = " << peer.capacity() << std::endl;
}

int	main() {
	peer();
}