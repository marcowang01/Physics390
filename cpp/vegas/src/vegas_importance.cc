#include <iostream>
#include <vector>
#include <utility> // for pair
#include <numeric> // accumulate
#include <cmath>
#include <stdlib.h>
#include <assert.h>

using namespace std;

#include "vegas_constants.hh"
#include "vegas_importance.hh"



// -----------------------------------------------------------------------------
//
//
//
// -----------------------------------------------------------------------------
void
setup_map( vector<VegasBin> &xvec, double range_i, double range_f, unsigned Ng) 
// -----------------------------------------------------------------------------
{
  xvec.clear();
  for( int i=0; i<Ng; i++ ) { 
    double width = (range_f-range_i)/Ng;
    double lbound = range_i + i*width;
    xvec.push_back(VegasBin {lbound,width});
  }
}



// -----------------------------------------------------------------------------
//
//
//
// -----------------------------------------------------------------------------
int
find_x_bin( double x, vector<VegasBin> &xvec )
// -----------------------------------------------------------------------------
{
  int bin=0;
  while( x > xvec[bin].low_edge ) {  
    bin++;
    if( bin >= xvec.size() ) break;
  }
  return bin-1;
}


// -----------------------------------------------------------------------------
//
//
//
// -----------------------------------------------------------------------------
double 
xform__x_from_y( double y, vector<VegasBin> &xvec, int Ng )  
// -----------------------------------------------------------------------------
{
  int    i_y = floor(y*Ng);
  double d_y = y*Ng - i_y;
  double x_y = xvec[i_y].low_edge + (xvec[i_y].width)*d_y;
  return x_y;
}



// -----------------------------------------------------------------------------
//
//
//
// -----------------------------------------------------------------------------
double 
Jy( double y, vector<VegasBin> &xvec, int Ng )  
// -----------------------------------------------------------------------------
{
  int    i_y = floor(y*Ng);
  double j_y = Ng*xvec[i_y].width;
  return j_y;
}



// -----------------------------------------------------------------------------
//
//
//
// -----------------------------------------------------------------------------
void 
update_map( vector<VegasBin> &xvec, vector<double> &dvec, int Ng )  
// -----------------------------------------------------------------------------
{
  vector<VegasBin> xvecp;
  xvecp.assign(xvec.begin(),xvec.end()); // to inherit first & last boundaries
  double delta_d = accumulate(dvec.begin(),dvec.end(),0.) / Ng;

  int j=-1;
  double Sd = 0.;
  for( int i=1; i<xvecp.size(); i++ ) {  // step 2

    while(  Sd < delta_d ) {   // step 3
      j++;
      if( j < Ng )
	Sd += dvec[j];
      else { 
	cerr << "breaking while ..." << endl;
	break;
      }
    }
    Sd -= delta_d;

    
    assert( Sd > 0 );
    assert( dvec[j] > 0 );
    assert( xvec[j].width > 0 );
    assert( (Sd/dvec[j])*xvec[j].width > 0 );

    if( j+1 < Ng ) 
      xvecp[i].low_edge  = xvec[j+1].low_edge - (Sd/dvec[j])*xvec[j].width;
    else 
      xvecp[i].low_edge  = VEGAS_HIGH_RANGE - (Sd/dvec[j])*xvec[j].width;

  }

  //
  // update the widths
  //
  for( int i=0; i<xvecp.size(); i++ ) {
    if( i < xvecp.size()-1 ) { 
      xvecp[i].width = xvecp[i+1].low_edge - xvecp[i].low_edge;
      if( xvecp[i].width < 0 ) cerr << "err width i: " << i
				     << "\thi: " << xvecp[i+1].low_edge 
				     << "\tlo: " << xvecp[i].low_edge << endl;
    }
    else {
      xvecp[i].width = VEGAS_HIGH_RANGE - xvecp[i].low_edge;
      if( xvecp[i].width < 0 ) cerr << "err width i: " << i
				     << "\thi: " << VEGAS_HIGH_RANGE 
				     << "\tlo: " << xvecp[i].low_edge << endl;
    }
  }

  // update the map
  xvec = xvecp;
}

// 
// normalize the dvec
//
void
normalize_d( vector<double> &dvec, vector<int> &nvec )
{
  if(dvec.size() != nvec.size()){
    cout << "Error: vectors are of unequal length." << endl;
    return;
  }
  // iterate over the vector and normalize
  for(size_t i = 0; i < dvec.size(); i++) {
      if(nvec[i] != 0) { // avoid division by zero
          dvec[i] /= nvec[i]; // divide by the corresponding element in nvec
      }
      else {
          dvec[i] = 0.0; // if the nvec element is 0, assign 0.0 to the corresponding element in dvec
      }
  }
}

//
// smooth the dvec
//
void
smooth( vector<double> &dvec)
{
  vector<double> copy = dvec;
  dvec[0] = (7 * copy[0] + copy[1]) / 8.;
  for (int i = 1; i < dvec.size() - 1; i++) {
    dvec[i] = (copy[i-1] + 6 * copy[i] + copy[i+1]) / 8.;
  }
  dvec[dvec.size()-1] = (copy[dvec.size()-2] + 7 * copy[dvec.size()-1]) / 8.;
}

//
// compress the dvec with parameter alpha
//
void
compress( vector<double> &dvec, double alpha)
{
  for (int i = 0; i < dvec.size(); i++) {
    if (dvec[i] == 0) {
        cout << "Error: Division by zero encountered. The input vector must not contain zeros." << endl;
        return;
    }
    dvec[i] = pow((1-dvec[i])/(log(1/dvec[i])), alpha);
  }
}

