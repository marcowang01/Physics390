#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integration_MeanVariance.hh"
#include "probability.hh"


//
// variance of the target function itself 
// doesn't help here ..
//
/*
double
variance_maxwell_boltzmann( double * params )
{
  double a = params[0];
  double var = a*a*(3.*M_PI - 8.)/M_PI;
  return var;
}
*/

int 
main(int argc, char** argv ) 
{ 
  
  unsigned seed = strtoul(argv[1],NULL,10);
  unsigned long ntrials = strtoul(argv[2],NULL,10);
  unsigned long nevents = strtoul(argv[3],NULL,10);

  double params = { 1. };  // a
  srand(seed);

  double range_i = 0.;
  double range_f = 20.;
  double V =  range_f - range_i;

  MeanVarianceResults results; 
  for(int i=0; i<ntrials; i++ ) {


    results  = integrate_1D_MeanVariance(&pdf_maxwell_boltzmann, (double*)&params, range_i, range_f, nevents );
    fprintf( stderr, "i: %d\tintegral: %lf\terror: %lf\tNevents: %lu\n", 
	     i, results.integral, results.error, nevents);
  }
}
