#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integration_Naive.hh"
#include "sphere_functions.hh"

#ifdef PERF_TIME
#include <sys/time.h>
struct timeval t_start, t_stop;
#endif

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

  int factor=8 / 4 * 3; //  8 * 4/3 * pi * R^3 for volume of sphere

#ifdef PERF_TIME
  gettimeofday(&t_start,NULL);
#endif

  if( verbose ) volume=integrate_2D_Naive(&spherical_cap_3D, (double*)&params, 0., 1., ntrials, &points);
  else          volume=integrate_2D_Naive(&spherical_cap_3D, (double*)&params, 0., 1., ntrials );

#ifdef PERF_TIME
  gettimeofday(&t_stop,NULL);
  unsigned delta_t = 1e6*(t_stop.tv_sec - t_start.tv_sec) + (t_stop.tv_usec - t_start.tv_usec);

  // with true error
  fprintf( stderr, "Volume: %lf\t8xVolume: %lf\terror: %lf\tNtrials: %lu\tusec: %lu\n", 
	   volume, factor*volume, factor*binomial_error(ntrials, (M_PI/factor)*ntrials), ntrials, delta_t);
#else

  // with true error
  fprintf( stderr, "Volume: %lf\t8xVolume: %lf\terror: %lf\tNtrials: %lu\n", 
	   volume, factor*volume, factor*binomial_error(ntrials, (M_PI/factor)*ntrials), ntrials);
#endif

  // with estimated error
  //fprintf( stderr, "Volume: %lf\t4xVolume: %lf\terror: %lf\tNtrials: %lu\n", 
  //volume, 4*volume, 4*binomial_error(ntrials, volume*ntrials), ntrials);

}
