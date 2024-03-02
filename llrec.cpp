#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) {
  //function is done if head is NULL
  //sets both smaller and larger to the current value

  /*
  * 0 means the current value is smaller
  * 1 means the current value is larger
  */
  int state = 0;
  larger = head;
  smaller = head;
  // if the smaller is NULL then that means the function finished
  if (smaller == NULL) {
    return;
  }
  // if the value is wrong then the value should be cleared out
  else if (smaller->val > pivot) {
    smaller = NULL;
    state = 1;
  }
  // if larger is NULL then the function is also finished
  if (larger == NULL) {
    return;
  }
  //same idea with the value being wrong
  else if (larger->val <= pivot) {
    larger = NULL;
  }
  // increment head
  head = head->next;

  // call recursively if the head isn't NULL or when the function is done
  if (head != NULL) {
    // if the smaller or larger is 0 it needs to be incremented
    if (state == 0) {
      llpivot(head, smaller->next, larger, pivot);
    }
    else {
      llpivot(head, smaller, larger->next, pivot);
    }
  }
}