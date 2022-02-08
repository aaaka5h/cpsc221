// File:        imglist.cpp
// Date:        2022-01-27 10:21
// Description: Contains partial implementation of ImgList class
//              for CPSC 221 2021W2 PA1
//              Function bodies to be completed by yourselves
//
// ADD YOUR FUNCTION IMPLEMENTATIONS IN THIS FILE
//

#include "imglist.h"

#include <math.h> // provides fmax, fmin, and fabs functions

/**************************
* MISCELLANEOUS FUNCTIONS *
**************************/

/*
* This function is NOT part of the ImgList class,
* but will be useful for one of the ImgList functions.
* Returns the "difference" between two hue values.
* PRE: hue1 is a double between [0,360).
* PRE: hue2 is a double between [0,360).
* 
* The hue difference is the absolute difference between two hues,
* but takes into account differences spanning the 360 value.
* e.g. Two pixels with hues 90 and 110 differ by 20, but
*      two pixels with hues 5 and 355 differ by 10.
*/
double HueDiff(double hue1, double hue2) {
  return fmin(fabs(hue1 - hue2), fabs(360 + fmin(hue1, hue2) - fmax(hue1, hue2)));
}

/*********************
* CONSTRUCTORS, ETC. *
*********************/

/*
* Default constructor. Makes an empty list
*/
ImgList::ImgList() {
  // set appropriate values for all member attributes here
  northwest = NULL;
  southeast = NULL;
}

/*
* Creates a list from image data
* PRE: img has dimensions of at least 1x1
*/
ImgList::ImgList(PNG& img) {
  // build the linked node structure and set the member attributes appropriately
  unsigned int height = img.height();
  unsigned int width = img.width();

  if (width == 1 || height == 1) {
    northwest = new ImgNode();
    southeast = northwest;
  }

  // Useful nodes
  northwest = new ImgNode();
  ImgNode* aboveRowStart = northwest;
  ImgNode* aboveRowEnd = new ImgNode();

  for (unsigned int y=0; y<height; y++) {
    // create first row of nodes
    if (y == 0) {
      ImgNode* westmost = aboveRowStart;
      ImgNode* eastmost = aboveRowEnd;
      westmost->colour = *img.getPixel(0, 0);
      eastmost->colour = *img.getPixel(width - 1, 0);
    
      for (unsigned int x=1; x<width-1; x++) {
        ImgNode* curr = new ImgNode();
        curr->colour = *img.getPixel(x, 0);
        // Create east, west pointers
        curr->west = westmost;
        curr->east = eastmost;
        westmost->east = curr;
        eastmost->west = curr;
        // advance westmost pointer
        westmost = curr;
      }

    } else {
      ImgNode* westmost = new ImgNode();
      westmost->colour = *img.getPixel(0, y);
      westmost->north = aboveRowStart;
      aboveRowStart->south = westmost;
      ImgNode* eastmost = new ImgNode();
      eastmost->colour = *img.getPixel(width-1, y);
      eastmost->north = aboveRowEnd;
      aboveRowEnd->south = eastmost;
      ImgNode* above = aboveRowStart->east;
      
      for (unsigned int x=1; x<width-1; x++) {
        ImgNode* curr = new ImgNode();
        curr->colour = *img.getPixel(x, y);
        curr->west = westmost;
        curr->east = eastmost;
        westmost->east = curr;
        eastmost->west = curr;
        curr->north = above;
        above->south = curr;
        // advance westmost and above
        westmost = westmost->east;
        above = above->east;
      }

      aboveRowStart = aboveRowStart->south;
      aboveRowEnd = aboveRowEnd->south;
    }
  }

  southeast = aboveRowEnd;
}

/*
* Copy constructor.
* Creates this this to become a separate copy of the data in otherlist
*/
ImgList::ImgList(const ImgList& otherlist) {
  // build the linked node structure using otherlist as a template
  Copy(otherlist);
}

/*
* Assignment operator. Enables statements such as list1 = list2;
*   where list1 and list2 are both variables of ImgList type.
* POST: the contents of this list will be a physically separate copy of rhs
*/
ImgList& ImgList::operator=(const ImgList& rhs) {
  // Re-build any existing structure using rhs as a template
  
  if (this != &rhs) { // if this list and rhs are different lists in memory
    // release all existing heap memory of this list
    Clear();    
    
    // and then rebuild this list using rhs as a template
    Copy(rhs);
  }
  
  return *this;
}

