/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 22:05:58 by peerdb        #+#    #+#                 */
/*   Updated: 2020/11/05 22:54:52 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <iostream>
#include <string>
#include "srcs/list/List.hpp"

int main( ) {
	ft::list<int> hats(6, 42);

	ft::list<int>::iterator it = hats.begin();
	ft::list<int>::const_iterator cit;
	cit = it;
	ft::list<int>::const_iterator connie(cit++);
}
