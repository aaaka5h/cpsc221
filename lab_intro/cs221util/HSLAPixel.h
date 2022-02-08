/**
 * @file HSLAPixel.h
 *
 * @author CS 221: Data Structures
 */

#ifndef CS221UTIL_HSLAPIXEL_H
#define CS221UTIL_HSLAPIXEL_H

#include <string>
#include <vector>
#include "HSLAPixel.h"

namespace cs221util {
  class HSLAPixel {
  public:

    double h;
    double l;
    double s;
    double a;

    // default constructor
    HSLAPixel();

    // alternative constructor
    HSLAPixel(double hue, double saturation, double luminance);

    HSLAPixel(double hue, double saturation, double luminance, double alpha);
  };

}

#endif
