#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integration_Naive.hh"
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
  double dim = range_f - range_i;
  double V = dim*dim;

  for(int i=0; i<ntrials; i++ ) {

    double result  = integrate_1D_Naive(&pdf_maxwell_boltzmann, (double*)&params, range_i, range_f, nevents );
    double ninside = nevents*(result/V);
    double error   = V*binomial_error(nevents, ninside);
    fprintf( stderr, "i: %d integral: %lf error: %lf Nevents: %lu\n", 
	     i, result, error, nevents);
  }
}
