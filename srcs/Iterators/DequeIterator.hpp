//
// Created by Peer De bakker on 10/26/20.
//

#ifndef FT_CONTAINERS_DEQUEITERATOR_H
#define FT_CONTAINERS_DEQUEITERATOR_H

#include <cstddef>
#include <iostream>

template <class T>
class	DequeIterator {
public:
	typedef DequeIterator<T>	iterator;
	typedef T					value_type;
	typedef	size_t				size_type;
	typedef ptrdiff_t			difference_type;
	typedef T*					pointer;
	typedef const T*			const_pointer;
	typedef T&					reference;
	typedef const T&			const_reference;
	typedef T**					map_pointer;
protected:
	const pointer* p;
public:
	DequeIterator() : p(0) {}
	DequeIterator(const DequeIterator& x) : p(x.p) {}
	DequeIterator(const pointer *p) : p(p) {}
	virtual ~DequeIterator() {}
	reference		operator*() { return (**this->p); }
	const_reference	operator*() const { return (**this->p); }
	pointer			operator->() { return (*this->p); }
	const_pointer	operator->() const { return (*this->p); }
	reference			operator[](int n) { return (**(this->p + n)); }
	const_reference		operator[](int n) const { return (**(this->p + n)); }

	DequeIterator operator++(int) {
		DequeIterator tmp(*this);
		++this->p;
		return (tmp);
	}
	DequeIterator &operator++() {
		++this->p;
		return (*this);
	}
	DequeIterator operator--(int) {
		DequeIterator tmp(*this);
		--this->p;
		return (tmp);
	}
	DequeIterator &operator--() {
		--this->p;
		return (*this);
	}

	DequeIterator &operator+=(int value) {
		this->p += value;
		return (*this);
	}
	DequeIterator operator+(int value) const {
		DequeIterator tmp(*this);
		return (tmp += value);
	}
	DequeIterator &operator-=(int value) {
		this->p -= value;
		return (*this);
	}
	DequeIterator operator-(int value) const {
		DequeIterator tmp(*this);
		return (tmp -= value);
	}
	difference_type operator-(DequeIterator const &other) const {
		return (this->p - other.p);
	}

	bool operator==(DequeIterator const &other) const {
		return (this->p == other.p);
	}
	bool operator!=(DequeIterator const &other) const {
		return (this->p != other.p);
	}
	bool operator<(DequeIterator const &other) const {
		return (this->p < other.p);
	}
	bool operator<=(DequeIterator const &other) const {
		return (this->p <= other.p);
	}
	bool operator>(DequeIterator const &other) const {
		return (this->p > other.p);
	}
	bool operator>=(DequeIterator const &other) const {
		return (this->p >= other.p);
	}
};

#endif //FT_CONTAINERS_DEQUEITERATOR_H
