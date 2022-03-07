/*
*  File:        orderingstructure.h
*  Description: Definition of an abstract ordering structure class.
*
*               You **should not** modify this file for the PA.
*
*  Date:        2022-02-10 23:31
*/
#ifndef _ORDERINGSTRUCTURE_H_
#define _ORDERINGSTRUCTURE_H_

/*
*  OrderingStructure: represents an interface for a structure that orders
*    items placed into it. Your Stack and Queue classes will implement this
*    interface.
*
*/
template <class T> class OrderingStructure {
  public:
    /**
     * Destructor for the OrderingStructure. Virtual so as to allow
     * derived classes to override if necessary.
     */
    virtual ~OrderingStructure() {
      // nothing
    }

    /*
    *  Adds the given element to the ordering structure.
    *  PARAM: item -  the item to be added.
    *  POST: item has been added to the ordering structure.
    */
    virtual void Add(const T& item) = 0;

    /*
    *  Removes an element from the ordering structure. You may assume
    *  that this function is only called when the ordering structure is
    *  not empty.
    *  POST: the appropriate element is removed from the ordering structure.
    *  RETURN: an element from the ordering structure.
    */
    virtual T Remove() = 0;

    /*
    *  Looks at the next element of the ordering structure, but does
    *  not remove it.
    *  RETURN: the next element on the ordering structure.
    */
    virtual T Peek() = 0;

    /*
    *  Determines if the ordering structure is empty.
    *  RETURN: true if there are no elements in the ordering structure,
    *          false otherwise.
    */
    virtual bool IsEmpty() const = 0;
};
#endif
