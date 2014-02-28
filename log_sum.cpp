// Assume input is 2d matrix and output is a row vector.

#include <cmath>
#include "mex.h"

double log_sum(double log_a, double log_b)
{
  double v;

  if (log_a < log_b)
  {
      v = log_b+log(1 + exp(log_a-log_b));
  }
  else
  {
      v = log_a+log(1 + exp(log_b-log_a));
  }
  return(v);
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  const mwSize *dims = mxGetDimensions(prhs[0]);
  double* x = mxGetPr(prhs[0]);
  plhs[0] = mxCreateDoubleMatrix(1, dims[1], mxREAL);
  double* y = mxGetPr(plhs[0]);
  
  int offset = 0;
  for (int i=0; i<dims[1]; i++, offset += dims[0])
  {
    double lsum = x[offset];
    for (int j=1; j<dims[0]; j++)
      lsum = log_sum(lsum, x[offset+j]);
    y[i] = lsum;
  }
}
