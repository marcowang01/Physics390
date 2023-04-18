#include <stdio.h>
#include <stdlib.h>
#include "probability.hh"

unsigned count_reject=0, count_metro=0;


//----------------------------------------------
// usage: ./test_maxwell_boltzmann_metropolis [random seed] [a] [test_cdf]
// example: ./test_maxwell_boltzmann_metropolis $RANDOM 1.0 1 > maxwell_boltzmann.dat
// ---------------------------------------------

int main(int argc, char** argv) {

  if( argc < 2 ) {
    fprintf(stderr,"Error : need a single argument (random seed)\n");
    return -1;
  }

  srand(strtoul(argv[1],NULL,10));

  double a = 1;
  if ( argc > 2 ) {
    a = strtod(argv[2],NULL);
  }

  bool test_cdf = false;
  if ( argc > 3 ) {
    test_cdf = true;
  }
  
  double range_i = 0.;
  double range_f =  20.;
  double params[1] = {a};

  double x_metro = range_i + rand()*((range_f-range_i)/RAND_MAX);;
  for( int i=0; i<500000; i++ ) { 

    if (test_cdf){
      x_metro  = sample_pdf_metropolis( &cdf_maxwell_boltzmann, (double*)&params, range_i, range_f, x_metro);
    } else {
      x_metro  = sample_pdf_metropolis( &pdf_maxwell_boltzmann, (double*)&params, range_i, range_f, x_metro);
    }
    printf( "i: %d val: %lf\n", i, x_metro);
  }

  fprintf(stderr, "count_metro: %d\n", count_metro);

}
