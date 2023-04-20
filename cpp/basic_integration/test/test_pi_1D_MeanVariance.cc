#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integration_MeanVariance.hh"
#include "circle_functions.hh"


int 
main(int argc, char** argv ) 
{ 
  
  unsigned seed = strtoul(argv[1],NULL,10);
  unsigned long ntrials = strtoul(argv[2],NULL,10);

  double params[] = { 1. }; // circle of radius 1.0
  double range_i = 0.;
  double range_f = 1.;
  srand(seed);

  MeanVarianceResults results = 
    integrate_1D_MeanVariance(&circular_arc_2D, (double*)&params, range_i, range_f, ntrials);

  // with estimated variance from MC
  fprintf( stderr, "Integral: %lf\t4xIntegral: %lf\terror: %lf\tNtrials: %lu\n", 
  results.integral, 4*results.integral, 4*results.error, ntrials);

}
