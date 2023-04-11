#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "cdfs.hh"


// -----------------------------------------------------------------------------
// exponential CDF
// -----------------------------------------------------------------------------
double 
cdf_exponential( double x, double* params ) 
// -----------------------------------------------------------------------------
{ 
  double lambda = params[0];
  return 1. - exp(-lambda*x);
}


// -----------------------------------------------------------------------------
// gaussian CDF
// -----------------------------------------------------------------------------
double 
cdf_gaussian( double x, double* params ) 
// -----------------------------------------------------------------------------
{ 
  double mu = params[0];
  double sigma = params[1];
  double arg_erf = (x-mu)/(sqrt(2)*sigma);
  return 0.5*( 1. + erf(arg_erf));
}
