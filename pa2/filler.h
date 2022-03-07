/*
*  File:        filler.h
*  Description: Defintion of a filler namespace.
*
*/
#ifndef _FILLER_H_
#define _FILLER_H_

#include <iostream>

#include "cs221util/PNG.h"

#include "animation.h"
#include "pixelpoint.h"
#include "priority.h"
#include "colorPicker.h"
#include "queue.h"
#include "stack.h"

using namespace std;
using namespace cs221util;

/*
*  filler namespace: specifies a set of functions for performing flood
*  fills on images.
*
*/
namespace filler
{

  /*
  * Struct to store configuration variables for filler function.
  */
  struct FillerConfig
  {
    int frameFreq;                      // Frequency with which to save frames to GIF animation.
    double tolerance;                    // Tolerance used to determine if pixel is in fill region.
    PNG img;                            // Image to perform the fill on.
    PixelPoint seedpoint;               // Seed location where the fill will begin.
    PriorityNeighbours neighbourorder;  // Structure for determining order of neighbours to explore (to add to the ordering structure)
    ColorPicker* picker;                // colorPicker used to fill the region.
  };

  /*
  *  Performs a flood fill using breadth first search.
  *
  *  PARAM:  config - FillerConfig struct to setup the fill.
  *  RETURN: animation object illustrating progression of flood fill algorithm.
  */
  animation FillBFS(FillerConfig& config);

  /*
  *  Performs a flood fill using depth first search.
  *
  *  PARAM:  config - FillerConfig struct to setup the fill.
  *  RETURN: animation object illustrating progression of flood fill algorithm.
  */
  animation FillDFS(FillerConfig& config);

  /*
  *  Run a flood fill on an image starting at the seed point.
  *
  *  PARAM: config - FillerConfig struct with data for flood fill of image.
  *  RETURN: animation object illustrating progression of flood fill algorithm.
  */
  template <template <class T> class OrderingStructure> animation Fill(FillerConfig& config);

  // Add any helper functions here

} // namespace filler

#include "filler.cpp"

#endif
