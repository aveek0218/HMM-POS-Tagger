#include <iostream>
#include <string>

#include "mex.h"


// Input: text: char type matrix, delim: char type matrix.
// Output: cell n x 1, each contain a piece of text.
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  char *text, *delim;
  mwSize buflen;
  
  buflen = mxGetNumberOfElements(prhs[0]) + 1;
  text = (char*)mxCalloc(buflen, sizeof(char));
  if (mxGetString(prhs[0], text, buflen) != 0)
    mexErrMsgIdAndTxt( "MATLAB:explore:invalidStringArray",
            "Could not convert string data.");

  buflen = mxGetNumberOfElements(prhs[1]) + 1;
  delim = (char*)mxCalloc(buflen, sizeof(char));
  if (mxGetString(prhs[1], delim, buflen) != 0)
    mexErrMsgIdAndTxt( "MATLAB:explore:invalidStringArray",
            "Could not convert string data.");
  
  int ndelim = 0;
  
  for (int i=0; text[i] != '\0'; i++)
  {
    if (text[i] == delim[0])
    {
      bool bDelim = true;
      int j;
      for (j=1; delim[j] != '\0'; j++)
      {
        if (text[i+j] == '\0' || text[i+j] != delim[j])
        {
          bDelim = false;
          break;
        }
      }
      if (bDelim)
      {
        ndelim ++;
        i = i + j - 1;
      }
    }
  }
  
  mwSize dims[2];
  dims[0] = ndelim+1;
  dims[1] = 1;
  
  plhs[0] = mxCreateCellArray(2, dims);
  
  int ilast = 0;
  int ielem = 0;
  
  for (int i=0; text[i] != '\0'; i++)
  {
    if (text[i] == delim[0])
    {
      bool bDelim = true;
      int j;
      for (j=1; delim[j] != '\0'; j++)
      {
        if (text[i+j] == '\0' || text[i+j] != delim[j])
        {
          bDelim = false;
          break;
        }
      }
      if (bDelim)
      {
        text[i] = '\0';
        mxArray* melem = mxCreateString(text + ilast);
        text[i] = delim[0];
        mxSetCell(plhs[0], ielem, melem);
        //  mxDestroyArray(melem);
        
        ilast = i+j;
        ielem ++;
        i = i + j - 1;
      }
    }
  }
  
  mxArray* melem = mxCreateString(text + ilast);
  mxSetCell(plhs[0], ielem, melem);
}
