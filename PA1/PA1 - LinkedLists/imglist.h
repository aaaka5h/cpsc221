// File:        imglist.h
// Date:        2022-01-19 23:27
// Description: Definition of a ImgList class, for CPSC 221 2021W2 PA1
//
// DO NOT MODIFY ANY EXISTING DEFINITIONS
// YOU MAY NOT ADD ANY MEMBER VARIABLES, WHETHER PRIVATE OR PUBLIC
// BUT YOU MAY ADD YOUR OWN PRIVATE MEMBER FUNCTIONS IF NECESSARY
//

#ifndef _IMGLIST_H_
#define _IMGLIST_H_

#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"

using namespace std;
using namespace cs221util;

class ImgNode {
  public:
    HSLAPixel colour; // the HSLA colour of this node when rendered
    ImgNode* north;   // pointer to the northern neighbour, if one exists; NULL otherwise
    ImgNode* east;    // pointer to the eastern neighbour, if one exists; NULL otherwise
    ImgNode* south;   // pointer to the southern neighbour, if one exists; NULL otherwise
    ImgNode* west;    // pointer to the western neighbour, if one exists; NULL otherwise
    unsigned int skipright; // number of nodes to this node's immediate east
                            // (in an original list) that were skipped
                            // to point to the current eastern neighbour
    unsigned int skipleft;
    unsigned int skipup;
    unsigned int skipdown;

    ImgNode() {  // default constructor
      colour.h = 0;  colour.s = 0;  colour.l = 0;  colour.a = 0;
      north = NULL;  east = NULL;  south = NULL;  west = NULL;
      skipright = 0; skipleft = 0; skipup = 0; skipdown = 0;
    };

    // copy constructor
    // copies colour and skip data from its parameter,
    // but does not copy pointer data
    ImgNode(const ImgNode& ndata) {
      colour = ndata.colour;
      north = NULL;  east = NULL;  south = NULL;  west = NULL;
      skipright = ndata.skipright; skipleft = ndata.skipleft;
      skipup = ndata.skipup; skipdown = ndata.skipdown;
    };
};

class ImgList {
  private:
    ImgNode* northwest; // entry point to the list; the upper-left corner of the image
    ImgNode* southeast; // last node in the list; the lower-right corner of the image

    // void Clear();       // deallocates all nodes in the list
    void Copy(const ImgList& otherlist); // copies content of otherlist into this list and sets this list's member pointers
    
    // modifiers
    ImgNode* SelectNode(ImgNode* rowstart, int selectionmode); // returns a pointer to the node which best satisfies specific criteria
    void Carve(int selectionmode); // removes a node from each row of the list based on specific criteria
                                   // note that nodes on the left/west and right/east boundaries will never be selected for removal

  public:
    void Clear();
    ImgList(); // default constructor creates an empty list
    ImgList(PNG& img); // builds a list from an input image, one node per pixel
    ImgList(const ImgList& otherlist); // builds a new list as a copy of otherlist
    ImgList& operator=(const ImgList& rhs); // assigns contents of rhs into this list as a copy; it must deallocate any existing data from this list
    ~ImgList(); // destructor deallocates all heap data associated with this list

    // accessors
    unsigned int GetDimensionX() const; // returns the horizontal dimension of the list (counted in nodes)
    unsigned int GetDimensionY() const; // returns the vertical dimension of the list (counted in nodes, always matches the full original image height in pixels)
    unsigned int GetDimensionFullX() const; // returns the horizontal dimension of the list (counted in original pixels, pre-carving)
    PNG Render(bool fillgaps, int fillmode) const; // renders list's pixel data to a PNG, with or without filling gaps caused by carving

    // modifiers
    void Carve(unsigned int rounds, int selectionmode); // removes "rounds" number of pixels (up to a maximum of width - 2) from each row, based on specific criteria
                                               // note that nodes on the left/west and right/east boundaries will never be selected for removal
  
    // The following two functions are used ONLY for us (the CPSC 221 staff) to test the structure of your ImgList.
    // None of your other member functions should be calling these.
    // In normal practice, we should not expose private member attributes like this.
    ImgNode* GetNorthwest() { return northwest; }
    ImgNode* GetSoutheast() { return southeast; }
  
  /*********************************************************
  * YOU MAY DEFINE YOUR OWN PRIVATE MEMBER FUNCTIONS BELOW *
  *********************************************************/
  private:
    double HueAvg(double hueWest, double hueEast) const;
};

#endif