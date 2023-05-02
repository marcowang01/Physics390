#ifndef SPHERE_FUNCTIONS
#define SPHERE_FUNCTIONS

#include <math.h>

//------------------------------------------------------------------------------
//
// The volume under which is 1/8 * 4/3 * pi * R^3
//
//------------------------------------------------------------------------------
double 
spherical_cap_3D( double x, double y, double* params) 
//------------------------------------------------------------------------------
{
  double R = params[0];
  return sqrt( R*R - x*x - y*y );
};


#endif
