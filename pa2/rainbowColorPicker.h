#ifndef RAINBOWCOLORPICKER_H
#define RAINBOWCOLORPICKER_H

#include <stdint.h>
#include <map>
#include <utility>
#include "colorPicker.h"

/**
 * RainbowColorPicker: a functor that determines the color that should be used
 * given an x and a y coordinate using a rainbow pattern.
 *
 */
class RainbowColorPicker : public ColorPicker
{
  public:
    /**
     * Constructs a new rainbowColorPicker.
     *
     * @param freq_ Frequency at which to cycle colors
     */
    RainbowColorPicker(long double freq_);

    /**
     * Picks the color for pixel (x, y).
     *
     * @param x The x coordinate to pick a color for.
     * @param y The y coordinat to pick a color for.
     * @return The color chosen for (x, y).
     */
    virtual HSLAPixel operator()(PixelPoint p);

  private:
    HSLAPixel NextColor();

    typedef std::map<std::pair<int, int>, HSLAPixel> PNGmap;
    size_t iter;
    PNGmap prev;
    long double freq;
};

#endif
