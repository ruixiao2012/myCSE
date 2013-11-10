#include "mex.h"
/*
 * arrayProduct.c
 * Multiplies an input scalar times a 1xN matrix 
 * and outputs a 1xN matrix
 *
 * mex arrayProduct.c
 * This is a MEX-file for MATLAB.
*/
/* http://www.mathworks.cn/cn/help/matlab/matlab_external/using-mex-files-to-call-c-c-and-fortran-programs.html#brgxbjv-1
 */
/* call this function in matlab command
s = 5; 
A = [1.5, 2, 9];
B = arrayProduct(s,A) */
/* void arrayProduct(double x, double *y, double *z, int n)
{
  int i;
  
  for (i=0; i<n; i++) {
    z[i] = x * y[i];
  }
} */ 

/* coumputational routine */
/* the int type has to be changed into mwSize */
void arrayProduct(double x, double *y, double *z, mwSize n)
{
  mwSize i;
  
  for (i=0; i<n; i++) {
    z[i] = x * y[i];
  }
}

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
/* variable declarations here */
    double multiplier;      /* input scalar */
    double *inMatrix;       /* 1xN input matrix */
    mwSize ncols;           /* size of matrix */
    double *outMatrix;      /* output matrix */

    
/* function routine */
    /* check for proper number of arguments */
    if(nrhs!=2) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs",
                "Two inputs required.");
    }
    if(nlhs!=1) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs",
                "One output required.");
    }
    
    /* make sure the first input argument is scalar */
    if( !mxIsDouble(prhs[0]) ||
            mxIsComplex(prhs[0]) ||
            mxGetNumberOfElements(prhs[0])!=1 ) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notScalar",
                "Input multiplier must be a scalar.");
    }
    /* check that number of rows in second input argument is 1 */
    if(mxGetM(prhs[1])!=1) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notRowVector",
                "Input must be a row vector.");
    }    
    
    
/* code here */    
    /* get the value of the scalar input  */
    multiplier = mxGetScalar(prhs[0]);
    /* create a pointer to the real data in the input matrix  */
    inMatrix = mxGetPr(prhs[1]);
    /* get dimensions of the input matrix */
    ncols = mxGetN(prhs[1]);
    
    /* create the output matrix */
    plhs[0] = mxCreateDoubleMatrix(1, ncols, mxREAL);
    /* get a pointer to the real data in the output matrix */
    outMatrix = mxGetPr(plhs[0]);
    /* call the computational routine */
    arrayProduct(multiplier, inMatrix, outMatrix, ncols);
    

}