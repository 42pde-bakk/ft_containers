//
// Created by Peer De bakker on 10/26/20.
//

#ifndef FT_CONTAINERS_DEQUEITERATOR_H
#define FT_CONTAINERS_DEQUEITERATOR_H

#include <cstddef>

template <class T, size_t buff_size>
struct	DequeIterator {
	typedef DequeIterator<T, buff_size>		iterator;
	typedef T&								reference;
	typedef T**								map_pointer;

	// pointer to the chunk
	T*	cur;
	T*	first; // The beginning of the chunk
	T*	last; // The end of the chunk

	//because the pointer may skip to other chunk
	//so this pointer to the map
	map_pointer node; // pointer to the map

	void	set_node(map_pointer new_node) {
		node = new_node;
		first = *new_node;
		last = first + buff_size;
	}
	reference operator*() const {
		return *cur;
	}
	iterator& operator++() {
		++cur;
		if (cur == last) {	// if it reaches the end of the chunk
			set_node(node + 1); // skip to the next chunk
			cur = first;
//			last = first + buff_size;
		}
	}
	// postfix forms of increment
	iterator operator++(int){
		iterator tmp = *this;
		++*this;//invoke prefix ++
		return tmp;
	}
	iterator& operator--(){
		if(cur == first){      // if it pointer to the begin of the chunk
			set_node(node - 1);//skip to the prev chunk
			cur = last;
		}
		--cur;
		return *this;
	}

	iterator operator--(int){
		iterator tmp = *this;
		--*this;
		return tmp;
	}
	iterator& operator+=(ptrdiff_t n){ // n can be postive or negative
		ptrdiff_t offset = n + (cur - first);
		if(offset >=0 && offset < ptrdiff_t(buff_size)){
			// in the same chunk
			cur += n;
		}else{//not in the same chunk
			ptrdiff_t node_offset;
			if (offset > 0){
				node_offset = offset / ptrdiff_t(buff_size);
			}else{
				node_offset = -((-offset - 1) / ptrdiff_t(buff_size)) - 1 ;
			}
			// skip to the new chunk
			set_node(node + node_offset);
			// set new cur
			cur = first + (offset - node_offset * buff_size);
		}

		return *this;
	}

// skip n steps
	iterator operator+(ptrdiff_t n)const{
		iterator tmp = *this;
		return tmp+= n; //reuse  operator +=
	}

	iterator& operator-=(ptrdiff_t n){
		return *this += -n; //reuse operator +=
	}

	iterator operator-(ptrdiff_t n)const{
		iterator tmp = *this;
		return tmp -= n; //reuse operator +=
	}

// random access (iterator can skip n steps)
// invoke operator + ,operator *
	reference operator[](ptrdiff_t n)const{
		return *(*this + n);
	}
};

#endif //FT_CONTAINERS_DEQUEITERATOR_H
