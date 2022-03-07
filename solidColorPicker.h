/**
 * @file solidColorPicker.h
 * Definition of a solid color picker.
 *
 */
#ifndef _SOLIDCOLORPICKER_H_
#define _SOLIDCOLORPICKER_H_

#include "colorPicker.h"

/**
 * SolidColorPicker: a functor that determines the color that should be
 * used given an x and y coordinate using a solid pattern. You can create
 * private helper functions inside this class, as well as local storage, if
 * necessary. Remember to overload a destructor if you need to.
 *
 */
class SolidColorPicker : public ColorPicker
{
  public:
    /**
     * Constructs a new solidColorPicker.
     *
     * @param fillColor The color for this color picker.
     */
    SolidColorPicker(HSLAPixel fillColor);

    /**
     * Picks the color for pixel (x, y).
     *
     * Simply returns the same color (used to construct the picker) all
     * of the time.
     */
    virtual HSLAPixel operator()(PixelPoint p);

  private:
    /**
     * @todo Define any additional private member variables or helper
     *	functions here as you see fit.
     */
    HSLAPixel color;
};

#endif
