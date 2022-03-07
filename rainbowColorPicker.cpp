#include "rainbowColorPicker.h"
#include <math.h>

using std::pair;
using std::map;

RainbowColorPicker::RainbowColorPicker(long double freq_) : iter(0), freq(freq_)
{
}

HSLAPixel RainbowColorPicker::operator()(PixelPoint p)
{
    PNGmap::iterator stored = prev.find(pair<int, int>(p.x, p.y));
    if (stored == prev.end()) {
        HSLAPixel next = NextColor();
        prev[pair<int, int>(p.x, p.y)] = next;
        return next;
    } else
        return stored->second;
}

// http://www.krazydad.com/makecolors.php
HSLAPixel RainbowColorPicker::NextColor()
{
    HSLAPixel ret;
    if (iter * freq > 1) iter = 0;
    ret.h = (360 * iter * freq);
    ret.s = 1.0;
    ret.l = 0.5;
    iter++;
    return ret;
}