/*
* Destructor.
* Releases any heap memory associated with this list.
*/
ImgList::~ImgList() {
  // Ensure that any existing heap memory is deallocated
  Clear();
}

/************
* ACCESSORS *
************/

/*
* Returns the horizontal dimension of this list (counted in nodes)
* Note that every row will contain the same number of nodes, whether or not
*   the list has been carved.
* We expect your solution to take linear time in the number of nodes in the
*   x dimension.
*/
unsigned int ImgList::GetDimensionX() const {
  // replace the following line with your implementation
  // check empty list
  if (!northwest || !southeast) {
    return 0;
  }

  // check list with one node
  if (northwest == southeast) {
    return 1;
  }
  
  // iterate through east pointers
  ImgNode* curr = northwest;
  unsigned width = 0;
  while (curr) {
    width++;
    curr = curr->east;
  }
  return width;
}

/*
* Returns the vertical dimension of the list (counted in nodes)
* It is useful to know/assume that the grid will never have nodes removed
*   from the first or last columns. The returned value will thus correspond
*   to the height of the PNG image from which this list was constructed.
* We expect your solution to take linear time in the number of nodes in the
*   y dimension.
*/
unsigned int ImgList::GetDimensionY() const {
  // replace the following line with your implementation
  // check empty list
  if (!northwest || !southeast) {
    return 0;
  }

  // check list with one node
  if (northwest == southeast) {
    return 1;
  }

  // iterate through south pointers
  ImgNode* curr = northwest;
  unsigned height = 0;
  while (curr) {
    height++;
    curr = curr->south;
  }
  return height;
}

/*
* Returns the horizontal dimension of the list (counted in original pixels, pre-carving)
* The returned value will thus correspond to the width of the PNG image from
*   which this list was constructed.
* We expect your solution to take linear time in the number of nodes in the
*   x dimension.
*/
unsigned int ImgList::GetDimensionFullX() const {
  // replace the following line with your implementation
  // check empty list
  if (!northwest || !southeast) {
    return 0;
  }

  // check list with one node
  if (northwest == southeast) {
    return 1;
  }

  // iterate through width of list with skips
  ImgNode* curr = northwest;
  unsigned width = 0;
  while (curr) {
    unsigned toAdd = curr->skipright + 1;
    width += toAdd;
    curr = curr->east;
  }
  return width;
}

/*
* Returns a pointer to the node which best satisfies the specified selection criteria.
* The first and last nodes in the row cannot be returned.
* PRE: rowstart points to a row with at least 3 physical nodes
* PRE: selectionmode is an integer in the range [0,1]
* PARAM: rowstart - pointer to the first node\in a row
* PARAM: selectionmode - criterion used for choosing the node to return
*          0: minimum luminance across row, not including extreme left or right nodes
*          1: node with minimum total of "hue difference" with its left neighbour and with its right neighbour.
*        In the (likely) case of multiple candidates that best match the criterion,
*        the left-most node satisfying the criterion (excluding the row's starting node)
*        will be returned.
* A note about "hue difference": For PA1, consider the hue value to be a double in the range [0, 360).
* That is, a hue value of exactly 360 should be converted to 0.
* The hue difference is the absolute difference between two hues,
* but be careful about differences spanning the 360 value.
* e.g. Two pixels with hues 90 and 110 differ by 20, but
*      two pixels with hues 5 and 355 differ by 10.
*/
ImgNode* ImgList::SelectNode(ImgNode* rowstart, int selectionmode) {
  ImgNode* curr = rowstart->east;

  if (selectionmode == 0) {
    // find node with minimum luminance across row (excluding start and end of row)
    double minLum = curr->colour.l;
    ImgNode* minLumNode = curr;
    while (curr->east->east) { 
      if (curr->east->colour.l < minLum) {
        minLum = curr->east->colour.l;
        minLumNode = curr->east;
      }
      curr = curr->east;
    }
    return minLumNode;
  } 
  
  else {
    // find node with minimum total "hue difference" to neighbors (excluding start and end of row)
    ImgNode* curr = rowstart->east;
    ImgNode* leastDiffNode = curr;
    double leastDiff = 360;
    while (curr->east->east) {
      curr = curr->east;
      double hueDiffLeft  = HueDiff(curr->colour.h, curr->west->colour.h);
      double hueDiffRight = HueDiff(curr->colour.h, curr->east->colour.h);

      if (hueDiffLeft + hueDiffRight < leastDiff) {
        leastDiff = hueDiffLeft + hueDiffRight;
        leastDiffNode = curr;        
      }
    }
    return leastDiffNode;
  }
}

