/*
*  File:        colorPicker.h
*  Description: Definition of a color picker abstract base class.
*
*/
#ifndef _COLORPICKER_H_
#define _COLORPICKER_H_

#include "cs221util/HSLAPixel.h"
#include "cs221util/PNG.h"

#include "pixelpoint.h"

using namespace cs221util;

/*
* colorPicker: a functor that determines the color that should be used
* given an x and y coordinate.
*
*/
class ColorPicker
{
  public:
    /*
    *  Destructor: does nothing, but as it is virtual, you may overload it in
    *  derived classes if needed.
    */
    virtual ~ColorPicker(){};

    /*
    *  Picks the color for pixel (x, y).
    *
    *  This function **must** be defined in the subclass! It chooses a color for
    *  the given point and returns it.
    *
    *  For example, the NegativeColorPicker::operator()() function is defined so as
    *  to return the negative color of the pixel at the specified location of the original image.
    *
    *  For the other patterns, you will have to figure out how to "pick" the
    *  colors.
    *
    *  PARAM:  p - The point for which you're picking a color.
    *  RETURN: The color chosen for (p).
    */
    virtual HSLAPixel operator()(PixelPoint p) = 0;
};

#endif
