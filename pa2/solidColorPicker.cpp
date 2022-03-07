#include "solidColorPicker.h"

SolidColorPicker::SolidColorPicker(HSLAPixel fillColor)
{
    /* sample code */
  // constructor initializes all member attributes.
  // Here, the color attribute is the only one to initialize.
  color = fillColor;
}

HSLAPixel SolidColorPicker::operator()(PixelPoint p)
{
    /* sample code */
  // This function determines the color of the pixel in the output image at point p.
  // For SolidColorPicker, this simply uses the fixed color
  // of the member attribute.
  // Other ColorPickers will need to do some computation to decide what
  // color to use.
  return color;
}
