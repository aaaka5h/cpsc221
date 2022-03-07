/*
*  File:        stack.h
*  Description: Definition of the Stack class.
*
*               You **should not** modify this file for the PA!
* 
*  Date: 2022-02-10 22:27
*
*/

#ifndef _STACK_H_
#define _STACK_H_

#define DEFAULTCAPACITY 4 // Initial capacity of the array.
#define EXPANSIONFACTOR 2 // Factor to multiply or divide current size by when resizing.
#define SHRINKRATE 4      // When the size of the array is less than equal 1 over this value the array should resize

#include "orderingstructure.h"

template <class T>
class Stack : public OrderingStructure<T> {
  public:
    /*
    *  Default constructor
    */
    Stack();

    /*
    *  Destructor
    */
    ~Stack();

    /*
    *  Adds the parameter object to the top of the Stack
    *  PARAM: item - the object to be added to the Stack
    *  POST:  the Stack contains newitem at the top, as its most recently added item.
    */
    void Push(const T& item);

    /*
    *  Removes the object on top of the Stack, and returns it.
    *  POST: the most recently added item is removed from the collection.
    *  RETURN: the element that used to be at the top of the Stack.
    */
    T Pop();

    /*
    *  Adds the given element to the ordering structure.
    *  See OrderingStructure::Add()
    */
    void Add(const T& item);

    /*
    *  Removes an element from the ordering structure. You may assume
    *  that this function is only called when the ordering structure is
    *  not empty.
    *  See OrderingStructure::Remove()
    */
    T Remove();

    /*
    *  Finds the object on top of the Stack, and returns it to the caller.
    *  Unlike Pop(), this operation does not alter the Stack itself.
    *  RETURN: the element at the top of the Stack.
    */
    T Peek();

    /*
    *  Determines if the Stack is empty.
    *  RETURN: true if the stack is empty,
    *          false otherwise.
    */
    bool IsEmpty() const;

    /*
    *  Return the maximum number of items the stack can hold.
    *
    *  Note: This is an implementation detail we would normally hide.
    *  We include it here for testing purposes.
    */
    size_t Capacity() const;

    /*
    *  Return the number of items on the stack.
    */
    size_t Size() const;

  private:
    /*
    *  The maximum number of items the stack can store without a resize
    */
    size_t max_items;

    /*
    *  The number of items currently in the stack
    */
    size_t num_items;

    /*
    *  The dynamic array representing our Stack
    */
    T* items;

    /*
    *  Resize the the member variable `items`.
    *  The minimum size is the number of items in the Stack.
    *  Don't forget to free up any memory that is no longer used.
    *  PARAM: n - the capacity of the stack after resizing
    */
    void Resize(size_t n);
};

#include "stack.cpp" // needed for template instantiation

#endif
