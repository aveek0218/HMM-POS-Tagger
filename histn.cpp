/* Usage:
 *      [h] = histn(x, n, w);
 *      suppose x contains numbers in 1:n, count them.
 *      if w is presented, then sum over the weights of w
*/ 
// #define __STDC_UTF_16__
#include "mex.h"

#include <memory.h>

void
mexFunction( int nlhs, mxArray *plhs[],
             int nrhs, const mxArray *prhs[] )
{
    if(nrhs < 2 || nrhs > 3)
        return;
    
    mwSize nbdims = mxGetNumberOfDimensions(prhs[0]);
    const mwSize *dims;
    dims = mxGetDimensions(prhs[0]);
    int numel = 1;
    for (int i=0;i<nbdims;i++)
        numel *= dims[i];
    
    double* x = mxGetPr(prhs[0]);
    int n = int(*(mxGetPr(prhs[1])));
    
    double* w = nrhs == 3 ? mxGetPr(prhs[2]) : 0;
    
    plhs[0] = mxCreateDoubleMatrix(n, 1, mxREAL);
    double *h = mxGetPr(plhs[0]);
    memset(h, 0, sizeof(double) * n);
    
    int outofrange = 0;
    for (int i=0;i<numel;i++)
    {
        int xi = x[i] - 1;
        
        if(xi < 0 || xi >= n)
            outofrange ++;
        else
            h[xi] += w == 0 ? 1.0 : w[i];
    }
    
    if(outofrange > 0)
        printf("Warning: Error in histn: # out of range = %d, \n"
               "         out of range numbers are discarded.\n", outofrange);
}
