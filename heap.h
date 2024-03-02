#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> array;

  int x;
  PComparator compare;

  
};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {
  // destructor clearing the inside vector
  array.clear();
}

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) {
  compare = c;
  x = m;
}
// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return array[0];


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  //
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("");

  }
  // replace the root of the heap with the last element
  // heapify again
  array[0] = array.back();
  array.pop_back();
  // don't heapify if the heap is empty or only has one
  if (size() > 1) {
    return;
  } 
  int idx = 0;
  size_t childIdx = (idx * x) + 1;

  while (childIdx < size()) {
    // find the highest priority child
    // start with the leftmost child
    int highChildIdx = (idx * x) + 1;
    for (int i = 1; i <= x; i++) {
      childIdx = (idx * x) + i;
      if (childIdx >= size()) {
        break;
      }
      // swap the child which has the higher priority
      if (compare(array[childIdx], array[highChildIdx])) {
        highChildIdx = childIdx;
      }
    }
    if (compare(array[highChildIdx] , array[idx])) {
      std::swap(array[idx], array[highChildIdx]);
      idx = highChildIdx;
      childIdx = (idx * x) + 1;
    }
    else {
      break;
    }
  }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
  array.push_back(item);
  if (size() == 1) {
    return;
  }
  int itemIdx = size() - 1;
  int parentIdx = (itemIdx - 1)/ x;
  while (compare(array[itemIdx], array[parentIdx]) && parentIdx >= 0) {
    std::swap(array[itemIdx], array[parentIdx]);
    itemIdx = parentIdx;
    parentIdx = (itemIdx - 1) / x;
  }
}


template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const{
  return size() == 0;
}

/**
* @brief Returns size of the heap
* 
*/
template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
  return array.size();
}
#endif

