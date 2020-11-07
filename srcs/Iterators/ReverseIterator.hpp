//
// Created by Peer De bakker on 11/7/20.
//

#ifndef FT_CONTAINERS_REVERSEITERATOR_HPP
#define FT_CONTAINERS_REVERSEITERATOR_HPP

template <class Iterator >
class BidirectionalIterator {
protected:
	Iterator	current;
public:
	typedef Iterator							iterator_type;
	typedef typename Iterator::pointer			pointer;
	typedef typename Iterator::reference		reference;
	typedef typename Iterator::size_type		size_type;
	typedef typename Iterator::difference_type	difference_type;
	typedef typename Iterator::iterator_category	iterator_category;

	BidirectionalIterator() : current() { }
	BidirectionalIterator(const iterator_type& x) : current(x) { }
	BidirectionalIterator(const BidirectionalIterator& x) : current(x.current) { }
	template<typename Iter>
	BidirectionalIterator(const BidirectionalIterator<Iter>& x) : current(x.base()) { } //.base() returns the underlying iterator
	~BidirectionalIterator() { }
	BidirectionalIterator&	operator=(const BidirectionalIterator& x) {
		Iterator::operator=(x);
		return *this;
	}
	iterator_type	base() const { return this->current; }

	reference	operator*() {
		return *current;
	}
	pointer		operator->() {
		return &operator*();
	}
	BidirectionalIterator&	operator++() {
		--current;
		return *this;
	}
	BidirectionalIterator	operator++(int) {
		BidirectionalIterator	tmp(*this);
		--current;
		return tmp;
	}
	BidirectionalIterator&	operator--() {
		++current;
		return *this;
	}
	BidirectionalIterator	operator--(int) {
		BidirectionalIterator	tmp(*this);
		++current;
		return *this;
	}
};
template <typename Iterator>
inline bool	operator==(const BidirectionalIterator<Iterator>& lhs, const BidirectionalIterator<Iterator>& rhs) {
	return (lhs.base() == rhs.base());
}
template <typename Iterator>
inline bool	operator<(const BidirectionalIterator<Iterator>& lhs, const BidirectionalIterator<Iterator>& rhs) {
	return (lhs.base() < rhs.base());
}
template <typename Iterator>
inline bool	operator!=(const BidirectionalIterator<Iterator>& lhs, const BidirectionalIterator<Iterator>& rhs) {
	return !(lhs == rhs);
}
template <typename Iterator>
inline bool	operator>(const BidirectionalIterator<Iterator>& lhs, const BidirectionalIterator<Iterator>& rhs) {
	return (rhs < lhs);
}
template <typename Iterator>
inline bool	operator<=(const BidirectionalIterator<Iterator>& lhs, const BidirectionalIterator<Iterator>& rhs) {
	return !(rhs < lhs);
}
template <typename Iterator>
inline bool	operator>=(const BidirectionalIterator<Iterator>& lhs, const BidirectionalIterator<Iterator>& rhs) {
	return !(lhs < rhs);
}
// Comparison of reverse_iterator to const reverse iterator
template <typename IteratorL, typename IteratorR>
inline bool operator==(const BidirectionalIterator<IteratorL>& lhs, const BidirectionalIterator<IteratorR>& rhs) {
	return (lhs.base() == rhs.base());
}
template <typename IteratorL, typename IteratorR>
inline bool operator<(const BidirectionalIterator<IteratorL>& lhs, const BidirectionalIterator<IteratorR>& rhs) {
	return (lhs.base() < rhs.base());
}
template <typename IteratorL, typename IteratorR>
inline bool operator!=(const BidirectionalIterator<IteratorL>& lhs, const BidirectionalIterator<IteratorR>& rhs) {
	return !(lhs == rhs);
}
template <typename IteratorL, typename IteratorR>
inline bool operator>(const BidirectionalIterator<IteratorL>& lhs, const BidirectionalIterator<IteratorR>& rhs) {
	return (rhs < lhs);
}
template <typename IteratorL, typename IteratorR>
inline bool operator<=(const BidirectionalIterator<IteratorL>& lhs, const BidirectionalIterator<IteratorR>& rhs) {
	return !(rhs < lhs);
}
template <typename IteratorL, typename IteratorR>
inline bool operator>=(const BidirectionalIterator<IteratorL>& lhs, const BidirectionalIterator<IteratorR>& rhs) {
	return !(lhs < rhs);
}
// Generator function for reverse_iterator
template <typename Iterator>
inline BidirectionalIterator<Iterator>	make_reverse_iterator(Iterator i) {
	return BidirectionalIterator<Iterator>(i);
}

//template

//template<typename Iterator>
//inline typename ReverseRandomAccessIterator<Iterator>::difference_type operator-(const ReverseRandomAccessIterator<Iterator>& lhs, const ReverseRandomAccessIterator<Iterator>& rhs) {
//	return (lhs.base() - rhs.base());
//}
//template<typename IteratorL, typename IteratorR>
//inline typename ReverseRandomAccessIterator<IteratorL>::difference_type operator-(const ReverseRandomAccessIterator<IteratorL>& lhs, const ReverseRandomAccessIterator<IteratorR>& rhs) {
//	return (lhs.base() - rhs.base());
//}
//
//template <typename Iterator>
//inline ReverseRandomAccessIterator<Iterator>	operator+(typename ReverseRandomAccessIterator<Iterator>::difference_type n, const ReverseRandomAccessIterator<Iterator>& x) {
//	return ReverseRandomAccessIterator<Iterator>(x.base() - n);
//}

#endif //FT_CONTAINERS_REVERSEITERATOR_HPP
