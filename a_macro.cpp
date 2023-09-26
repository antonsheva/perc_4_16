#include "afuncs.h"
#define M_GET_MATRIX(lines, clmn, arr, mx)                     \
    for(int i = 0; i < lines; i++){                         \
         for (int k = 0; k < clmn ; k++){                \
             mx[i][k] = arr[i * clmn + k];     \
         }                                                                 \
    }                                                                      \

/*
    for (int i=0; i < MX_ARR_LEN; i++){                     \
       for (int k=0; k < MX_ARR_LEN; k++){                \
            mx[i][k]=0;                                     \
        }                                                                  \
    }  
*/




#define M_GET_TWO_MATRIX(l1, r1, a1, l2,r2,a2, arr1,arr2,  arrLen)  \
    for (int l=0; l < arrLen; l++){                     \
       for (int k=0; k < arrLen; k++){                \
            arr1[l][k]=0;                                     \
            arr2[l][k]=0;                                     \
        }                                                                  \
    }                                                                      \
    for(int l = 0; l < l1; l++){                         \
         for (int k = 0; k < r1 ; k++){                \
             arr1[l][k] = a1[l * r1 + k];     \
         }                                                                 \
    }                                                                      \
    for(int l = 0; l < l2; l++){                        \
         for (int k = 0; k < r2 ; k++){               \
             arr2[l][k] = a2[l * r2 + k];     \
         }                                                                 \
    }

#define M_ARR(l, r, arr) \
    l, r, &arr[0][0]

#define M_CONV_MATRIX_TO_ARR(l,r,inArr, outArr)\
    for(int cmtaI = 0; cmtaI < l; cmtaI++){\
         for (int cmtaK = 0; cmtaK < r ; cmtaK++){\
             outArr[cmtaI * r + cmtaK] = inArr[cmtaI][cmtaK];\
         }\
    }

#define M_RESET_ARR(arr, len)\
    for (int rstaI=0; rstaI < len; rstaI++) arr[rstaI]  = 0;

#define M_SET_ARR(arr, val, len)\
    for (int rstaI=0; rstaI < len; rstaI++) arr[rstaI]  = val;


#define M_RESET_MATRIX(matrix, len)            \
    for (int rstmI=0; rstmI < len; rstmI++){      \
       for (int rstmK=0; rstmK < len; rstmK++){ \
            matrix[rstmI][rstmK]=0;                    \
        }                                                       \
    }

#define M_RESET_MX(matrix, lns, clmns)            \
    for (int rstmI=0; rstmI < lns; rstmI++){      \
       for (int rstmK=0; rstmK < clmns; rstmK++){ \
            matrix[rstmI][rstmK]=0;                    \
        }                                                       \
    }

#define M_SET_MATRIX(matrix, val, l,r)         \
    for (int rstmI=0; rstmI < l; rstmI++){        \
       for (int rstmK=0; rstmK < r; rstmK++){   \
            matrix[rstmI][rstmK]=val;               \
        }                                                    \
    }

#define M_ARR_COPY(arr1,arr2,len)\
    for (int i = 0; i < len; ++i) {\
        arr2[i]=arr1[i];\
    }

#define M_COPY_MX_TO_ARR(mx, h,w, arr)\
    for(int y=0; y<h; y++){\
        for(int x=0; x<w; x++){\
            arr[y*w+x] = mx[y][x];\
        }\
    }











