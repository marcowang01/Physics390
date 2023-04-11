#ifndef PRNG_PDFS
#define PRNG_PDFS


double pdf_uniform( double x, double* params ); 

double pdf_exponential( double x, double* params );
double cdf_exponential( double x, double* params );

double pdf_gaussian( double x, double* params );
double cdf_gaussian( double x, double* params );

double pdf_double_gaussian( double x, double* params );

double pdf_student( double x, double* params );

double pdf_gamma( double x, double* params );


#endif
