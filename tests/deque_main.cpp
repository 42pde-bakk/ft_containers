//
// Created by Peer De bakker on 10/24/20.
//

#include "Deque.hpp"
#include <deque>
#include <string>
#include <iostream>
#include <sys/time.h>
#include <cstring> // for strcmp
#include <stddef.h>
#include <stdlib.h> // for system()

# if defined(unix) || defined(__unix__) || defined(__unix)
#  define LINUX 1
# else
#  define LINUX 0
# endif

size_t begintime;
size_t endtime;
struct timeval	tv;

template< typename T>
void	print_container_content(ft::deque<T>& d, const std::string& name = "container") {
	std::cout << name << " contains:\n";
	for (typename ft::deque<T>::const_iterator it = d.begin(); it != d.end(); it++)
		std::cout << *it << std::endl;
	std::cout << " $" << std::endl;
}

//template< typename T>
//void	reverse_print_container_content(ft::deque<T>& d, const std::string& name = "container") {
//	std::cout << name << " in reverse contains:\n";
//	for (typename ft::deque<T>::const_reverse_iterator it = d.rbegin(); it != d.rend(); it++)
//		std::cout << *it << std::endl;
//	std::cout << " $" << std::endl;
//}

void	ctors_dtors() {
	ft::deque<int> def;
	def.push_back(80);
	print_container_content(def, "def");
	ft::deque<int> fill(8, 400);
	print_container_content(fill, "fill");
}

void	capacity() {
	ft::deque<int> eval;
	std::cout << std::boolalpha << "deque is empty? : " << eval.empty() << std::endl;
	for (int i = 0; i < 18; ++i)
		eval.push_back(i);
	std::cout << std::boolalpha << "deque is empty? : " << eval.empty() << std::endl;
	std::cout << "deque.size() = " << eval.size() << std::endl;
	std::cout << "deque.max_size() : " << eval.max_size() << std::endl;
	print_container_content(eval, "eval");
}

void	element_access() {
	ft::deque<int> oldtoothbrush;
	for (int i = 0; i < 389; ++i) {
		std::cout << "i is " << i << std::endl;
		// oldtoothbrush.push_back(i);
		oldtoothbrush.push_front(-i);
	}
	int access[] = {8, 87, 67, 9, 400, 700, 699};
	for (int i = 0; i < 6; ++i)
		std::cout << "deque[" << i << "] gives " << oldtoothbrush[i] << std::endl;
	try {
		for (int i = 0; i < 6; ++i)
			std::cout << "deque.at( " << i << " ) gives " << oldtoothbrush.at(access[i]) << std::endl;
		std::cout << "this one is going to throw an error: " << std::endl;
		std::cout << "deque.at(1000) gives: " << oldtoothbrush.at(1000) << std::endl;	
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::cout << "exception msg is allowed to differ from STL" << std::endl;
	}
	std::cout << "deque.front(): " << oldtoothbrush.front() << std::endl;
	std::cout << "deque.back(): " << oldtoothbrush.back() << std::endl;
}

void	eraser() {
	ft::deque<int> e;
	for (int i = 0; i < 19; i++)
		e.push_front(i);
	ft::deque<int>::iterator it = e.erase(e.begin() + 8, e.begin() + 12);
	std::cout << "return from erase gives: " << *it << std::endl;
	it = e.erase(e.begin() + 3);
	std::cout << "return from erase gives: " << *it << std::endl;
	print_container_content(e, "e");
}

void	iterators() {
	ft::deque<int> d;
	for (int i = 0; i < 8; ++i)
		d.push_back(i * 2);
	ft::deque<int>::iterator it = d.begin();
	ft::deque<int>::const_iterator cit(it++);
	cit = it + 2;
	std::cout << "operator==() gives " << std::boolalpha << (cit - 2 == it) << std::endl;
	std::cout << "operator!=() gives " << std::boolalpha << (cit - 2 != it) << std::endl;
	std::cout << "*cit = " << *cit << std::endl;
	*it = -1200;
	std::cout << "*it = -1200: " << *it << std::endl;
	std::cout << "++cit = " << *(++cit) << std::endl;
	std::cout << "cit++ = " << *(cit++) << std::endl;
	std::cout << "--cit = " << *(--cit) << std::endl;
	std::cout << "cit-- = " << *(cit--) << std::endl;
	std::cout << "*(cit + n) = " << *(cit + 4) << std::endl;
	std::cout << "*(cit - n) = " << *(cit - 1) << std::endl;
	std::cout << "cit - (cit - 2) = " << (cit - (cit - 2)) << std::endl;

	cit += 3;
	std::cout << "*cit = " << *cit << std::endl;
	cit -= 1;
	std::cout << "*cit = " << *cit << std::endl;
	std::cout << "it[3] = " << (it[3]) << std::endl;

// relational operators
	std::cout << "operator<() gives " << std::boolalpha << (cit - 2 < it) << std::endl;
	std::cout << "operator>() gives " << std::boolalpha << (cit - 2 > it) << std::endl;
	std::cout << "operator<=() gives " << std::boolalpha << (cit - 2 <= it) << std::endl;
	std::cout << "operator>=() gives " << std::boolalpha << (cit - 2 >= it) << std::endl;
//	std::cout << "*(cit + n) = " << *(3 + cit) << std::endl; //maybe handle this one too
	print_container_content(d);
}

int	main(int argc, char **argv) {
	if (argc >= 2 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&tv, NULL);
		begintime = tv.tv_usec;
	}
	// ctors_dtors();
	// capacity();
	// element_access();
	// eraser();
	iterators();
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