/*
* Renders this list's pixel data to a PNG, with or without filling gaps caused by carving.
* PRE: fillmode is an integer in the range of [0,2]
* PARAM: fillgaps - whether or not to fill gaps caused by carving
*          false: render one pixel per node, ignores fillmode
*          true: render the full width of the original image,
*                filling in missing nodes using fillmode
* PARAM: fillmode - specifies how to fill gaps
*          0: solid, uses the same colour as the node at the left of the gap
*          1: solid, using the averaged values (all channels) of the nodes at the left and right of the gap
*             Note that "average" for hue will use the closer of the angular distances,
*             e.g. average of 10 and 350 will be 0, instead of 180.
*             Average of diametric hue values will use the smaller of the two averages
*             e.g. average of 30 and 210 will be 120, and not 300
*                  average of 170 and 350 will be 80, and not 260
*          2: *** OPTIONAL - FOR BONUS ***
*             linear gradient between the colour (all channels) of the nodes at the left and right of the gap
*             e.g. a gap of width 1 will be coloured with 1/2 of the difference between the left and right nodes
*             a gap of width 2 will be coloured with 1/3 and 2/3 of the difference
*             a gap of width 3 will be coloured with 1/4, 2/4, 3/4 of the difference, etc.
*             Like fillmode 1, use the smaller difference interval for hue,
*             and the smaller-valued average for diametric hues
*/
PNG ImgList::Render(bool fillgaps, int fillmode) const {
  // Useful nodes
  ImgNode* curr = northwest;
  ImgNode* currRow = northwest;
  
  PNG outpng; //this will be returned later. Might be a good idea to resize it at some point.
  if (fillgaps) {
    outpng.resize(GetDimensionFullX(), GetDimensionY());  // count in original pixels
  } else {
    outpng.resize(GetDimensionX(), GetDimensionY());  // count in nodes
  }

  for (unsigned int y=0; y<GetDimensionY(); y++) {
    if (!fillgaps) {
      for (unsigned int x=0; x<GetDimensionX(); x++) {
        HSLAPixel* pixel = outpng.getPixel(x, y);
        *pixel = curr->colour;
        // stop curr = NULL;
        if (curr->east) {
          curr = curr->east;
        }
      }
      // stop currRow = NULL;
      if (currRow->south) {
        currRow = currRow->south;
        curr = currRow;
      }
    } 

    else {
      if (fillmode == 0) {
        for (unsigned int y=0; y<GetDimensionY(); y++) {
          for (unsigned int x=0; x<GetDimensionFullX(); x++) {
            HSLAPixel* pixel = outpng.getPixel(x, y);
            *pixel = curr->colour;
            // stop curr = NULL;
            if (curr->east) {
              curr = curr->east;
            }
          }
          // stop currRow = NULL;
          if (currRow->south) {
            currRow = currRow->south;
            curr = currRow;
          }
        }
      }

      else if (fillmode == 1) {  
        for (unsigned int y=0; y<GetDimensionY(); y++) {
          unsigned int x = 0;
          while (x < GetDimensionFullX()) {
            HSLAPixel* pixel = outpng.getPixel(x, y);
            *pixel = curr->colour;
            x++;
            for (unsigned int skips=0; skips<curr->skipright; skips++) {
              HSLAPixel* pixel = outpng.getPixel(x, y);
              ImgNode* right = curr->east;
              pixel->s = (curr->colour.s + right->colour.s) / 2.0;
              pixel->l = (curr->colour.l + right->colour.l) / 2.0;
              pixel->a = (curr->colour.a + right->colour.a) / 2.0;
              // find pixel->h using HueAvg function (see below)
              pixel->h = HueAvg(curr->colour.h, right->colour.h);
              // increment x
              x++;
            }
            // stop curr = NULL;
            if (x == GetDimensionFullX()) {
              break;
            }
            // advance curr
            curr = curr->east;
          }
          if (currRow->south) {
            currRow = currRow->south;
            curr = currRow;
          }
        }
      }
    }
  }
  
  return outpng;
}

/************
* MODIFIERS *
************/

