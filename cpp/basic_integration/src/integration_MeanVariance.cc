#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "integration_MeanVariance.hh"


//------------------------------------------------------------------------------
//
// Integrate by taking the average function value within a sample of many trials
//
//------------------------------------------------------------------------------
double
integrate_1D_MeanVariance( double (*function)(double, double*), 
			   double* params, 
			   double range_i, double range_f, 
			   unsigned long ntrials,
			   double * sdev) 
//------------------------------------------------------------------------------
{

  double sum=0, ssum=0.;
  double V = (range_f-range_i);
  for( int i=0; i<ntrials; i++ ) {
    double x = V*rand()/RAND_MAX;
    double y = function(x,params);
    //printf( "x: %lf y: %lf\n", x,y);
    sum += y; ssum += y*y;
  } // trials

  double mean = sum/ntrials;
  double std_dev_y  = sqrt((1./(ntrials-1))*(ssum - ntrials*mean*mean)); 
  double std_dev    = sqrt((1./(ntrials-1))*(ssum - ntrials*mean*mean)); 
  if( sdev != NULL )
    *sdev = std_dev;
  return V*mean;
}


