/*
*  File:        queue.h
*  Description: Definition of the Stack class.
*
*               You **should not** modify this file for the PA!
*
*  Date: 2022-02-11 00:11
*
*/
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "orderingstructure.h"
#include "stack.h"

/*
*  Queue class: represents a standard queue. Templated to hold elements of
*  any type. **You must only use the two private member Stacks as your
*  storage space! You cannot create new private member variables to hold
*  your objects!** It is up to you to determine how to use them, however.
*
*  Your Queue class should have O(1) running time over n operations
*  (amortized). There is an obvious solution that takes O(n) running time,
*  but this will not recieve all of the available points.
*
*  You **should not** modify this file for the PA!
*
*/
template <class T>
class Queue : public OrderingStructure<T> {
  public:
    /*
    *  Adds the parameter object to the back of the Queue.
    *
    *  NOTE: This fuction should have O(1) behavior over n operations!
    *
    *  PARAM: item -  object to be added to the Queue.
    */
    void Enqueue(const T& item);

    /*
    *  Removes the object at the front of the Queue, and returns it to
    *  the caller. You may assume that this function is only called
    *  when the Queue is non-empty.
    *
    *  NOTE: This function should have O(1) behavior over n operations!
    *
    *  RETURN: the item that used to be at the front of the Queue.
    */
    T Dequeue();

    /*
    *  Adds an element to the ordering structure.
    *
    *  See OrderingStructure::Add()
    */
    void Add(const T& item);

    /*
    *  Removes an element from the ordering structure.
    *
    *  See OrderingStructure::Remove()
    */
    T Remove();

    /*
    *  Finds the object at the front of the Queue, and returns it to
    *  the caller. Unlike Dequeue(), this operation does (conceptually!) not alter the
    *  Queue; however, you may need to alter the internal representation of the Queue.
    *  You may assume that this function is only called when the
    *  Queue is non-empty.
    *
    *  NOTE: This function should have O(1) behavior over n operations!
    *
    *  RETURN: the item at the front of the queue.
    */
    T Peek();

    /*
    *  Determines if the Queue is empty.
    *
    *  RETURN: true if the stack is empty,
    *          false otherwise.
    * 
    *  NOTE: This function must always run in O(1) time!
    */
    bool IsEmpty() const;

  private:
    Stack<T> stack_1; /**< One of the two Stack objects you must use. */
    Stack<T> stack_2; /**< The other of the two Stack objects you must use. */
};
#include "queue.cpp"
#endif
