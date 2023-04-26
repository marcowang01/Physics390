#include <stdio.h>
#include <stdlib.h>
#include "probability.hh"

unsigned count_reject=0, count_metro=0;

int main(int argc, char** argv) {

  if( argc != 3 ) {
    fprintf(stderr,"Error : arguments <random seed> <a>\n");
    return -1;
  }

  srand(strtoul(argv[1],NULL,10));
  double a = strtoul(argv[2],NULL,10);
  
  double range_i = 0.;
  double range_f = 20.;
  double params[1] = {a};

  double x;
  for( int i=0; i<250000; i++ ) { 
    x = sample_pdf_rejection( &pdf_maxwell_boltzmann, (double*)&params, range_i, range_f);
    printf( "i: %d val: %lf\n", i, x);
  }

}
