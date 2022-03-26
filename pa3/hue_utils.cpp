/*
*  File:        hue_utils.cpp
*  Description: Contains implementation of functions which will be useful for producing visually-meaningful
*               averages of a hue channel
*
*               Basic principles:
*               Hue is represented as a floating point value in degrees, in the range of [0, 360).
*               In order to compute an "average" hue over two or more points, we will use
*               trigonometry to convert the unit vector of the hue angle (in radians) into
*               Cartesian (x,y) vector components.
*               The Cartesian vector components can be averaged using a simple mean
*               (or weighted mean, in the case of computing average colour of a node from its children)
*               and the average Cartesian vectors will then be converted back to a unit vector
*               hue angle (in radians), and finally converted back to an angle in degrees.
*
*               Example: average of 315, 300, and 30
*
*               315 : x-component ~=  0.7071, y-component ~= -0.7071
*               300 : x-component  =  0.5,    y-component ~= -0.8660
*                30 : x-component ~=  0.8660, y-component  =  0.5
*
*                 avg x-component ~=  0.6910
*                 avg y-component ~= -0.3577
*
*               hue angle (in radians) ~= 5.8055
*               hue angle (in degrees) ~= 332.6322
*/

#include "hue_utils.h"

/*
*  Obtains the x-component of a unit vector provided as an angle in degrees.
*  PARAM:  angle - hue value whose x-component is to be obtained
*  PRE:    angle is a double in the range of [0, 360)
*  RETURN: Cartesian x-component of the input angle
*/
double Deg2X(double angle) {
  double rads = angle * PI / 180.0; // get the angle in radians, for use with cmath trig functions
  return cos(rads); // Remember SOHCAHTOA
}

/*
*  Obtains the y-component of a unit vector provided as an angle in degrees.
*  PARAM: angle - hue value whose y-component is to be obtained
*  PRE:   angle is a double in the range of [0, 360)
*  RETURN: Cartesian y-component of the input angle
*/
double Deg2Y(double angle) {
  double rads = angle * PI / 180.0; // get the angle in radians, for use with cmath trig functions
  return sin(rads); // Remember SOHCAHTOA
}

/*
*  Converts a Cartesian direction vector supplied as x- and y- components into an angle in degrees.
*  PARAM:  x_component - x-component of the Cartesian vector
*  PARAM:  y_compoennt - y-component of the Cartesian vector
*  RETURN: angle in degrees of the provided Cartesian components
*/
double XY2Deg(double x_component, double y_component) {
  if (x_component == 0 && y_component == 0)
    return 0; // some arbitrary hue vector!
  double rads = atan2(y_component, x_component); // get the angle in radians. Remember SOHCAHTOA
  double degs = fmod(rads * 180.0 / PI, 360);
  if (degs < 0)
    degs += 360;
  return degs;
}