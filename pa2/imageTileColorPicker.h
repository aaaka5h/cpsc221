/*
*  File: imageTileColorPicker.h
*  Definition of an image tile color picker.
*
*/
#ifndef _IMAGETILECOLORPICKER_H_
#define _IMAGETILECOLORPICKER_H_

#include "colorPicker.h"

/*
*  imageTileColorPicker: a functor that determines the color that should be used
*  given a point using color values from a different image.
*
*/
class ImageTileColorPicker : public ColorPicker
{
  public:
    /*
    *  Constructs a new ImageTileColorPicker.
    *
    *  PRE:   otherimage has dimensions at least 1x1
    *  PARAM: otherimage - image from which colors will be taken to draw on mainimage
    */
    ImageTileColorPicker(PNG& otherimage);

    /*
    *  Picks the color for pixel (x, y).
    *  img_other is tiled across the dimensions of img_main, starting at (0,0).
    *  The color from the tiled image at (x,y) is then selected.
    *
    *  An image tiling looks like the same image repeated over and over again
    *  in a grid, starting at (0,0).
    *  You should be able to achieve this effect with some simple arithmetic operations.
    *
    *  PARAM:  p - The point for which you're picking a color
    *  RETURN: The color chosen for (p).
    */
    virtual HSLAPixel operator()(PixelPoint p);

  private:
    PNG img_other;   // image from which colors will be taken
};

#endif
