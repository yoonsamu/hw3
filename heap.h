#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <algorithm>

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
  //the array of values
  std::vector<T> arr;

  //the n in n-ary heap
  int x;

  //the comparison (less than or greater than)
  PComparator compare;
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c){
  x = m;
  compare = c;
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {
  arr.clear();
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::underflow_error("");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return arr[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::underflow_error("");
  }
  arr[0] = arr.back();
  arr.pop_back();
  if (size() == 1 || size() == 0) {
    return;
  }
  int idx = 0;
  size_t childIdx = idx * x + 1; //starts at the leftmost child
  while (childIdx < size()) {
    int highestChildIdx = idx * x + 1;
    //traverses through each child
    for (int i = 1; i <= x; i++) {
      childIdx = idx * x + i;
      if (childIdx >= size()) {
        break;
      }
      if (compare(arr[childIdx], arr[highestChildIdx])) {
        highestChildIdx = childIdx;
      }
    }
    if (compare(arr[highestChildIdx], arr[idx])) {
      std::swap(arr[idx], arr[highestChildIdx]);
      idx = highestChildIdx;
      childIdx = idx * x + 1;
    }
    else {
      break;
    }
  }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
  arr.push_back(item);
  if (size() == 1) {
    return;
  }
  int itemIdx = size() - 1;
  int parentIdx = (itemIdx - 1)/ x;
  while (compare(arr[itemIdx], arr[parentIdx]) && parentIdx >= 0) {
    std::swap(arr[itemIdx], arr[parentIdx]);
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
  return arr.size();
}

#endif