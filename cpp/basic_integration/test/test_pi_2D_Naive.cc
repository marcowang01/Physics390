#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integration_Naive.hh"
#include "circle_functions.hh"



int 
main(int argc, char** argv ) 
{ 

  unsigned seed = strtoul(argv[1],NULL,10);
  unsigned long ntrials = strtoul(argv[2],NULL,10);
  unsigned verbose=0;
  if( argc > 3 ) { 
    verbose = 1;
  }

  Points3D points;
  double params[] = { 1. }; // circle of radius 1.0
  srand(seed);

  double volume;
  if( verbose ) volume=integrate_2D_Naive(&sphereical_shell_3D, (double*)&params, 0., 1., ntrials, &points);
  else          volume=integrate_2D_Naive(&sphereical_shell_3D, (double*)&params, 0., 1., ntrials );


  // with true error
  // pi_estimate is from volumne of 1 octanct of the sphere
  // V  = (1/8) * (4/3)pi
  //    = pi/6
  fprintf( stderr, "Volume: %lf\t6xVolume: %lf\terror: %lf\tNtrials: %lu\n", 
	   volume, 6*volume, 6*binomial_error(ntrials, (1./6)*(4*M_PI/3)*ntrials), ntrials);

}
