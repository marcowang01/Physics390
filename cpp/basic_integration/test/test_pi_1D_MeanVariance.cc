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

  double integral = integrate_1D_MeanVariance(&circular_arc_2D, (double*)&params, range_i, range_f., ntrials );

  fprintf( stderr, "Integral: %lf\t4xIntegral: %lf\terror: %lf\tNtrials: %lu\n", 
	   integral, 4*integral, 4*circular_arc_2D_variance(ntrials,range_i,range_f), ntrials);
}
