#include <stdio.h>
#include <stdlib.h>
#include "pdfs.hh"
#include "sampling.hh"

unsigned do_count_reject=1;
unsigned count_reject=0, count_metro=0;

int main(int argc, char** argv) {

  srand(strtoul(argv[1],NULL,10));
  
  double params[2] = {0.25,1.5};
  double range_i = -5;
  double range_f =  5;

  double x_reject, x_metro;

  // warm up MH
  x_metro = range_i + rand()*((range_f-range_i)/RAND_MAX);
  for( int i=0; i<50000; i++ ) 
    x_metro, sample_pdf_metropolis( &pdf_gaussian, (double*)&params, range_i, range_f, x_metro);

  for( int i=0; i<200000; i++ ) { 
    do_count_reject=1;
    x_reject = sample_pdf_rejection( &pdf_gaussian, (double*)&params, range_i, range_f);
    do_count_reject=0;
    x_metro  = sample_pdf_metropolis( &pdf_gaussian, (double*)&params, range_i, range_f, x_metro);
    printf( "%d %lf %lf\n", i, x_reject, x_metro);
  }

  fprintf(stderr, "count_reject: %d\tcount_metro: %d\n", count_reject, count_metro);


}
