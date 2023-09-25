#include "afuncs.h"
#include <math.h>
#include "Unit2.h"

double TMP_mx[MX_ARR_LEN][MX_ARR_LEN];

AFuncs::AFuncs()
{

}


// Get sigmoid for single value
double AFuncs::getSigmoid(double x,  double  tilt, double bias)
{
  double tmp, res;
  tmp = pow( 2.72, -1.0*(x+bias) * tilt);  //-0.5
  res = (1/(1 + tmp));
  return res;
}
//----------------------------------------------------------------------------------------------------

float AFuncs::getSigmoid(float x,  float  tilt, float bias)
{
  float tmp, res;
  tmp = pow( 2.72, -1.0*(x+bias) * tilt);  //-0.5
  res = (1/(1 + tmp));
  return res;
}


// Get sigmoid for array
double AFuncs::getSigmoid(double arrX[], int len,  double  tilt, double bias)
{
  double tmp1, res;
  long double tmp;

  for (int var = 0; var < len; ++var) {
	  tmp1 = abs(-1.0*(arrX[var]+bias) * tilt);
      tmp = pow( 2.72, tmp1);  //-0.5
	  arrX[var] = (1/(1 + tmp));
  }
  return res;
}
//-----------------------------------------------------------------------------------------------------

float AFuncs::getSigmoid(float arrX[], int len,  float  tilt, float bias)
{
  double tmp, tmp1, res;
  for (int var = 0; var < len; ++var) {
	  tmp1 = -1.0*(arrX[var]+bias) * tilt;
	  tmp = pow( 2.72, tmp1);  //-0.5
	  tmp = (1/(1 + tmp));
	  arrX[var] = tmp;
  }
  return res;
}
//-----------------------------------------------------------------------------------------------------



// Multiplying matrixes
bool AFuncs::matrixMul(int l1, int r1, int a1[], int l2, int r2, int a2[], int lRes, int rRes,  int result[])
{
    int i,k, n;
    int arr1[MX_ARR_LEN][MX_ARR_LEN];
    int arr2[MX_ARR_LEN][MX_ARR_LEN];
    int arrRes[MX_ARR_LEN][MX_ARR_LEN];

    if (r1 != l2) return false;

    M_RESET_MATRIX(arrRes, MX_ARR_LEN)

    M_GET_TWO_MATRIX(l1,r1,a1, l2,r2,a2, arr1,arr2, MX_ARR_LEN)

    for(i=0; i < l1; i++){
        for(k=0; k < r2; k++){
             for(n=0; n < r1; n++){
                 arrRes[i][k] += arr1[i][n]*arr2[n][k];
             }
        }
    }
    i=0;
    M_CONV_MATRIX_TO_ARR(lRes, rRes, arrRes, result)

    return true;
}


// Multiplying matrixes
bool AFuncs::matrixMul(int l1, int r1, float a1[], int l2, int r2, float a2[], int lRes, int rRes,  float result[])
{
    int i,k, n;
    float arr1[MX_ARR_LEN][MX_ARR_LEN];
    float arr2[MX_ARR_LEN][MX_ARR_LEN];
    float arrRes[MX_ARR_LEN][MX_ARR_LEN];

    if (r1 != l2) return false;

    // M_RESET_MATRIX(arrRes, MX_ARR_LEN);

    M_GET_TWO_MATRIX(l1,r1,a1, l2,r2,a2, arr1,arr2, MX_ARR_LEN)

    for(i=0; i < l1; i++){
        for(k=0; k < r2; k++){
             arrRes[i][k] = 0;
             for(n=0; n < r1; n++){
                 arrRes[i][k] += arr1[i][n]*arr2[n][k];
             }
        }
    }
    i=0;
    M_CONV_MATRIX_TO_ARR(lRes, rRes, arrRes, result)

    return true;
}
//-----------------------------------------------------------------------------------------------------

// Multiplying matrixes
bool AFuncs::matrixMul(int l1, int r1, double a1[], int l2, int r2, double a2[], int lRes, int rRes,  double result[])
{
    int i,k, n;
    double arr1[MX_ARR_LEN][MX_ARR_LEN];
    double arr2[MX_ARR_LEN][MX_ARR_LEN];
    double arrRes[MX_ARR_LEN][MX_ARR_LEN];

    if (r1 != l2) return false;

    M_RESET_MATRIX(arrRes, MX_ARR_LEN);

    M_GET_TWO_MATRIX(l1,r1,a1, l2,r2,a2, arr1,arr2, MX_ARR_LEN)

    for(i=0; i < l1; i++){
        for(k=0; k < r2; k++){
             for(n=0; n < r1; n++){
                 arrRes[i][k] += arr1[i][n]*arr2[n][k];
             }
        }
    }
    i=0;
    M_CONV_MATRIX_TO_ARR(lRes, rRes, arrRes, result)

    return true;
}
//-----------------------------------------------------------------------------------------------------


