/*
* File:        priority.h
* Description: Defines a priority ordering structure specially made for determining the
*              order of neighbours visited in PA2's filler::fill function.
*              Note that this does NOT serve the same purpose as the stack/queue
*              ordering structure which you have also been asked to implement.
*
*              Ignoring resize costs, any single insertion or removal operation
*              should cost at most O(n), where n is the number of PixelPoints
*              stored in the collection.
*
*              You may add your own private functions to support the priority ordering of
*              the collection contents.
* 
* Date:        2022-02-10 01:59
*
*/

#ifndef _PRIORITY_H_
#define _PRIORITY_H_

#include "cs221util/HSLAPixel.h"
#include "pixelpoint.h"

#include <vector>

using namespace cs221util;
using namespace std;

class PriorityNeighbours {
  public:

    /*
    *  Default constructor
    *  Initializes refcolor to the default color according to the HSLAPixel implementation.
    */
    PriorityNeighbours();

    /*
    *  Parameterized constructor
    *  Initializes refcolor to the supplied value.
    */
    PriorityNeighbours(HSLAPixel ref);

    /*
    *  Inserts an item into the collection
    *  PARAM: p - item to be inserted
    *  POST:  the collection contains p, along with all previously existing items.
    */
    void Insert(PixelPoint p);

    /*
    *  Removes and returns an item from the collection satisfying the priority condition
    *  PRE:    the collection is not empty (but it would be good to check anyway!).
    *  POST:   the item satisfying the priority condition is removed from the collection.
    *  RETURN: the item satisfying the priority condition
    * 
    *  Priority condition:
    *    The PixelPoint in the collection whose color is the minimum distance away
    *    from the reference color is the priority item to be returned.
    * 
    *    In case of multiple items with the same priority value (i.e. minimal distance
    *    away from the reference color), the one with the minimal y-coordinate will be
    *    selected.
    *    In case of multiple items with the same priority value and the same y-coordinate,
    *    the one with the minimal x-coordinate will be selected.
    * 
    *    ***ATTENTION*** The dist() function in HSLAPixel.h will be very helpful!
    * 
    *  Combined with Insert(), think about the time complexity of maintaining the
    *  priority order and/or accessing the priority element in this specific application!
    */
    PixelPoint Remove();

    /*
    *  Checks if the collection is empty
    *  RETURN: true, if the collection is empty
    *          false, otherwise
    */
    bool IsEmpty() const;

    /*
    *  Returns the value of the reference color
    */
    HSLAPixel GetReferenceColor() const;

    /*
    *  Sets the reference color attribute
    *  POST: refcolor is set to the supplied value
    */
    void SetReferenceColor(HSLAPixel ref);
    
  private:
    HSLAPixel refcolor;        // reference color for determining priority of the points in the collection
    vector<PixelPoint> points; // array to store your priority collection.
                               // You may organize this in any way you like,
                               // as long as the Remove() function always
                               // returns the item satisfying the priority condition


  private:
    /* YOU CAN DECLARE YOUR PRIVATE FUNCTIONS HERE */

};

#endif