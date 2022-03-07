/*
*  File: negativeColorPicker.h
*  Definition of a negative color picker.
*
*/
#ifndef _NEGATIVECOLORPICKER_H_
#define _NEGATIVECOLORPICKER_H_

#include <cmath>

#include "cs221util/HSLAPixel.h"

#include "colorPicker.h"
#include "pixelpoint.h"

using namespace std;

/*
*  NegativeColorPicker: a functor that determines the color that should be used
*  given a point containing both an x and a y coordinate.
*  The final hue and luminance of the (x, y) point has inverted hue and luminance
*  values of the (x, y) point of the original image.
*  Saturation and alpha will not be changed.
*/
class NegativeColorPicker : public ColorPicker
{
  public:
    /*
    *  Constructs a new NegativeColorPicker.
    */
    NegativeColorPicker(PNG& inputimg);

    /*
    *  Picks the color for pixel (x, y), which is a member of point p.
    *  The new color consists of components h, s, and l.
    *  The saturation s and alpha a are unchanged from the original color.
    * 
    *  The hue and luminance are inverted from the original image. Refer to HSLA documentation
    *  to determine an "appropriate" meaning for hue/luminance inversion/negation.
    *  e.g. inverting a luminance of 0.2 should yield 0.8, and inverting a hue of 10 should yield 190.
    * 
    *  RETURN: The color chosen for (p).
    */
    virtual HSLAPixel operator()(PixelPoint p);

  private:
    PNG img;                  // Original image used in flood fill algorithm
};

#endif