/*
* Removes exactly one node from each row in this list, according to specified criteria.
* The first and last nodes in any row cannot be carved.
* PRE: this list has at least 3 nodes in each row
* PRE: selectionmode is an integer in the range [0,1]
* PARAM: selectionmode - see the documentation for the SelectNode function.
* POST: this list has had one node removed from each row. Neighbours of the created
*       gaps are linked appropriately, and their skip values are updated to reflect
*       the size of the gap.
*/
void ImgList::Carve(int selectionmode) {
  ImgNode* rowstart = northwest;
  while (rowstart) {
    ImgNode* toDelete = SelectNode(rowstart, selectionmode);
    toDelete->east->west = toDelete->west;
    toDelete->east->skipleft = (toDelete->east->skipleft) + (toDelete->skipleft) + 1;

    toDelete->west->east = toDelete->east;
    toDelete->west->skipright = (toDelete->west->skipright) + (toDelete->skipright) + 1;

    if (toDelete->north) {
      toDelete->north->south = toDelete->south;
      toDelete->north->skipdown = (toDelete->north->skipdown) + (toDelete->skipdown) + 1;
    }

    if (toDelete->south) {
      toDelete->south->north = toDelete->north;
      toDelete->south->skipup = (toDelete->south->skipup) + (toDelete->skipup) + 1;
    }

    delete toDelete;
    toDelete = NULL;
    
    if (!rowstart->south) {
      return;
    }
    rowstart = rowstart->south;
  }
}

// note that a node on the boundary will never be selected for removal
/*
* Removes "rounds" number of nodes (up to a maximum of node width - 2) from each row,
* based on specific selection criteria.
* Note that this should remove one node from every row, repeated "rounds" times,
* and NOT remove "rounds" nodes from one row before processing the next row.
* PRE: selectionmode is an integer in the range [0,1]
* PARAM: rounds - number of nodes to remove from each row
*        If rounds exceeds node width - 2, then remove only node width - 2 nodes from each row.
*        i.e. Ensure that the final list has at least two nodes in each row.
* POST: this list has had "rounds" nodes removed from each row. Neighbours of the created
*       gaps are linked appropriately, and their skip values are updated to reflect
*       the size of the gap.
*/
void ImgList::Carve(unsigned int rounds, int selectionmode) {
  // add your implementation here
  // ImgNode* cantCarve = northwest->east->east;
  // while (cantCarve) {
  //  for (unsigned r=0; r<rounds; r++) {
  //    // carve out based on selectionmode from each row
  //    Carve(selectionmode);
  //  }
  // }
  return;
}


/*
* Helper function deallocates all heap memory associated with this list,
* puts this list into an "empty" state. Don't forget to set your member attributes!
* POST: this list has no currently allocated nor leaking heap memory,
*       member attributes have values consistent with an empty list.
*/
void ImgList::Clear() {
  // add your implementation here
  // if (northwest) {
  //   if (northwest == southeast) {
  //     delete northwest;
  //   }
  // }

  // ImgNode* curr = northwest;
  // ImgNode* currRow = northwest;
  
  // // iterate through rows
  // while (currRow != NULL) {
  //   // iterate through columns
  //   while (curr->east != NULL) {
  //     ImgNode* left = curr;
  //     curr = left->east;  // get pointer to next element
  //     cout << "curr is: " << curr << endl;
  //     delete left;
  //   }

  //   // advance current row to currRow + 1
  //   currRow = currRow->south;
  //   if (!curr) {
  //     curr = curr->south;
  //   }
  // }

  // northwest = NULL;
  // southeast = NULL; 
}

/* ************************
*  * OPTIONAL - FOR BONUS *
** ************************
* Helper function copies the contents of otherlist and sets this list's attributes appropriately
* PRE: this list is empty
* PARAM: otherlist - list whose contents will be copied
* POST: this list has contents copied from by physically separate from otherlist
*/
void ImgList::Copy(const ImgList& otherlist) {
  // add your implementation here
  
}

/*************************************************************************************************
* IF YOU DEFINED YOUR OWN PRIVATE FUNCTIONS IN imglist.h, YOU MAY ADD YOUR IMPLEMENTATIONS BELOW *
*************************************************************************************************/

double ImgList::HueAvg(double hueWest, double hueEast) const{
    double hueAvg;
    double minHue = fmin(hueWest, hueEast);
    double maxHue = fmax(hueWest, hueEast);
    if (hueWest == 360) {
      hueWest = 0.0;
    }
    if (hueEast == 360) {
      hueEast = 0.0;
    }
    if (hueEast == hueWest) {
      return hueEast;
    }
    if (maxHue - minHue == HueDiff(hueWest, hueEast)) {
      hueAvg = (maxHue + minHue) / 2.0;
    } else {
      hueAvg = (HueDiff(hueWest, hueEast)) / 2.0 + maxHue - 360;
      if (hueAvg < 0) {
        hueAvg += 360;
      }
    }
    return hueAvg;          
}
