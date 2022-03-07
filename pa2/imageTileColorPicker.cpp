/*
*  File: imageTileColorPicker.cpp
*  Implements the image tile color picker for CPSC 221 PA2.
*
*/

#include "imageTileColorPicker.h"

ImageTileColorPicker::ImageTileColorPicker(PNG& otherimage) {
  img_other = otherimage;
}

HSLAPixel ImageTileColorPicker::operator()(PixelPoint p) {
  int other_x = p.x;
  int other_y = p.y;

  // Using while loop with repeated subtraction will go to infinite loop (width/height are unsigned ints)
  other_x = other_x % img_other.width();
  other_y = other_y % img_other.height();
  
  HSLAPixel* res = img_other.getPixel(other_x, other_y);
  return *res;
}
