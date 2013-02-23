#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "eecs281heap.h"
#include <algorithm>
#include <utility>


//A specialized version of the 'heap' ADT implemented as a binary heap.
template<typename TYPE, typename COMP = std::less<TYPE>>
class binary_heap : public eecs281heap<TYPE, COMP> {
public:
  using size_type = long unsigned int;

  //Description: Construct a heap out of an iterator range with an optional
  //             comparison functor.
  //Runtime: O(n) where n is number of elements in range.
  template<typename InputIterator>
  binary_heap(InputIterator start, InputIterator end, COMP comp = COMP());

  //Description: Construct an empty heap with an optional comparison functor.
  //Runtime: O(1)
  binary_heap(COMP comp = COMP());

  //Description: Assumes that all elements inside the heap are out of order and
  //             'rebuilds' the heap by fixing the heap invariant.
  //Runtime: O(n)
  virtual void make_heap();

  //Description: Add a new element to the heap.
  //Runtime: O(log(n))
  virtual void push(const TYPE& val);

  //Description: Remove the most extreme (defined by 'compare') element from
  //             the heap.
  //Note: We will not run tests on your code that would require it to pop an
  //element when the heap is empty. Though you are welcome to if you are
  //familiar with them, you do not need to use exceptions in this project.
  //Runtime: O(log(n))
  virtual void pop();

  //Description: Return the most extreme (defined by 'compare') element of
  //             the heap.
  //Runtime: O(1)
  virtual const TYPE& top() const;

  //Description: Get the number of elements in the heap. This has been
  //             implemented for you.
  //Runtime: O(1)
  virtual size_type size() const
    { return data.size(); }

  //Description: Return true if the heap is empty. This has been implemented
  //             for you.
  //Runtime: O(1)
  virtual bool empty() const
    { return data.empty() };
private:
  //Note: This vector *must* be used your heap implementation.
  std::vector<TYPE> data;
private:
  //***Add any additional member functions or data you require here.
  void maxHeapify(int i);
};

template<typename TYPE, typename COMP>
void maxHeapify(int i) {
	int left = 2 * i;
	int right = 2 * i + 1;
	int largest;
	if((left < data.size()) && (this->compare(data[i], data[left]))) {
		largest = left;
	}
	else {
		largest = i;
	}
	if((right < data.size()) && (this->compare(data[largest], data[right]))) {
		largest = r;
	}
	if(largest != i) {
		std::swap(data[i], data[largest]);
		maxHeapify(largest);
	}
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>::make_heap() {
	for(int i = data.size() / 2; i >= 0; i--) {
			maxHeapify(i);
	}
}
template<typename TYPE, typename COMP>
template<typename InputIterator>
binary_heap<TYPE, COMP>::binary_heap(
  InputIterator start,
  InputIterator end,
  COMP comp
) {
	while(start != end) {
		data.push_back(start++);
	}
	this->compare = comp;
	make_heap();
}

template<typename TYPE, typename COMP>
binary_heap<TYPE, COMP>::binary_heap(COMP comp) {
	this->compare comp;
}



template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>::push(const TYPE& val) {
	int i = data.size();
	data.push_back(val);
	while((i > 0) && (this->compare(data[i/2],data[i]))) {
		std::swap(data[i/2], data[i]);
	}
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>::pop() {
	TYPE max = data[0];
	data[0] = data[data.size() - 1];
	data.erase[data.end()--];
	maxHeapify(0);
}

template<typename TYPE, typename COMP>
const TYPE& binary_heap<TYPE, COMP>::top() const {
	return data.front();
}

#endif //BINARY_HEAP_H

