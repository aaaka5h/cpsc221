/*
*  File: censorColorPicker.h
*  Definition of a censor color picker.
*
*/
#ifndef _CENSORCOLORPICKER_H_
#define _CENSORCOLORPICKER_H_

#include "colorPicker.h"
#include "pixelpoint.h"

/*
*  censorColorPicker: a functor that determines the color that should be used
*  given a point using a mosaic block pattern.
*
*/
class CensorColorPicker : public ColorPicker
{
  public:
    /*
    *  Constructs a new CensorColorPicker.
    *
    *  PARAM: b_width - width of each mosaic block in pixels.
    *  PARAM: ctr - middle/center point of mosaic area
    *  PARAM: rad - maximum pixel distance away from center where the mosaic color will be applied
    *  PARAM: inputimage - Original input image used to determine average color for a block
    */
    CensorColorPicker(unsigned int b_width, PixelPoint ctr, unsigned int rad, PNG& inputimage);

    /*
    *  Picks the color for pixel (x, y). There is a circular region in which the fill is "active".
    *  Outside that region, it simply returns the colour from the original image. Inside the active
    *  region, this instead returns a color picked from the given (x, y) location in a blocky
    *  "mosaic image" that you should precompute in the constructor above. (So, THIS function's
    *  main job is just deciding which image to find the pixel in based on the circular active region.)
    *
    *  The mosaic image is divided into blockwidth x blockwidth square blocks, where the H/S/L/A values
    *  (x, y) will be set as the average H/S/L/A values of all pixels in the block of the
    *  original image where (x, y) resides.
    *
    *  Each square region has its upper left corner at a point where its
    *  image coordinates are divisible by blockwidth,
    *  e.g. for blockwidth = 5, the upper left corners of the blocks will be at
    *       (0,0),  (5,0),  (10,0), ...
    *       (0,5),  (5,5),  (10,5), ...
    *       (0,10), (5,10), (10,10), etc.
    *
    *  NOTE: Unlike PA1, do not be concerned about using the minimum angular interval(s)
    *        for computing hue average. Just use a simple arithmetic mean.
    *
    *  PARAM:  p - The point for which you're picking a color
    *  RETURN: The color chosen for (p).
    */
    virtual HSLAPixel operator()(PixelPoint p);

  private:
    unsigned int blockwidth; // width of a mosaic block in pixels.
    PixelPoint center;       // middle/center point of mosaic area
    unsigned int radius;     // maximum pixel distance away from center where the mosaic color will be applied
    PNG img;                 // Original image used in flood fill algorithm
    PNG blockyimg;           // fully block-ified version of the original image, computed once at creation time
};

#endif