// Multiplying an array by a matrix
void AFuncs::matrixMul( int arr[], int lns, int clmns, int serMx[],  int result[])
{
     
    int tmpArr[MX_ARR_LEN];
    M_RESET_ARR(tmpArr,MX_ARR_LEN)
    M_RESET_ARR(result, clmns)
    M_GET_MATRIX(lns,clmns,serMx,  TMP_mx)

    for(int c=0; c < clmns; c++){
        for(int l=0; l < lns; l++){
            tmpArr[c] += arr[l] * TMP_mx[l][c];
        }
    }
    M_ARR_COPY(tmpArr,result,clmns)
    return;
}
//-----------------------------------------------------------------------------------------------------

// Multiplying an array by a matrix
void AFuncs::matrixMul( float arr[], int lns, int clmns, float serMx[],  float result[])
{
    M_RESET_ARR(result, clmns)
	M_GET_MATRIX(lns,clmns,serMx,  TMP_mx)
	for(int i=0; i < clmns; i++){
		for(int n=0; n < lns; n++){
			result[i] += arr[n] * TMP_mx[n][i];
		}
	}
	return;
}
//-----------------------------------------------------------------------------------------------------

// Multiplying an array by a matrix
void AFuncs::matrixMul( double arr[], int lns, int clmns, double serMx[],  double result[])
{
    
	double tmpArr[MX_ARR_LEN];
    M_RESET_ARR(tmpArr,MX_ARR_LEN)
    M_RESET_ARR(result, clmns)
    M_GET_MATRIX(lns,clmns,serMx,  TMP_mx)

    for(int i=0; i < clmns; i++){
        for(int n=0; n < lns; n++){
            result[i] += arr[n] * TMP_mx[n][i];
        }
    }
}
//--------------------------------------------------------------------------------------------------------

// Multiplying an array by a matrix
void AFuncs::matrixMul( double arr[], int lns, int clmns, double **serMx,  double result[])
{
  
    M_RESET_ARR(result, clmns)
    for(int i=0; i < clmns; i++){
        for(int n=0; n < lns; n++){
            result[i] += arr[n] * serMx[n][i];
        }
    }
    return;
}
//--------------------------------------------------------------------------------------------------------


// Multiplying a matrix by an array
void AFuncs::matrixMul(int lns, int clmns, int serMx[],  int arr[],  int result[])
{
 	M_RESET_ARR(result, lns)
    M_GET_MATRIX(lns,clmns,serMx,  TMP_mx)

    for(int i=0; i < lns; i++){
        for(int n=0; n < clmns; n++){
            result[i] += arr[n] * TMP_mx[i][n];
        }
    }
 
}

// Multiplying a matrix by an array
void AFuncs::matrixMul(int lns, int clmns, float serMx[],  float arr[],  float result[])
{
	M_RESET_ARR(result, lns)
	M_GET_MATRIX(lns,clmns,serMx,  TMP_mx)

    for(int i=0; i < lns; i++){
		for(int n=0; n < clmns; n++){
			result[i] += arr[n] * TMP_mx[i][n];
		}
	}
}

// Multiplying a matrix by an array
void AFuncs::matrixMul(int lns, int clmns, double serMx[],  double arr[],  double result[])
{ 
    M_RESET_ARR(result, clmns)
    M_GET_MATRIX(lns,clmns,serMx,  TMP_mx)
    for(int i=0; i < lns; i++){
        for(int n=0; n < clmns; n++){
            result[i] += arr[n] * TMP_mx[i][n];
        }
    }
}
//--------------------------------------------------------------------------------------------------------------


// Multiplying an array  by an array (int)
int AFuncs::arraysMul(int *arr1, int *arr2, int len)
{
    int res = 0;
    for (int i = 0; i < len; ++i) {
        res += arr1[i] * arr2[i];
    }
    return res;
}

// Multiplying an array  by an array (float)
int AFuncs::arraysMul(float *arr1, float *arr2, int len)
{
    float res = 0;
    for (int i = 0; i < len; ++i) {
        res += arr1[i] * arr2[i];
    }
    return res;
}

// Multiplying an array  by an array (double)
int AFuncs::arraysMul(double *arr1, double *arr2, int len)
{
    double res = 0;
    for (int i = 0; i < len; ++i) {
        res += arr1[i] * arr2[i];
    }
    return res;
}





void AFuncs::matrixMul( float arr[], int lns, int clmns, float **serMx,  float result[])
{
    M_RESET_ARR(result, clmns)
	for(int i=0; i < clmns; i++){
		for(int n=0; n < lns; n++){
			result[i] += arr[n] * serMx[n][i];
		}
	}
	return;
}


void AFuncs::matrixMul(int lns, int clmns, float **serMx,  float arr[],  float result[])
{
	M_RESET_ARR(result, clmns)
	for(int i=0; i < lns; i++){
		for(int n=0; n < clmns; n++){
			result[i] += arr[n] * serMx[i][n];
		}
    }
    return;
}






















