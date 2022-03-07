/*
*  File:        pixelpoint.h
*  Description: Defines a PixelPoint class, which consists of a (x,y) image coordinate,
*               along with a HSLAPixel color.
* 
*               *************************************************************
*               You should ***NOT*** modify this file, nor its implementation
*               *************************************************************
* 
*  Date:        2022-02-10 00:28
*/

#ifndef _PIXELPOINT_H_
#define _PIXELPOINT_H_

#include "cs221util/HSLAPixel.h"

using namespace cs221util;
using namespace std;

struct PixelPoint {

  PixelPoint(unsigned int rx = 0, unsigned int ry = 0, HSLAPixel rcolor = HSLAPixel(0, 0, 0)) : x(rx), y(ry), color(rcolor) {}

  unsigned int x;  // image x coordinate of this point
  unsigned int y;  // image y coordinate of this point
  HSLAPixel color; // color value of this point

  //PixelPoint& operator=(const PixelPoint& rhs) {
  //  if (this != &rhs) {
  //    x = rhs.x;
  //    y = rhs.y;
  //    color = rhs.color;
  //  }
  //  return *this;
  //}

  bool operator==(const PixelPoint& rhs) const {
    return (x == rhs.x && y == rhs.y && color == rhs.color);
  }
};


#endif